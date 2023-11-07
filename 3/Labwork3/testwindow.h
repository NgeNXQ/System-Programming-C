#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "testdata.h"

namespace Ui { class TestWindow; }

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    static TestWindow& getInstance(QWidget* parent = nullptr, const QString& filePath = QString());

private slots:
    void deleteInstance() const;
    void onButtonNextClicked() const;
    void onButtonPreviousClicked() const;

private:
    TestWindow(const TestWindow&) = delete;
    explicit TestWindow(QWidget* parent = nullptr, const QString& filePath = QString());

    ~TestWindow(void);

    TestWindow& operator=(const TestWindow&) = delete;

    static TestWindow* instance;

    Ui::TestWindow* ui;
    QVBoxLayout* layout;
    QLabel* labelQuestion;
    QPushButton* buttonNext;
    QPushButton* buttonPrevious;

    void displayTest(TestData&);
};

#endif // TESTWINDOW_H
