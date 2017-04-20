#ifndef VARPARSER_H
#define VARPARSER_H

// вычленение переменных и их параметров из kon файла
// включая структуры, массивы, указатели

#include <QStringList>
#include <QMultiHash>
#include <QVector>
#include <QHash>

class VarParser
{
    QStringList dataBlock;
    QString inpFileName;    // исходнфй kon файл
    QHash<QString,int> mapOfVars;   // данные из map файла: имя - адрес

    void getVarsBlock();    // формирование dataBlock из содержимого #DATA исходного файла
    void removeComments(void);  // удаление комментариев
    void treatDefines(void);    // обработка define
    void searchVars(void);      // поиск переменных
    void searchStructures(void);    // поиск структур
    bool buildXML(void);    // генерация xml файла с описанием структур, массивов, переменных
    static int idNum;   // идентификатор полей для построения xml файла с описанием данных
    bool readMapFile(void); // чтение и разбор map файла



    // встроенный класс для фундаментальных типов данных (char, int, ...)
    class FundamentalType {
        int id;
        QString name;
        int size;

    public:
        FundamentalType();
        int getId() const;
        void setId(int value);
        QString getName() const;
        void setName(const QString &value);
        int getSize() const;
        void setSize(int value);
    };

    // класс для представления переменной
    class Variable {
        int id;
        QString name;
        int type;   // ссылка на идентификатор типа (может быть фунд. типом, массивом, структурой)
        int address;
        QString memType;

    public:
        Variable();
        int getId() const;
        void setId(int value);
        QString getName() const;
        void setName(const QString &value);
        int getType() const;
        void setType(int value);
        int getAddress() const;
        void setAddress(int value);
        QString getMemType() const;
        void setMemType(const QString &value);
    };

    // Описание структуры
    class Structure {
        int id;
        QVector<int> members;   // идентификаторы полей структуры
        QString name;
        int size;

    public:
        Structure();
        int getId() const;
        void setId(int value);
        QVector<int> getMembers() const;
        void setMembers(const QVector<int> &value);
        QString getName() const;
        void setName(const QString &value);
        int getSize() const;
        void setSize(int value);
    };

    // поле структуры
    class Field {
        int id;
        QString name;
        int type;   // идентификатор типа
        int offset; // смещение относительно базового адреса структуры

    public:
        Field();
        int getId() const;
        void setId(int value);
        QString getName() const;
        void setName(const QString &value);
        int getType() const;
        void setType(int value);
        int getOffset() const;
        void setOffset(int value);
    };

    // описание массива
    class Array {
        int id;
        int type;
        int size;   // размер памяти, занимаемый массивом
        int cnt;    // число элементов массива

    public:
        Array();
        int getId() const;
        void setId(int value);
        int getType() const;
        void setType(int value);
        int getSize() const;
        void setSize(int value);
        int getCnt() const;
        void setCnt(int value);
    };

    Array* addArray(const QVector<int> &dimension, int baseTypeID);

    QVector<FundamentalType*> fundTypes;
    QVector<Variable*> variables;
    QVector<Array*> arrays;
    QVector<Field*> fields;
    QVector<Structure*> structs;

    void addStruct(const QString &name, const QString &body, const QString &vars);
    void addStructVar(const QString &structName, const QString &varName);
    void createFundTypes(void);
    Array* checkArray(const QString &varDef, int basetype);
    void clearVarTree(void);

public:
    explicit VarParser(const QString &fName);
    bool createXML(void);   // формирование выходного XML файла
    // поиск адресов переменных, в которых хранятся номера тек. ситуаций процессов
    static bool readSitNum(QVector<int> &addr, QVector<int> &prNum);
    static bool readEmemAddr(int &addr, int &count);
    static bool readDisplVars(QStringList &names, QVector<int> &addr, QStringList &types);
    static bool readExchangeBufs(QStringList &names, QVector<int> &addr);
    static bool readModbusVars(QStringList &names, QVector<int> &addr);
    ~VarParser();
};

#endif // VARPARSER_H
