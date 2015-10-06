#ifndef PULTVARDEFINITION_H
#define PULTVARDEFINITION_H

#include <QString>

class PultVarDefinition
{
    QString pattern;
    QString name;
    QString dataType;
    int strNum;
    int subStrNum;
    int posInStr;
    bool isEditable;
    bool forceSign;
    bool isEEVar;
    int EEposInSettingsTable;
public:
    PultVarDefinition();
    ~PultVarDefinition();
    QString getPattern() const;
    void setPattern(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getDataType() const;
    void setDataType(const QString &value);
    int getStrNum() const;
    void setStrNum(int value);
    int getSubStrNum() const;
    void setSubStrNum(int value);
    int getPosInStr() const;
    void setPosInStr(int value);
    bool getIsEditable() const;
    void setIsEditable(bool value);
    bool getForceSign() const;
    void setForceSign(bool value);
    bool getIsEEVar() const;
    void setIsEEVar(bool value);
    int getEEposInSettingsTable() const;
    void setEEposInSettingsTable(int value);
};

#endif // PULTVARDEFINITION_H
