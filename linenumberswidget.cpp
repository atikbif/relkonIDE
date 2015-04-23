#include "linenumberswidget.h"
#include <QPainter>
#include <QPaintEvent>

LineNumbersWidget::LineNumbersWidget(QWidget *par): QWidget(par), InpDataInterface()
{
    width=fontMetrics().width(QLatin1Char('9'))*7;
}

QSize LineNumbersWidget::sizeHint() const
{
    return QSize(width,0);
}

void LineNumbersWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush br(QColor(0xD6,0xD2,0xD2));
    painter.fillRect(event->rect(),br);

    QList<int> nums = inpData.value("lineNums");
    painter.setPen(Qt::darkGray);
    for(int i=0;i<nums.count();i++)
    {
        if(i%2) {
            painter.drawText(0, nums[i], width, fontMetrics().height(),
                                 Qt::AlignHCenter, QString::number(nums[i-1]+1));
        }
    }
}

