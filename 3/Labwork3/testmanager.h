#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QString>

#include "testdata.h"

class TestManager
{
public:

    enum Option
    {
        NEXT,
        PREVIOUS
    };

    static TestManager& getInstance();

    void readTests(const QString& filePath);
    TestData& getTest(const TestManager::Option);

private:
    TestManager();

    int index;
    QList<TestData> tests;
};

#endif // TESTMANAGER_H
