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

    const int LABEL_TIMER_RIGHT_OFFSET = 15;
    const int LABEL_TIMER_BOTTOM_OFFSET = 45;

    this->ui->setupUi(this);

    this->setMinimumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);
    this->setMaximumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);

    this->timerTest = new QTimer(this);
    this->labelTimer = new QLabel(this);
    this->timerMinute = new QTimer(this);
    this->layout = new QVBoxLayout(this);
    this->labelQuestion = new QLabel(this);
    this->buttonNext = new QPushButton(this);
    this->buttonPrevious = new QPushButton(this);

    this->ui->verticalLayout->addLayout(this->layout);

    this->labelTimer->setWordWrap(true);
    this->labelTimer->setFont(QFont(this->labelQuestion->font().family(), 14));

    this->labelTimer->move(TEST_WINDOW_WIDTH / 2 - LABEL_TIMER_RIGHT_OFFSET,
                           TEST_WINDOW_HEIGHT - LABEL_TIMER_BOTTOM_OFFSET);

    this->labelQuestion->setWordWrap(true);
    this->labelQuestion->setFont(QFont(this->labelQuestion->font().family(), 14));

    this->buttonPrevious->setGeometry(0, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    this->buttonNext->setGeometry(TEST_WINDOW_WIDTH - BUTTON_OFFSET, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);

    this->buttonNext->setText("Далі");
    this->buttonNext->setFont(QFont(this->buttonNext->font().family(), 12));

    this->buttonPrevious->setText("Назад");
    this->buttonPrevious->setFont(QFont(this->buttonPrevious->font().family(), 12));

    connect(this->timerTest, &QTimer::timeout, this, &TestWindow::onTimerTestTimeout);
    connect(this->timerMinute, &QTimer::timeout, this, &TestWindow::onTimerMinuteTimeout);
    connect(this->buttonNext, &QPushButton::clicked, this, &TestWindow::onButtonNextClicked);
    connect(this->buttonPrevious, &QPushButton::clicked, this, &TestWindow::onButtonPreviousClicked);

    try
    {
        TestManager::getInstance().loadTests(filePath);

        if (TestManager::getInstance().getTimeLimit() > 0)
        {
            this->timerTest->setInterval(TestManager::getInstance().getTimeLimit());

            const int MILLISECONDS_IN_SECOND = 1000;
            this->timerMinute->setInterval(MILLISECONDS_IN_SECOND);

            this->timerTest->start();
            this->timerMinute->start();
        }

        this->testIndex = 0;
        this->displayTest(this->testIndex);
    }
    catch (const std::runtime_error& ex)
    {
        QMessageBox::critical(this, "Помилка", QString("Не вдалося завантажити тести: %1").arg(ex.what()));
        QCoreApplication::quit();
    }
}

void TestWindow::stopTest(void)
{
    this->timerTest->stop();
    this->timerMinute->stop();

    QMessageBox::information(this, "Результат", QString("Остаточний результат: %1").arg(QString::number(TestManager::getInstance().calculateTestTotalResults(), 'f', 1)));
    QCoreApplication::quit();
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

void TestWindow::onTimerTestTimeout(void)
{
    this->stopTest();
}

void TestWindow::onTimerMinuteTimeout(void)
{
    const int SECONDS_IN_MINUTE = 60;
    const int MILLISECONDS_IN_SECOND = 1000;

    const int minutesLeft = this->timerTest->remainingTime() / MILLISECONDS_IN_SECOND / SECONDS_IN_MINUTE;
    const int secondsLeft = this->timerTest->remainingTime() / MILLISECONDS_IN_SECOND % SECONDS_IN_MINUTE;

    QString minutesLeftString = (minutesLeft < 10) ? "0" + QString::number(minutesLeft) : QString::number(minutesLeft);
    QString secondsLeftString = (secondsLeft < 10) ? "0" + QString::number(secondsLeft) : QString::number(secondsLeft);

    if (minutesLeft == 0)
        minutesLeftString = "0";

    if (secondsLeft == 0)
        secondsLeftString = "0";

    this->labelTimer->setText(minutesLeftString + ':' + secondsLeftString);

    this->timerMinute->stop();
    this->timerMinute->start();
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
            this->stopTest();
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

    delete this->layout;
    this->layout = nullptr;

    delete this->timerTest;
    this->timerTest = nullptr;

    delete this->buttonNext;
    this->buttonNext = nullptr;

    delete this->labelTimer;
    this->labelTimer = nullptr;

    delete this->timerMinute;
    this->timerMinute = nullptr;

    delete this->labelQuestion;
    this->labelQuestion = nullptr;

    delete this->buttonPrevious;
    this->buttonPrevious = nullptr;
}
