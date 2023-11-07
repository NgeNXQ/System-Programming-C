#include <QPair>
#include <QDebug>
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
                for (const QPair<const QPair<const QString, const bool>, bool>& answer : test.answers)
                    qDebug() << "Added test to the list" << answer.first.first;

                tests.append(test);
                test.question.clear();
                test.answers.clear();
            }
        }

        if (!test.question.isEmpty())
        {
            for (const QPair<const QPair<const QString, const bool>, bool>& answer : test.answers)
                qDebug() << "Added test to the list" << answer.first.first;

            tests.append(test);
        }

        file.close();
    }
    else
        throw std::runtime_error("Не вдалося прочитати вміст файлу.");
}

QList<TestData> TestManager::getTests()
{
    return tests;
}
