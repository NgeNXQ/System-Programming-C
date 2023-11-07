#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow(void);

private slots:
    void onButtonLoadTestClicked(void);

private:
    Ui::MainWindow* ui;
    QPushButton* buttonLoadTest;
};

#endif // MAINWINDOW_H
