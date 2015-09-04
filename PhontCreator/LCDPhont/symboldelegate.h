#ifndef SYMBOLDELEGATE_H
#define SYMBOLDELEGATE_H

#include <QStyledItemDelegate>

class SymbolDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SymbolDelegate(QObject *parent=0);
    ~SymbolDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SYMBOLDELEGATE_H
