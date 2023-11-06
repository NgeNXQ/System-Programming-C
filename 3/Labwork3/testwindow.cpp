#include "testwindow.h"
#include "ui_testwindow.h"

#include <QFile>
#include <QDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "testdata.h"

TestWindow* TestWindow::instance = nullptr;

TestWindow::TestWindow(QWidget* parent, const QString& filePath) : QDialog(parent), ui(new Ui::TestWindow)
{
    const int TEST_WINDOW_WIDTH = 500;
    const int TEST_WINDOW_HEIGHT = 500;

    this->ui->setupUi(this);

    this->setWindowTitle("Питання № ТЕСТ");
    this->setMinimumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);
    this->setMaximumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);

    this->labelQuestion = new QLabel(this);
    this->answersLayout = new QVBoxLayout(this);
    this->buttonNext = new QPushButton("Next", this);

    this->ui->verticalLayout->addWidget(this->buttonNext);
    this->ui->verticalLayout->addWidget(this->labelQuestion);
    this->ui->verticalLayout->addLayout(this->answersLayout);

    this->currentQuestionIndex = 0;
    this->loadTest(filePath);
    this->displayQuestion();

    connect(this, &TestWindow::destroyed, this, &TestWindow::deleteInstance);
    connect(buttonNext, &QPushButton::clicked, this, &TestWindow::onButtonNextClicked);
}

void TestWindow::loadTest(const QString& filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&file);
        TestData test;

        while (!inStream.atEnd())
        {
            QString line = inStream.readLine().trimmed();

            if (line.startsWith("[Q]"))
            {
                if (!test.questionText.isEmpty())
                    this->tests.append(test);

                test.questionText = line.mid(3).trimmed();
                test.correctAnswers.clear();
                test.incorrectAnswers.clear();

            }
            else if (line.startsWith("[C]"))
            {
                test.correctAnswers.append(line.mid(3).trimmed());
            }
            else if (line.startsWith("[I]"))
            {
                test.incorrectAnswers.append(line.mid(3).trimmed());
            }
        }

        if (!test.questionText.isEmpty())
            tests.append(test);

        file.close();
    }
}

void TestWindow::displayQuestion()
{
    if (currentQuestionIndex < this->tests.size())
    {
        const TestData& currentQuestion = this->tests.at(currentQuestionIndex);
        this->labelQuestion->setText(currentQuestion.questionText);

        QLayoutItem* item;

        while ((item = answersLayout->takeAt(0)))
        {
            delete item->widget();
            delete item;
        }

        for (const QString& answer : currentQuestion.correctAnswers)
        {
            QCheckBox* radioButton = new QCheckBox(answer, this);
            answersLayout->addWidget(radioButton);
        }

        for (const QString& answer : currentQuestion.incorrectAnswers)
        {
            QCheckBox* radioButton = new QCheckBox(answer, this);
            answersLayout->addWidget(radioButton);
        }
    }
}

void TestWindow::onButtonNextClicked()
{
    if (this->currentQuestionIndex < tests.size())
    {
        // Check the selected answer
        const TestData& currentQuestion = tests.at(currentQuestionIndex);
        int correctCount = 0;
        int totalAnswers = currentQuestion.correctAnswers.size();

        for (int i = 0; i < answersLayout->count(); ++i)
        {
            QCheckBox* radioButton = qobject_cast<QCheckBox*>(answersLayout->itemAt(i)->widget());

            if (radioButton && radioButton->isChecked())
            {
                if (currentQuestion.correctAnswers.contains(radioButton->text()))
                    ++correctCount;
            }
        }

        // Perform result calculation logic (you can adapt this to your specific needs)
        double result = static_cast<double>(correctCount) / totalAnswers;
        QString resultText = QString("Result for Question %1: %2%").arg(currentQuestionIndex + 1).arg(result * 100, 0, 'f', 2);
        qDebug() << resultText;

        currentQuestionIndex++;

        if (currentQuestionIndex < tests.size())
            displayQuestion();
        else
            calculateResults();
    }
}

void TestWindow::calculateResults()
{
    // Implement your result calculation logic when all questions have been processed
    // For example, display a message box with the overall result.
    QMessageBox::information(this, "Test Completed", "Test has been completed. Add your result calculation logic here.");
    close(); // Close the test window
}

TestWindow& TestWindow::getInstance(QWidget* parent, const QString& filePath)
{
    if (instance == nullptr)
        instance = new TestWindow(parent, filePath);

    return *instance;
}

void TestWindow::deleteInstance()
{
    delete this->instance;
    this->instance = nullptr;
}

TestWindow::~TestWindow()
{
    delete this->ui;
    this->ui = nullptr;
}
