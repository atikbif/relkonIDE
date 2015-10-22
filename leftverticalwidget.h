#ifndef LEFTVERTICALWIDGET_H
#define LEFTVERTICALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QList>
#include <QSize>
#include "inpdatainterface.h"

class LeftVerticalWidget : public QWidget
{
    Q_OBJECT
    QMap<QString, QList<int> > inpData;
    QList<QWidget*> wList;
public:
    explicit LeftVerticalWidget(QWidget *parent=0);
    void updateData(const QString &label, const QList<int> inp);
protected slots:
    void getSignalFromChild(QString code,int value);
signals:
    void sendValue(QString, int);
};

#endif // LEFTVERTICALWIDGET_H
