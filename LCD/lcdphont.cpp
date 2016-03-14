#include "lcdphont.h"
#include <QFile>
#include <QDataStream>

const QString LCDPhont::defName = "lcd_phont.rph";

LCDPhont::LCDPhont(const QString &fName):rowCount(0),
    columnCount(0),symbCount(0)
{
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_5_4);
            int height = 0;
            int width = 0;
            int cnt = 0;
            in >> height;
            in >> width;
            in >> cnt;
            for(int i=0;i<cnt;i++) {
                int code=0;
                QList<QBitArray> data;
                in >> code;
                in >> data;
                pixels.insert(code,data);
            }
            symbCount = cnt;
            rowCount = height;
            columnCount = width;
            file.close();

            createUnicodeTable();
        }

    }
}

bool LCDPhont::getBitValue(int phCode, int row, int column) const
{
    if(!uncdTable.values().contains(phCode)) return false;
        if(pixels.contains(phCode)) {
            return pixels.value(phCode).at(row).at(column);
        }
    return false;
}

bool LCDPhont::hasSymbol(int uncdValue) const
{
    return uncdTable.contains(uncdValue);
}

int LCDPhont::getSymbCodeinPhont(int unicodeValue) const
{
    if(hasSymbol(unicodeValue)) return uncdTable.value(unicodeValue);
    return 0x20;
}

int LCDPhont::getUnicodeValue(int phontCode) const
{
    if(uncdTable.values().contains(phontCode)) {
        return uncdTable.key(phontCode);
    }
    return 0x20; // space code
}

LCDPhont::~LCDPhont()
{

}

void LCDPhont::createUnicodeTable()
{
    // диапазон символов в шрифте, коды которых совпадают с юникод
    const int latinStartCode = 0x20;
    const int latinFinishCode = 0x7A;
    for(int i=latinStartCode;i<=latinFinishCode;i++) {
        uncdTable.insert(i,i);
    }
    // кириллица
    uncdTable.insert(0x0401,0xA2);  // Ё
    uncdTable.insert(0x0410,0x41);  // А
    uncdTable.insert(0x0411,0xA0);  // Б
    uncdTable.insert(0x0412,0x42);  // В
    uncdTable.insert(0x0413,0xA1);  // Г
    uncdTable.insert(0x0414,0xE0);  // Д
    uncdTable.insert(0x0415,0x45);  // Е
    uncdTable.insert(0x0416,0xA3);  // Ж
    uncdTable.insert(0x0417,0xA4);  // З
    uncdTable.insert(0x0418,0xA5);  // И
    uncdTable.insert(0x0419,0xA6);  // Й
    uncdTable.insert(0x041A,0x4B);  // К
    uncdTable.insert(0x041B,0xA7);  // Л
    uncdTable.insert(0x041C,0x4D);  // М
    uncdTable.insert(0x041D,0x48);  // Н
    uncdTable.insert(0x041E,0x4F);  // О
    uncdTable.insert(0x041F,0xA8);  // П
    uncdTable.insert(0x0420,0x50);  // Р
    uncdTable.insert(0x0421,0x43);  // С
    uncdTable.insert(0x0422,0x54);  // Т
    uncdTable.insert(0x0423,0xA9);  // У
    uncdTable.insert(0x0424,0xAA);  // Ф
    uncdTable.insert(0x0425,0x58);  // Х
    uncdTable.insert(0x0426,0xE1);  // Ц
    uncdTable.insert(0x0427,0xAB);  // Ч
    uncdTable.insert(0x0428,0xAC);  // Ш
    uncdTable.insert(0x0429,0xE2);  // Щ
    uncdTable.insert(0x042A,0xAD);  // Ъ
    uncdTable.insert(0x042B,0xAE);  // Ы
    uncdTable.insert(0x042C,0x62);  // Ь
    uncdTable.insert(0x042D,0xAF);  // Э
    uncdTable.insert(0x042E,0xB0);  // Ю
    uncdTable.insert(0x042F,0xB1);  // Я
    uncdTable.insert(0x0430,0x61);  // а
    uncdTable.insert(0x0431,0xB2);  // б
    uncdTable.insert(0x0432,0xB3);  // в
    uncdTable.insert(0x0433,0xB4);  // г
    uncdTable.insert(0x0434,0xE3);  // д
    uncdTable.insert(0x0435,0x65);  // е
    uncdTable.insert(0x0436,0xB6);  // ж
    uncdTable.insert(0x0437,0xB7);  // з
    uncdTable.insert(0x0438,0xB8);  // и
    uncdTable.insert(0x0439,0xB9);  // й
    uncdTable.insert(0x043A,0xBA);  // к
    uncdTable.insert(0x043B,0xBB);  // л
    uncdTable.insert(0x043C,0xBC);  // м
    uncdTable.insert(0x043D,0xBD);  // н
    uncdTable.insert(0x043E,0x6F);  // о
    uncdTable.insert(0x043F,0xBE);  // п
    uncdTable.insert(0x0440,0x70);  // р
    uncdTable.insert(0x0441,0x63);  // с
    uncdTable.insert(0x0442,0xBF);  // т
    uncdTable.insert(0x0443,0x79);  // у
    uncdTable.insert(0x0444,0xE4);  // ф
    uncdTable.insert(0x0445,0x78);  // х
    uncdTable.insert(0x0446,0xE5);  // ц
    uncdTable.insert(0x0447,0xC0);  // ч
    uncdTable.insert(0x0448,0xC1);  // ш
    uncdTable.insert(0x0449,0xE6);  // щ
    uncdTable.insert(0x044A,0xC2);  // ъ
    uncdTable.insert(0x044B,0xC3);  // ы
    uncdTable.insert(0x044C,0xC4);  // ь
    uncdTable.insert(0x044D,0xC5);  // э
    uncdTable.insert(0x044E,0xC6);  // ю
    uncdTable.insert(0x044F,0xC7);  // я
    uncdTable.insert(0x0451,0xB5);  // ё

    // спец символы
    uncdTable.insert(0x2469,123);
    uncdTable.insert(0x24EC,124);
    uncdTable.insert(0x24EF,125);
    uncdTable.insert(0x23CE,126);
    uncdTable.insert(0xAB,200);
    uncdTable.insert(0xBB,201);
    uncdTable.insert(0x2A0D,206);
    uncdTable.insert(0x2160,215);
    uncdTable.insert(0x2161,216);
    uncdTable.insert(0x2191,217);
    uncdTable.insert(0x2193,218);
    uncdTable.insert(0x260E,237);
    uncdTable.insert(0xBD,242);
    uncdTable.insert(0x2153,241);
    uncdTable.insert(0xBC,240);
}

