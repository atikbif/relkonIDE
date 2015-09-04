#include "symboldata.h"

bool SymbolData::checkXY(int strNum, int pos) const
{
    if((strNum<0)||(strNum>=height)) return false;
    if((pos<0)&&(pos>=width)) return false;
    if(strNum>=data.count()) return false;
    if(pos>=data.at(strNum).count()) return false;
    return true;
}

bool SymbolData::getPixel(int strNum, int pos) const
{
    if(!checkXY(strNum,pos)) return false;
    return (data.at(strNum)).at(pos);
}

void SymbolData::setPixel(int strNum, int pos, bool value)
{
    if(!checkXY(strNum,pos)) return;
    data[strNum][pos] = value;
}

bool SymbolData::setData(const QList<QBitArray> &pixels)
{
    if(pixels.count()!=data.count()) return false;
    foreach (QBitArray pixLine, data) {
       if(pixLine.count()!=width) return false;
    }
    data = pixels;
    return true;
}

SymbolData::SymbolData(int sHeight, int sWidth, int sCode):
    height(sHeight), width(sWidth), code(sCode)
{
    for(int i=0;i<height;i++) {
        QBitArray pixelLine;
        pixelLine.fill(false,width);
        data += pixelLine;
    }
}

const QList<QBitArray> SymbolData::getData() const
{
    return data;
}

int SymbolData::getHeight() const
{
    return height;
}

int SymbolData::getWidth() const
{
    return width;
}

int SymbolData::getCode() const
{
    return code;
}

SymbolData::~SymbolData()
{

}

