#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QLabel>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include "testquestion.h"

#define CREATE_GROUP_BOX(groupBoxName, groupBoxButtons, buttonCount, x, y, w, h) \
    QGroupBox* groupBoxName = new QGroupBox(this); \
    groupBoxName->setGeometry(x, y, w, h); \
    groupBoxName->setVisible(false); \
    groupBoxName->setFlat(true); \
    groupBoxButtons.clear(); \
    for (int i = 0; i < buttonCount; ++i) { \
        QPushButton* button = new QPushButton(groupBoxName); \
        button->setGeometry(10, 20 + i * 40, 120, 30); \
        button->setVisible(false); \
        groupBoxButtons.append(button); \
    } \

#define DELETE_GROUP_BOX(groupBoxName, groupBoxButtons) \
    qDeleteAll(groupBoxButtons); \
    groupBoxButtons.clear(); \
    delete groupBoxName; \
    groupBoxName = nullptr; \


QT_BEGIN_NAMESPACE
namespace Ui { class TestWindow; }
QT_END_NAMESPACE

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget* parent = nullptr, const QString& filePath = QString());
    ~TestWindow();

private slots:
    void onButtonNextClicked();

private:
    Ui::TestWindow* ui;
    QLabel* labelQuestion;
    QPushButton* buttonNext;

    int questionIndex;
    void checkAnswers();
    void displayQuestion();
    QVector<TestQuestion> questions;
};

#endif // TESTWINDOW_H
