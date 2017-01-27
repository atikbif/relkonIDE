#ifndef PRBUILDER_H
#define PRBUILDER_H

#include <QObject>
#include <QStringList>
#include "LCD/display.h"

class PrBuilder : public QObject
{
    Q_OBJECT
    bool newBuild = false;
    QStringList konFile;
    int convertStrNum(int cStrNum);
    const Display& lcd;
    QString plcType;

    void removeBuildFiles(const QString & prPath, const QString &prName);
public:
    explicit PrBuilder(const Display& d, QObject *parent = 0);
signals:
    void printMessage(const QString &str);
    void buildIsFinished(void);
    void buildIsOk(void);
public slots:
    void buildRequest(QString prPath, QString prName);
    void setFileText(QStringList str, QString plc);
};

#endif // PRBUILDER_H
