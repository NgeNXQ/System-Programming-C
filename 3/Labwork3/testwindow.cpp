#include <QPair>
#include <QTimer>
#include <QDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCoreApplication>

#include "testwindow.h"
#include "ui_testwindow.h"

#include "testdata.h"
#include "testmanager.h"

TestWindow::TestWindow(QWidget* parent, const QString& filePath) : QDialog(parent), ui(new Ui::TestWindow)
{
    const int TEST_WINDOW_WIDTH = 500;
    const int TEST_WINDOW_HEIGHT = 500;

    const int BUTTON_WIDTH = 100;
    const int BUTTON_HEIGHT = 50;
    const int BUTTON_OFFSET = 100;

    this->ui->setupUi(this);

    this->setMinimumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);
    this->setMaximumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);

    this->timer = new QTimer(this);
    this->layout = new QVBoxLayout(this);
    this->labelQuestion = new QLabel(this);
    this->buttonNext = new QPushButton(this);
    this->buttonPrevious = new QPushButton(this);

    this->ui->verticalLayout->addLayout(this->layout);

    this->labelQuestion->setWordWrap(true);
    this->labelQuestion->setFont(QFont(this->labelQuestion->font().family(), 14));

    this->buttonPrevious->setGeometry(0, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    this->buttonNext->setGeometry(TEST_WINDOW_WIDTH - BUTTON_OFFSET, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);

    this->buttonNext->setText("Далі");
    this->buttonNext->setFont(QFont(this->buttonNext->font().family(), 12));

    this->buttonPrevious->setText("Назад");
    this->buttonPrevious->setFont(QFont(this->buttonPrevious->font().family(), 12));

    connect(this->timer, &QTimer::timeout, this, &TestWindow::onTimerTimeout);
    connect(this->buttonNext, &QPushButton::clicked, this, &TestWindow::onButtonNextClicked);
    connect(this->buttonPrevious, &QPushButton::clicked, this, &TestWindow::onButtonPreviousClicked);

    try
    {
        TestManager::getInstance().loadTests(filePath);

        if (TestManager::getInstance().getTimeLimit() > 0)
        {
            const int MILLISECONDS_IN_MINUTE = 1000;
            this->timer->setInterval(TestManager::getInstance().getTimeLimit() * MILLISECONDS_IN_MINUTE);
            this->timer->start();
        }

        this->testIndex = 0;
        this->displayTest(testIndex);
    }
    catch (const std::runtime_error& ex)
    {
        QMessageBox::critical(this, "Помилка", QString("Не вдалося завантажити тести: %1").arg(ex.what()));
        QCoreApplication::quit();
    }
}

void TestWindow::displayTest(const int index)
{
    if (index >= 0 && index < TestManager::getInstance().getTestsCount())
    {
        this->deleteTestUI();

        TestData test = TestManager::getInstance().getTest(testIndex);

        this->labelQuestion->setText(test.question);
        this->layout->addWidget(this->labelQuestion);

        for (QPair<QPair<QString, bool>, bool>& answer : test.answers)
        {
            QCheckBox* checkBox = new QCheckBox(answer.first.first);
            checkBox->setFont(QFont(checkBox->font().family(), 14));
            checkBox->setChecked(answer.second);
            this->layout->addWidget(checkBox);
            connect(checkBox, &QCheckBox::toggled, this, [=, &answer](bool checked) { answer.second = checked; });
        }

        this->layout->addStretch();
        this->adjustSize();

        TestManager::getInstance().updateTestResults(index, test);
    }
    else
    {
        QMessageBox::critical(this, "Помилка", "Неправильний індекс тесту.");
        QCoreApplication::quit();
    }
}

void TestWindow::deleteTestUI(void) const
{
    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr)
    {
        if (item->widget() && item->widget() != this->labelQuestion)
            delete item->widget();

        delete item;
    }
}

void TestWindow::onTimerTimeout(void)
{
    this->timer->stop();
    QMessageBox::information(this, "Результат", QString("Total Result: %1").arg(TestManager::getInstance().calculateTestTotalResults()));
    QCoreApplication::quit();
}

void TestWindow::onButtonNextClicked(void)
{
    if (this->testIndex + 1 < TestManager::getInstance().getTestsCount())
    {
        this->displayTest(++this->testIndex);
    }
    else
    {
        if (QMessageBox::question(this, "Завершення тесту", "Бажаєте завершити тест?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
        {
            QMessageBox::information(this, "Результат", QString("Total Result: %1").arg(TestManager::getInstance().calculateTestTotalResults()));
            QCoreApplication::quit();
        }
    }
}

void TestWindow::onButtonPreviousClicked(void)
{
    if (this->testIndex > 0)
        this->displayTest(--this->testIndex);
}

TestWindow::~TestWindow(void)
{
    this->deleteTestUI();

    delete this->ui;
    this->ui = nullptr;

    delete this->timer;
    this->timer = nullptr;

    delete this->layout;
    this->layout = nullptr;

    delete this->buttonNext;
    this->buttonNext = nullptr;

    delete this->labelQuestion;
    this->labelQuestion = nullptr;

    delete this->buttonPrevious;
    this->buttonPrevious = nullptr;
}
