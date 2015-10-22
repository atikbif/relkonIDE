#ifndef SYMBOLEDITOR_H
#define SYMBOLEDITOR_H

#include <QWidget>
#include "symboldata.h"
#include <QModelIndex>

class SymbolEditor : public QWidget
{
    Q_OBJECT
    SymbolData* sData;
    static const int space = 2;
public:
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
