#ifndef FOLDINGWIDGET_H
#define FOLDINGWIDGET_H

#include <QWidget>
#include "inpdatainterface.h"

class FoldingWidget: public QWidget, public InpDataInterface
{
    Q_OBJECT
    int width;
    int cnt;
public:
    explicit FoldingWidget(QWidget *par=0);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void toggleFolding(QString,int);
};

#endif // FOLDINGWIDGET_H
