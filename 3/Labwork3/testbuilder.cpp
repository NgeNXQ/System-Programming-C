#include "TestBuilder.h"

TestBuilder::TestBuilder() {}

void TestBuilder::startNewQuestion(const QString& questionText)
{
    question = TestQuestion(questionText);
}

void TestBuilder::addAnswer(const QString& answerText, bool isCorrect)
{
    question.addAnswer(answerText, isCorrect);
}

TestQuestion TestBuilder::build()
{
    return question;
}
