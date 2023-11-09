#include <QPair>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "testdata.h"
#include "testmanager.h"

TestManager* TestManager::instance = nullptr;

TestManager& TestManager::getInstance(void)
{
    if (instance == nullptr)
        instance = new TestManager();

    return *instance;
}

TestManager::TestManager() { }

TestManager::~TestManager(void)
{
    delete instance;
    instance = nullptr;
}

int TestManager::getTestsCount() const
{
    return this->tests.count();;
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

float TestManager::calculateTestTotalResults(void) const
{
    float totalScore = 0.0f;

    int testScore;
    int testTotalCorrect;

    for (const TestData& test : this->tests)
    {
        testScore = 0;
        testTotalCorrect = 0;

        for (const QPair<QPair<QString, bool>, bool>& answer : test.answers)
        {
            if (answer.first.second)
            {
                ++testTotalCorrect;

                if (answer.second)
                    ++testScore;
            }
        }

        if (testTotalCorrect > 1)
            totalScore += static_cast<float>(testScore) / static_cast<float>(testTotalCorrect);
        else if (testTotalCorrect == 1 && testScore == 1)
            totalScore += 1.0f;
    }

    return totalScore;
}

const TestData& TestManager::getTest(const int index) const
{
    if (index >= 0 && index < this->tests.size())
        return this->tests[index];

    throw std::runtime_error("Неправильний індекс тесту.");
}
