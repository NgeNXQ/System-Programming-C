#ifndef TESTDATA_H
#define TESTDATA_H

#include <QList>
#include <QString>

struct TestData
{
    QString questionText;
    QList<QString> correctAnswers;
    QList<QString> incorrectAnswers;
};

#endif // TESTDATA_H
