#include "symboleditor.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

void SymbolEditor::setData(const SymbolData &sd)
{
    if(sData) delete sData;
    sData = new SymbolData(sd.getCode());
    sData->setData(sd.getData());
    repaint();
}

SymbolEditor::SymbolEditor(QWidget *parent) : QWidget(parent), sData(nullptr)
{
    setMinimumSize(100,100);
}

SymbolEditor::~SymbolEditor()
{

}

void SymbolEditor::newSymbol(const QModelIndex &index)
{
    if(!index.isValid()) return;
    QVariant v = index.data();
    SymbolData *ptr = static_cast<SymbolData*>(v.value<void*>());
    setData(*ptr);
}

void SymbolEditor::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton) return;
    if(sData!=nullptr) {
        bool fitPosX = false;
        bool fitPosY = false;
        int rectWidth = rect().width()/sData->getWidth();
        int rectHeight = rect().height()/sData->getHeight();
        int strNum=0,pos=0;
        int x = event->pos().x();
        int y = event->pos().y();
        for(int i=0;i<sData->getWidth();i++) {
            if((x>=1+i*rectWidth)&&(x<1+(i+1)*rectWidth-space)) {pos=i;fitPosY=true;break;}
        }
        for(int i=0;i<sData->getHeight();i++) {
            if((y>=1+i*rectHeight)&&(y<1+(i+1)*rectHeight-space)) {strNum=i;fitPosX=true;break;}
        }
        if(fitPosX && fitPosY) {
            bool pixValue = sData->getPixel(strNum,pos);
            sData->setPixel(strNum,pos,!pixValue);
            emit dataChanged(sData->getCode(),sData);
            repaint();
        }
    }
}

void SymbolEditor::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    QPen pen(Qt::red);
    painter.setPen(pen);

    if(sData!=nullptr) {
        int rectWidth = rect.width()/sData->getWidth();
        int rectHeight = rect.height()/sData->getHeight();
        if((rectWidth>0)&&(rectHeight>0)) {
            for(int i=0;i<sData->getHeight();i++) {
                for(int j=0;j<sData->getWidth();j++) {
                    if(sData->getPixel(i,j)) {
                        painter.setBrush(Qt::black);
                    }
                    else {
                        painter.setBrush(Qt::gray);
                    }
                    painter.drawRect(1+j*rectWidth,1+i*rectHeight,rectWidth-space,rectHeight-space);
                }
            }
        }
    }
    painter.restore();
}

