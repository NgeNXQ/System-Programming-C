#ifndef TESTBUILDER_H
#define TESTBUILDER_H

#include "testquestion.h"

class TestBuilder
{
public:
    TestBuilder();

    void startNewQuestion(const QString& questionText);
    void addAnswer(const QString& answerText, bool isCorrect);
    TestQuestion build();

private:
    TestQuestion question;
};


#endif // TESTBUILDER_H
