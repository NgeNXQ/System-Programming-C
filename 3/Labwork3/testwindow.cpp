//#include "testwindow.h"
#include "ui_testwindow.h"

#include <QFile>
#include <QLabel>
#include <QIODevice>
#include <QGroupBox>
#include <QLayoutItem>
#include <QPushButton>
#include <QMessageBox>

TestWindow::TestWindow(QWidget* parent, const QString& filePath) : QDialog(parent), ui(new Ui::TestWindow)
{
    const int TEST_WINDOW_WIDTH = 500;
    const int TEST_WINDOW_HEIGHT = 500;

    this->ui->setupUi(this);

    this->setWindowTitle("Питання № ТЕСТ");
    this->setMinimumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);
    this->setMaximumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);

    //this->questions = TestFactory::createTestQuestionsFromFile(filePath);
    //this->displayQuestion();
}

//void TestWindow::onButtonNextClicked()
//{
//    this->checkAnswers();
//    this->questionIndex++;

//    if (questionIndex < questions.size())
//    {
//        displayQuestion();
//    }
//    else
//    {
        // All questions answered, show a summary or perform another action.
//    }
//}

//void TestWindow::displayQuestion()
//{
//    if (questionIndex < questions.size())
//    {
//        const TestQuestion &currentQuestion = this->questions[questionIndex];
//        this->labelQuestion->setText(currentQuestion.getQuestionText());

        // Populate checkboxes with answers
 //       QLayoutItem* child;
//        while ((child = ui->answersLayout->takeAt(0)) != 0)
//        {
 //           delete child->widget();
 //           delete child;
 //       }

 //       const QVector<QString> &answers = currentQuestion.getAnswers();
 //       for (int i = 0; i < answers.size(); i++) {
//            QCheckBox *checkBox = new QCheckBox(answers[i]);
//            ui->answersLayout->addWidget(checkBox);
//        }
//    }
//}

//void MainWindow::checkAnswers()
//{
//    if (currentQuestionIndex < questions.size()) {
//        const TestQuestion &currentQuestion = questions[currentQuestionIndex];
//        const QVector<bool> &correctAnswers = currentQuestion.getCorrectAnswers();
//       QVector<bool> userAnswers;
//        QList<QCheckBox*> checkBoxes = ui->answersGroup->findChildren<QCheckBox*>();
//
//        for (int i = 0; i < checkBoxes.size(); i++) {
//            userAnswers.append(checkBoxes[i]->isChecked());
//        }
//
 //       if (correctAnswers == userAnswers) {
//            // Correct answer logic here
//        } else {
 //           // Incorrect answer logic here
 //       }
 //   }
//}

TestWindow::~TestWindow()
{
    delete ui;
}
