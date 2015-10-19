#include "request.h"


QByteArray Request::getAnswerData() const
{
    return answerData;
}

void Request::setAnswerData(const QByteArray &value)
{
    answerData = value;
}
Request::Request():netAddr(1),memAddr(0),dataNumber(0)
{
    
}

Request::~Request()
{
    
}

