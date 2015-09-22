#include "displaywidget.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(100,100);
}

DisplayWidget::~DisplayWidget()
{

}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void DisplayWidget::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event)
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.save();

    QRect rect = event->rect();
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::red);
    painter.setPen(pen);
    painter.drawRect(rect);

    painter.restore();
}

