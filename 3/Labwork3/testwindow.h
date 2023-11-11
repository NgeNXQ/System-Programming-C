#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QTimer>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui { class TestWindow; }

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    TestWindow(QWidget*, const QString&);
    ~TestWindow(void);

private slots:
    void onTimerTimeout(void);
    void onButtonNextClicked(void);
    void onButtonPreviousClicked(void);

private:
    QTimer* timer;
    Ui::TestWindow* ui;
    QVBoxLayout* layout;
    QLabel* labelQuestion;
    QPushButton* buttonNext;
    QPushButton* buttonPrevious;

    int testIndex;

    void displayTest(const int);
    void deleteTestUI(void) const;
    void updateResults(const int testIndex);
};

#endif // TESTWINDOW_H
