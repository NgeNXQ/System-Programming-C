#include <QPair>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "testdata.h"
#include "testmanager.h"

TestManager::TestManager() {}

TestManager& TestManager::getInstance()
{
    static TestManager instance;
    return instance;
}

void TestManager::readTests(const QString& filePath)
{
    QString line;
    TestData test;
    QFile file(filePath);
    QTextStream stream(&file);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!stream.atEnd())
        {
            line = stream.readLine().trimmed();

            if (line.startsWith("[Q]"))
            {
                test.question = line.mid(3).trimmed();
            }
            else if (line.startsWith("[C]") || line.startsWith("[I]"))
            {
                QPair<QString, bool> answer(line.mid(3).trimmed(), line.startsWith("[C]"));
                test.answers.append(QPair<QPair<QString, bool>, bool>(answer, false));
            }
            else if (line.isEmpty())
            {
                tests.append(test);
                test.question.clear();
                test.answers.clear();
            }
        }

        if (!test.question.isEmpty())
            tests.append(test);

        file.close();
    }
    else
        throw std::runtime_error("Не вдалося прочитати вміст файлу.");
}

TestData& TestManager::getTest(const TestManager::Option option)
{
    switch (option)
    {
    case TestManager::Option::NEXT:
    {
        if (this->index + 1 < this->tests.size())
            return this->tests[++this->index];
        else
            return -1;
    }
    case TestManager::Option::PREVIOUS:
    {
        if (this->index - 1 > 0)
            return this->tests[--this->index];
        else
            return nullptr;
    }
    }
}
