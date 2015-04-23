#ifndef LINENUMBERSWIDGET_H
#define LINENUMBERSWIDGET_H

#include <QWidget>
#include "inpdatainterface.h"

class LineNumbersWidget: public QWidget, public InpDataInterface
{
    Q_OBJECT
    int width;
public:
    explicit LineNumbersWidget(QWidget *par=0);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent *event);

};

#endif // LINENUMBERSWIDGET_H
