#include "foldingwidget.h"
#include <QPainter>
#include <QPaintEvent>

FoldingWidget::FoldingWidget(QWidget *par): QWidget(par), InpDataInterface()
{
    width = fontMetrics().width(QLatin1Char('9'))*3;
    cnt=0;
}

QSize FoldingWidget::sizeHint() const
{
    return QSize(width,0);
}

void FoldingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush br(QColor(0xEA,0xE7,0xE7));
    painter.fillRect(event->rect(),br);

    QList<int> nums = inpData.value("folding");
    painter.setPen(Qt::darkGray);
    for(int i=0;i<nums.count();i++)
    {
        if(i%3==1) {
            int sqWidth = event->rect().width()*0.7;
            if(sqWidth%2) sqWidth--;
            int x1 = 2;
            int y1 = nums.at(i)+2;
            int x2 = x1+sqWidth;
            int y2 = y1+sqWidth;
            painter.drawRect(x1,y1,x2-x1,y2-y1);
            painter.drawLine(x1+2,(y1+y2)/2,x2-2,(y1+y2)/2);
            if(nums.count()>i+1) {
                if(nums.at(i+1)==0) painter.drawLine((x1+x2)/2,y1+2,(x1+x2)/2,y2-2);
            }

        }
    }
}

void FoldingWidget::mousePressEvent(QMouseEvent *event)
{
    QList<int> nums = inpData.value("folding");
    for(int i=0;i<nums.count();i++)
    {
        if(i%3==1) {
            int top = nums.at(i);
            int bottom = top + width;
            int y = event->pos().y();
            if((y>top)&&(y<bottom)) {
                emit toggleFolding("folding",nums.at(i-1));
                break;
            }
        }
    }
}
