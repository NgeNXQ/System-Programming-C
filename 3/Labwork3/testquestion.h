#ifndef TESTQUESTION_H
#define TESTQUESTION_H

#include <QString>
#include <QVector>

class TestQuestion
{
public:
    TestQuestion() = default;

    TestQuestion(const QString& questionText);
    void addAnswer(const QString& answerText, bool isCorrect);

    const QString& getQuestionText() const;
    const QVector<QString>& getAnswers() const;
    const QVector<bool>& getCorrectAnswers() const;

private:
    QString questionText;
    QVector<QString> answers;
    QVector<bool> correctAnswers;
};

#endif // TESTQUESTION_H
