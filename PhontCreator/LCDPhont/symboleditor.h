#ifndef SYMBOLEDITOR_H
#define SYMBOLEDITOR_H

#include <QWidget>
#include "symboldata.h"
#include <QModelIndex>

class SymbolEditor : public QWidget
{
    Q_OBJECT
    SymbolData* sData;
    int width,height;
    static const int space = 5;
public:
    int getHeight(void) const {return height;}
    int getWidth(void) const {return width;}
    void setHeight(int value);
    void setWidth(int value);
    void setData(const SymbolData &sd);
    explicit SymbolEditor(QWidget *parent = 0);
    ~SymbolEditor();

signals:
    dataChanged(int code, SymbolData* ptr);
public slots:
    void newSymbol(const QModelIndex &index);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // SYMBOLEDITOR_H
