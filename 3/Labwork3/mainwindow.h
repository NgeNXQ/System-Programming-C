#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< Updated upstream
=======
#include <QLineEdit>
#include <QTextEdit>
>>>>>>> Stashed changes

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
<<<<<<< Updated upstream
};
=======
    QLineEdit *inputField;
    QTextEdit *outputField;

private slots:
    void handleButton();
};

>>>>>>> Stashed changes
#endif // MAINWINDOW_H
