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
    TestWindow(QWidget*, const QString&);
    ~TestWindow(void);

private slots:
    void onButtonNextClicked();
    void onButtonPreviousClicked();

private:
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
