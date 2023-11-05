#include "TestQuestion.h"

TestQuestion::TestQuestion(const QString& questionText) : questionText(questionText) {}

void TestQuestion::addAnswer(const QString& answerText, bool isCorrect)
{
    answers.push_back(answerText);
    correctAnswers.push_back(isCorrect);
}

const QString& TestQuestion::getQuestionText() const
{
    return questionText;
}

const QVector<QString>& TestQuestion::getAnswers() const
{
    return answers;
}

const QVector<bool>& TestQuestion::getCorrectAnswers() const
{
    return correctAnswers;
}
