#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QList>
#include <QLabel>
#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>

#include "testdata.h"

namespace Ui { class TestWindow; }

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    static TestWindow& getInstance(QWidget* parent = nullptr, const QString& filePath = QString());

private slots:
    void onButtonNextClicked();
    void deleteInstance();

private:
    static TestWindow* instance;
    TestWindow(const TestWindow&) = delete;
    TestWindow& operator=(const TestWindow&) = delete;

    explicit TestWindow(QWidget* parent = nullptr, const QString& filePath = QString());
    ~TestWindow();

    Ui::TestWindow* ui;
    QLabel* labelQuestion;
    QList<TestData> tests;
    QPushButton* buttonNext;
    QVBoxLayout* answersLayout;

    int currentQuestionIndex;

    void loadTest(const QString& filePath);
    void displayQuestion();
    void calculateResults();
};

#endif // TESTWINDOW_H
