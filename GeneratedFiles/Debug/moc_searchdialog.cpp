/****************************************************************************
** Meta object code from reading C++ file 'searchdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Search/searchdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchDialog_t {
    QByteArrayData data[20];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchDialog_t qt_meta_stringdata_SearchDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SearchDialog"
QT_MOC_LITERAL(1, 13, 11), // "startSearch"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "SearchData"
QT_MOC_LITERAL(4, 37, 5), // "sInfo"
QT_MOC_LITERAL(5, 43, 7), // "replace"
QT_MOC_LITERAL(6, 51, 7), // "newText"
QT_MOC_LITERAL(7, 59, 10), // "replaceAll"
QT_MOC_LITERAL(8, 70, 7), // "outText"
QT_MOC_LITERAL(9, 78, 7), // "goToStr"
QT_MOC_LITERAL(10, 86, 6), // "strNum"
QT_MOC_LITERAL(11, 93, 9), // "unfoldStr"
QT_MOC_LITERAL(12, 103, 9), // "getResult"
QT_MOC_LITERAL(13, 113, 4), // "list"
QT_MOC_LITERAL(14, 118, 27), // "on_pushButtonSearch_clicked"
QT_MOC_LITERAL(15, 146, 28), // "on_pushButtonReplace_clicked"
QT_MOC_LITERAL(16, 175, 31), // "on_listWidget_itemDoubleClicked"
QT_MOC_LITERAL(17, 207, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(18, 224, 4), // "item"
QT_MOC_LITERAL(19, 229, 31) // "on_pushButtonReplaceAll_clicked"

    },
    "SearchDialog\0startSearch\0\0SearchData\0"
    "sInfo\0replace\0newText\0replaceAll\0"
    "outText\0goToStr\0strNum\0unfoldStr\0"
    "getResult\0list\0on_pushButtonSearch_clicked\0"
    "on_pushButtonReplace_clicked\0"
    "on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0"
    "on_pushButtonReplaceAll_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       7,    2,   70,    2, 0x06 /* Public */,
       9,    2,   75,    2, 0x06 /* Public */,
      11,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   83,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,
      16,    1,   88,    2, 0x08 /* Private */,
      19,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,   10,    4,
    QMetaType::Void, QMetaType::Int,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

       0        // eod
};

void SearchDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchDialog *_t = static_cast<SearchDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSearch((*reinterpret_cast< const SearchData(*)>(_a[1]))); break;
        case 1: _t->replace((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->replaceAll((*reinterpret_cast< const SearchData(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->goToStr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const SearchData(*)>(_a[2]))); break;
        case 4: _t->unfoldStr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->getResult((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: _t->on_pushButtonSearch_clicked(); break;
        case 7: _t->on_pushButtonReplace_clicked(); break;
        case 8: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->on_pushButtonReplaceAll_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchDialog::*)(const SearchData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDialog::startSearch)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDialog::replace)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchDialog::*)(const SearchData & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDialog::replaceAll)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SearchDialog::*)(int , const SearchData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDialog::goToStr)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SearchDialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchDialog::unfoldStr)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SearchDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SearchDialog.data,
      qt_meta_data_SearchDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SearchDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SearchDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SearchDialog::startSearch(const SearchData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchDialog::replace(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SearchDialog::replaceAll(const SearchData & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SearchDialog::goToStr(int _t1, const SearchData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SearchDialog::unfoldStr(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
