#ifndef PRBUILDER_H
#define PRBUILDER_H

#include <QObject>
#include <QStringList>

class PrBuilder : public QObject
{
    Q_OBJECT
    bool newBuild = false;
    QStringList konFile;
    int convertStrNum(int cStrNum);

    void removeBuildFiles(const QString & prPath, const QString &prName);
public:
    explicit PrBuilder(QObject *parent = 0);
signals:
    void printMessage(const QString &str);
    void buildIsFinished(void);
    void buildIsOk(void);
public slots:
    void buildRequest(QString prPath, QString prName);
    void setFileText(QStringList str);
};

#endif // PRBUILDER_H
