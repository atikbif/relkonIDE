#include "patterneditorwidget.h"
#include <QPaintEvent>
#include <QPainter>

PatternEditorWidget::PatternEditorWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(100,100);
}

PatternEditorWidget::~PatternEditorWidget()
{

}

void PatternEditorWidget::paintEvent(QPaintEvent *event)
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

