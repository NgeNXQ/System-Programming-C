#include <QPair>
#include <QDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "testmanager.h"
#include "testwindow.h"
#include "ui_testwindow.h"
#include "testdata.h"
#include "testmanager.h"

TestWindow* TestWindow::instance = nullptr;

TestWindow::TestWindow(QWidget* parent, const QString& filePath) : QDialog(parent), ui(new Ui::TestWindow), currentTestIndex(0)
{
    const int BUTTON_OFFSET = 100;
    const int TEST_WINDOW_WIDTH = 500;
    const int TEST_WINDOW_HEIGHT = 500;
    const int BUTTON_WIDTH = 100;
    const int BUTTON_HEIGHT = 50;

    this->ui->setupUi(this);

    this->setMinimumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);
    this->setMaximumSize(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT);

    this->layout = new QVBoxLayout(this);
    this->labelQuestion = new QLabel(this);
    this->buttonNext = new QPushButton(this);
    this->buttonPrevious = new QPushButton(this);

    this->ui->verticalLayout->addLayout(this->layout);
    this->ui->verticalLayout->addWidget(this->labelQuestion);

    this->labelQuestion->setWordWrap(true);
    this->labelQuestion->setFont(QFont(this->labelQuestion->font().family(), 14));

    this->buttonPrevious->setGeometry(0, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    this->buttonNext->setGeometry(TEST_WINDOW_WIDTH - BUTTON_OFFSET, TEST_WINDOW_HEIGHT - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);

    this->buttonNext->setText("Далі");
    this->buttonNext->setFont(QFont(this->buttonNext->font().family(), 12));

    this->buttonPrevious->setText("Назад");
    this->buttonPrevious->setFont(QFont(this->buttonPrevious->font().family(), 12));

    connect(this, &TestWindow::destroyed, this, &TestWindow::deleteInstance);
    connect(this->buttonNext, &QPushButton::clicked, this, &TestWindow::onButtonNextClicked);
    connect(this->buttonPrevious, &QPushButton::clicked, this, &TestWindow::onButtonPreviousClicked);

    TestManager::getInstance().readTests(filePath);
    //this->displayTest(TestManager::getInstance().getTests()[0]);
}

void TestWindow::displayTest(const TestData& test)
{
    this->labelQuestion->setText(test.question);

    QLayoutItem* item;

    while ((item = layout->takeAt(0)) != nullptr)
    {
        if (item->widget())
            delete item->widget();

        delete item;
    }

    for (const QPair<const QPair<const QString&, const bool>, bool>& answer : test.answers)
    {
        QCheckBox* checkBox = new QCheckBox(answer.first.first);
        checkBox->setFont(QFont(checkBox->font().family(), 14));
        this->layout->addWidget(checkBox);
    }

    this->layout->addStretch();
    this->adjustSize();
}

void TestWindow::onButtonNextClicked(void)
{
    if (currentTestIndex < TestManager::getInstance().getTests().size() - 1)
    {
        userAnswers[currentTestIndex] = 0;
        currentTestIndex++;
        displayTest(TestManager::getInstance().getTests()[currentTestIndex]);
    }
}

void TestWindow::onButtonPreviousClicked(void)
{
    if (currentTestIndex > 0)
    {
        userAnswers[currentTestIndex] = 0;
        currentTestIndex--;
        displayTest(TestManager::getInstance().getTests()[currentTestIndex]);
    }
}

TestWindow& TestWindow::getInstance(QWidget* parent, const QString& filePath)
{
    if (instance == nullptr)
        instance = new TestWindow(parent, filePath);

    return *instance;
}

void TestWindow::deleteInstance(void) const
{
    delete this->instance;
    this->instance = nullptr;
}

TestWindow::~TestWindow(void)
{
    delete this->ui;
    this->ui = nullptr;
}
