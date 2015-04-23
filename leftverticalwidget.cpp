#include "leftverticalwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include "linenumberswidget.h"
#include "foldingwidget.h"


LeftVerticalWidget::LeftVerticalWidget(QWidget *parent): QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* w1 = new LineNumbersWidget();
    QWidget *w2 = new FoldingWidget();
    connect(static_cast<FoldingWidget*>(w2),SIGNAL(toggleFolding(QString,int)),this,SLOT(getSignalFromChild(QString,int)));
    wList += w1;
    wList += w2;

    layout->setContentsMargins(0,2,0,2);

    unsigned int width=2;
    foreach (QWidget* w, wList) {
       width+=1+w->sizeHint().width();
       layout->addWidget(w);
    }
    resize(width,0);

    layout->setSpacing(1);
    if(wList.count()) layout->setStretchFactor(wList.at(0),1);
    setLayout(layout);
}

void LeftVerticalWidget::updateData(const QString &label, const QList<int> inp)
{
    foreach(QWidget *w, wList) {
        InpDataInterface *inpI = dynamic_cast<InpDataInterface*>(w);
        if(inpI) inpI->updateData(label,inp);
    }
}

void LeftVerticalWidget::getSignalFromChild(QString code, int value)
{
    emit sendValue(code, value);
}



