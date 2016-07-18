#ifndef PULTVARDEFINITION_H
#define PULTVARDEFINITION_H

// описание переменной, привязанной к строке пульта

#include <QString>

class PultVarDefinition
{
    QString pattern;
    QString name;
    QString dataType;
    QString id;
    int posInStr;
    bool isEdit;
    bool forceSign;
    bool isEE;
    int EEposInSettingsTable;
    bool isItExist;
public:
    PultVarDefinition();
    ~PultVarDefinition();
    QString getPattern() const;
    void setPattern(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getDataType() const;
    void setDataType(const QString &value);
    int getPosInStr() const;
    void setPosInStr(int value);
    bool isEditable() const;
    void setEditable(bool value);
    bool getForceSign() const;
    void setForceSign(bool value);
    bool isEEVar() const;
    void setEEVar(bool value);
    int getEEposInSettingsTable() const;
    void setEEposInSettingsTable(int value);
    QString getId() const;
    void setId(const QString &value);
    bool isExist() const;
    void setExist(bool value);
    bool operator <(const PultVarDefinition &a) const {return posInStr<a.posInStr;}
};

#endif // PULTVARDEFINITION_H
