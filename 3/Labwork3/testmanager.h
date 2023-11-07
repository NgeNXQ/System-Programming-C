#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QString>

#include "testdata.h"

class TestManager
{
public:
    static TestManager& getInstance();

    void loadTests(const QString& filePath);
    QList<TestData> getTests();

private:
    TestManager(); // Private constructor to prevent external instantiation
    QList<TestData> tests;
};

#endif // TESTMANAGER_H
