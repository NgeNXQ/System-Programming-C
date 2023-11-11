#include <QPair>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "testdata.h"
#include "testmanager.h"
#include "testdatabuilder.h"

TestManager* TestManager::instance = nullptr;

TestManager::TestManager() { }

TestManager::~TestManager(void) { }

int TestManager::getTestsCount() const
{
    return this->tests.count();;
}

int TestManager::getTimeLimit(void) const
{
    return this->timeLimit;
}

TestManager& TestManager::getInstance(void)
{
    if (instance == nullptr)
        instance = new TestManager();

    return *instance;
}

const TestData& TestManager::getTest(const int index) const
{
    if (index >= 0 && index < this->tests.size())
        return this->tests[index];

    throw std::runtime_error("Неправильний індекс тесту.");
}

float TestManager::calculateTestTotalResults(void) const
{
    float totalScore = 0.0f;
    bool isTestCorrect = true;

    for (const TestData& test : this->tests)
    {
        for (const QPair<QPair<QString, bool>, bool>& answer : test.answers)
        {
            if (answer.first.second != answer.second)
            {
                isTestCorrect = false;
                break;
            }
        }

        if (isTestCorrect)
            ++totalScore;
    }

    return totalScore;
}

void TestManager::updateTestResults(const int index, const TestData& test)
{
    if (index >= 0 && index < this->tests.size())
        this->tests[index] = test;
    else
        throw std::runtime_error("Неправильний індекс тесту.");
}

void TestManager::loadTests(const QString& filePath)
{
    QFile file(filePath);
    QTextStream stream(&file);

    QString line;
    TestDataBuilder builder;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!stream.atEnd())
        {
            line = stream.readLine().trimmed();

            if (line.startsWith("[Q]"))
            {
                builder.setQuestion(line.mid(3).trimmed());
            }
            else if (line.startsWith("[C]"))
            {
                builder.addAnswer(line.mid(3).trimmed(), true);
            }
            else if (line.startsWith("[I]"))
            {
                builder.addAnswer(line.mid(3).trimmed(), false);
            }
            else if (line.startsWith("[T]"))
            {
                const int TIME = line.mid(3).trimmed().toInt();

                if (TIME > 0)
                    this->timeLimit = TIME;
                else
                    throw std::runtime_error("Не вдалося прочитати вміст файлу.");
            }
            else if (line.isEmpty())
            {
                this->tests.append(*(builder.getTest()));
                builder.reset();
            }
            else
            {
                throw std::runtime_error("Не вдалося прочитати вміст файлу.");
            }
        }

        if (!builder.getTest()->question.isEmpty())
            this->tests.append(*(builder.getTest()));

        file.close();
    }
    else
        throw std::runtime_error("Не вдалося прочитати вміст файлу.");
}
