#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "testwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    const int MAIN_WINDOW_WIDTH = 320;
    const int MAIN_WINDOW_HEIGHT = 125;
    const int BUTTON_LOAD_TEST_WIDTH = 150;
    const int BUTTON_LOAD_TEST_HEIGHT = 75;
    const int BUTTON_LOAD_TEST_OFFSET_X = BUTTON_LOAD_TEST_WIDTH / 2;
    const int BUTTON_LOAD_TEST_OFFSET_Y = BUTTON_LOAD_TEST_HEIGHT / 2;

    this->ui->setupUi(this);

    this->setWindowTitle("Практикум № 3");
    this->setMinimumSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    this->setMaximumSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    this->buttonLoadTest = new QPushButton(this);

    this->buttonLoadTest->setGeometry(MAIN_WINDOW_WIDTH / 2 - BUTTON_LOAD_TEST_OFFSET_X,
                                MAIN_WINDOW_HEIGHT / 2 - BUTTON_LOAD_TEST_OFFSET_Y,
                                BUTTON_LOAD_TEST_WIDTH,
                                BUTTON_LOAD_TEST_HEIGHT);

    this->buttonLoadTest->setText("Обрати тест");

    connect(this->buttonLoadTest, &QPushButton::clicked, this, &MainWindow::onButtonLoadTestClicked);
}

void MainWindow::onButtonLoadTestClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Обрати тест"), QDir::currentPath(), tr("All Files (*.txt)"));

    if (!fileName.isEmpty())
    {
        this->hide();

        //TestWindow* const testWindow = new TestWindow(this, fileName);
        //testWindow->show();
        //delete testWindow;

    }
    else
    {
        QMessageBox::critical(this, tr("Помилка!"), tr("Ви не обрали жодного файлу з тестом."));
    }
}

MainWindow::~MainWindow()
{
    delete this->ui;
    this->ui = nullptr;

    delete this->buttonLoadTest;
    this->buttonLoadTest = nullptr;
}
