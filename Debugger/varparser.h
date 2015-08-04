#ifndef VARPARSER_H
#define VARPARSER_H

// вычленение переменных и их параметров из kon файла
// включая структуры, массивы, указатели

#include <QStringList>
#include <QMultiHash>
#include <QVector>

class VarParser
{
    QStringList dataBlock;
    QString inpFileName;

    void getVarsBlock();
    void removeComments(void);
    void treatDefines(void);
    void searchVars(void);
    void searchStructures(void);
    bool buildXML(void);
    static int idNum;


    class FundamentalType {
        int id;
        QString name;
        int size;

    public:
        int getId() const;
        void setId(int value);
        QString getName() const;
        void setName(const QString &value);
        int getSize() const;
        void setSize(int value);
    };

    class Variable {
        int id;
        QString name;
        int type;
        int address;
        QString memType;

    public:
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

    class Structure {
        int id;
        QVector<int> members;
        QString name;
        int size;

    public:
        int getId() const;
        void setId(int value);
        QVector<int> getMembers() const;
        void setMembers(const QVector<int> &value);
        QString getName() const;
        void setName(const QString &value);
        int getSize() const;
        void setSize(int value);
    };

    class Field {
        int id;
        QString name;
        int type;
        int offset;

    public:
        int getId() const;
        void setId(int value);
        QString getName() const;
        void setName(const QString &value);
        int getType() const;
        void setType(int value);
        int getOffset() const;
        void setOffset(int value);
    };

    class Array {
        int id;
        int type;
        int size;
        int cnt;

    public:
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

public:
    explicit VarParser(const QString &fName);
    bool createXML(void);
    ~VarParser();
};

#endif // VARPARSER_H
