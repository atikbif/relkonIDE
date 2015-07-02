#ifndef VARITEM_H
#define VARITEM_H

// параметры переменной для отладчика
// все данные представляются в виде дерева переменных

#include <QObject>
#include <QString>
#include <QDateTime>

class VarItem : public QObject
{
    Q_OBJECT
    QString dataType;   // int, char, struct, array, ...
    int memType;        // RAM, FRAM, CLOCK, USER, ...
    int priority;       // приоритет при опросе контроллера - влияет на частоту опроса
    int memAddress;
    QString name;
    QString value;      // в текстовом виде т.к. могут быть как целые значения так и с плавающей точкой
    QDateTime timeLabel;    // метка времени переменной
    int quality;        // качество связи

public:
    explicit VarItem(QObject *parent = 0);
    QString getName() const {return name;}
    ~VarItem();

signals:

public slots:
};

#endif // VARITEM_H
