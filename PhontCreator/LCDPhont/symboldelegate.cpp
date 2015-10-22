#include "symboldelegate.h"
#include <QPainter>
#include "symboldata.h"
#include <QImage>
#include <QRgb>

SymbolDelegate::SymbolDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

SymbolDelegate::~SymbolDelegate()
{

}

void SymbolDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    if(option.state & QStyle::State_Selected){
        painter->setPen(Qt::red);
    }

    void *v = index.data().value<void*>();
    SymbolData* s = static_cast<SymbolData*>(v);
    QImage image(s->getWidth(),s->getHeight(),QImage::Format_Mono);
    image.fill(Qt::black);
    for(int i=0;i<s->getHeight();i++) {
        for(int j=0;j<s->getWidth();j++) {
            if(s->getPixel(i,j)) image.setPixel(j,i,0);
        }
    }

    if(s!=nullptr) {
        painter->drawText(option.rect,Qt::AlignCenter,QString::number(s->getCode()));
        image = image.scaledToHeight(option.rect.height()-1,Qt::SmoothTransformation);
        painter->drawImage(option.rect.topLeft(),image);
    }
    painter->restore();
}

