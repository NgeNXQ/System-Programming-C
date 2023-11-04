#include "mainwindow.h"
#include "ui_mainwindow.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
=======
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setWindowTitle("App 1");
    setGeometry(100, 100, 200, 200);
    setMinimumSize(200, 200);

    outputField = new QTextEdit("Some text here.", this);
    outputField->setGeometry(10, 10, 180, 150);
    outputField->setReadOnly(true);

    inputField = new QLineEdit(this);
    inputField->setGeometry(10, 170, 140, 20);

    QPushButton *okButton = new QPushButton("OK", this);
    okButton->setGeometry(155, 170, 35, 20);
    connect(okButton, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::handleButton()
{
    outputField->setText(inputField->text());
    inputField->clear();
>>>>>>> Stashed changes
=======
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
>>>>>>> Stashed changes
}

MainWindow::~MainWindow()
{
    delete ui;
}

