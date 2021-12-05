#ifndef RCOMPILERINTERFACE_H
#define RCOMPILERINTERFACE_H

#include <QString>
#include <QVector>

typedef struct {
    int strNum;
    QString message;
}outMessage;

class RCompilerInterface
{
public:
    RCompilerInterface() = default;
    virtual QVector<outMessage>& getOutErrors(void) = 0;
    virtual void compile(void) = 0;
    virtual void link(void) = 0;
    virtual ~RCompilerInterface() = default;
};

#endif // RCOMPILERINTERFACE_H
