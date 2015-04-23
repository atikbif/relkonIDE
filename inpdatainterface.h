#ifndef INPDATAWIDGET_H
#define INPDATAWIDGET_H

#include <QMap>
#include <QList>
#include <QString>

class InpDataInterface
{
protected:
    QMap<QString, QList<int> > inpData;
public:
    InpDataInterface();
    void updateData(const QString &label, const QList<int> inp);
};

#endif // INPDATAWIDGET_H
