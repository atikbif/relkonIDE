#include "searchdata.h"


QString SearchData::getSearchText() const
{
    return searchText;
}

void SearchData::setSearchText(const QString &value)
{
    searchText = value;
}

QString SearchData::getReplaceText() const
{
    return replaceText;
}

void SearchData::setReplaceText(const QString &value)
{
    replaceText = value;
}

int SearchData::getSearchRegion() const
{
    return searchRegion;
}

void SearchData::setSearchRegion(int value)
{
    switch(value) {
    case FORWARD:
    case BACKWARD:
        searchRegion = value;
        break;
    default:
        searchRegion = FORWARD;
        break;
    }
}

bool SearchData::getWholeWord() const
{
    return wholeWord;
}

void SearchData::setWholeWord(bool value)
{
    wholeWord = value;
}

bool SearchData::getCaseSensivity() const
{
    return caseSensivity;
}

void SearchData::setCaseSensivity(bool value)
{
    caseSensivity = value;
}
SearchData::SearchData():searchText(""),replaceText(""),
    searchRegion(FORWARD),wholeWord(false),caseSensivity(false)
{

}

