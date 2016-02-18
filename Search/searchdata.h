#ifndef SEARCHDATA_H
#define SEARCHDATA_H

// класс с информацией о параметрах поискового запроса

#include <QString>

class SearchData
{
    QString searchText;
    QString replaceText;
    int searchRegion;
    bool wholeWord;
    bool caseSensivity;
    bool round;
public:
    enum {FORWARD,BACKWARD};
    SearchData();
    QString getSearchText() const;
    void setSearchText(const QString &value);
    QString getReplaceText() const;
    void setReplaceText(const QString &value);
    int getSearchRegion() const;
    void setSearchRegion(int value);
    bool getWholeWord() const;
    void setWholeWord(bool value);
    bool getCaseSensivity() const;
    void setCaseSensivity(bool value);
    bool getRoundCondition(void) const {return round;}
    void setRoundcondition(bool value) {round = value;}
};

#endif // SEARCHDATA_H
