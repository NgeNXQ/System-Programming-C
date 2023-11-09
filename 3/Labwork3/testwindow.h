#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui { class TestWindow; }

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    TestWindow(const TestWindow&) = delete;
    TestWindow& operator=(const TestWindow&) = delete;

    static TestWindow& getInstance(QWidget*, const QString&);

private slots:
    void deleteInstance();
    void onButtonNextClicked();
    void onButtonPreviousClicked();

private:
    explicit TestWindow(QWidget*, const QString&);
    ~TestWindow(void);

    static TestWindow* instance;

    Ui::TestWindow* ui;
    QVBoxLayout* layout;
    QLabel* labelQuestion;
    QPushButton* buttonNext;
    QPushButton* buttonPrevious;

    int testIndex;

    void displayTest(const int);
    void updateResults(const int testIndex);
};

#endif // TESTWINDOW_H
