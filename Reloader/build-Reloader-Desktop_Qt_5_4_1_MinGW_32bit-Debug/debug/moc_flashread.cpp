/****************************************************************************
** Meta object code from reading C++ file 'flashread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Reloader/Loader/flashread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashRead_t {
    QByteArrayData data[12];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlashRead_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlashRead_t qt_meta_stringdata_FlashRead = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FlashRead"
QT_MOC_LITERAL(1, 10, 9), // "startRead"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "readOK"
QT_MOC_LITERAL(4, 28, 7), // "inpData"
QT_MOC_LITERAL(5, 36, 16), // "startReadProcess"
QT_MOC_LITERAL(6, 53, 5), // "error"
QT_MOC_LITERAL(7, 59, 7), // "message"
QT_MOC_LITERAL(8, 67, 13), // "percentUpdate"
QT_MOC_LITERAL(9, 81, 5), // "value"
QT_MOC_LITERAL(10, 87, 12), // "readFinished"
QT_MOC_LITERAL(11, 100, 4) // "data"

    },
    "FlashRead\0startRead\0\0readOK\0inpData\0"
    "startReadProcess\0error\0message\0"
    "percentUpdate\0value\0readFinished\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashRead[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   48,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x08 /* Private */,
       8,    1,   52,    2, 0x08 /* Private */,
      10,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Float,    9,
    QMetaType::Void, QMetaType::QByteArray,   11,

       0        // eod
};

void FlashRead::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashRead *_t = static_cast<FlashRead *>(_o);
        switch (_id) {
        case 0: _t->startRead(); break;
        case 1: _t->readOK((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->startReadProcess(); break;
        case 3: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->readFinished((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlashRead::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashRead::startRead)) {
                *result = 0;
            }
        }
        {
            typedef void (FlashRead::*_t)(const QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashRead::readOK)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject FlashRead::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FlashRead.data,
      qt_meta_data_FlashRead,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlashRead::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashRead::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlashRead.stringdata))
        return static_cast<void*>(const_cast< FlashRead*>(this));
    return QDialog::qt_metacast(_clname);
}

int FlashRead::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FlashRead::startRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FlashRead::readOK(const QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
