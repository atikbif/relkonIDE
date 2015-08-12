#ifndef REQUEST_H
#define REQUEST_H

// класс данных для команды

#include <QByteArray>
#include <QHash>
#include <QString>

class Request
{
    unsigned int netAddr;       // сетевой адрес
    unsigned int memAddr;       // адрес в памяти
    unsigned int dataNumber;    // количество данных
    QByteArray wrData;          // массив с данными для записи
    QByteArray rdData;          // массив с прочитанными данными
    QByteArray answerData;      // необработанный ответ
    QHash<QString, QString> params;     // дополнительные параметры для расширения функционала
    QByteArray reqBody;
public:
    Request();
    void setNetAddress(int value) {netAddr=value;}
    int getNetAddress(void) const {return netAddr;}
    void setMemAddress(int value) {memAddr=value;}
    int getMemAddress(void) const {return memAddr;}
    void setDataNumber(int value) {dataNumber=value;}
    int getDataNumber(void) const {return dataNumber;}
    void setWrData(const QByteArray &wrData) {this->wrData = wrData;}
    const QByteArray& getWrData(void) const {return wrData;}
    void updateRdData(const QByteArray &rdData) {this->rdData = rdData;}
    const QByteArray& getRdData(void) const {return rdData;}
    void insParam(const QString &key, const QString &value) {params.insert(key,value);}
    bool hasKey(const QString &key) const {return params.contains(key);}
    QString getParam(const QString &key) const {return params.value(key);}
    QByteArray& getBody(void) {return reqBody;}
    ~Request();
    QByteArray getAnswerData() const;
    void setAnswerData(const QByteArray &value);
};

#endif // REQUEST_H
