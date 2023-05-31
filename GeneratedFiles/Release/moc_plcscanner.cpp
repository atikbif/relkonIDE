/****************************************************************************
** Meta object code from reading C++ file 'plcscanner.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Debugger/Scanner/plcscanner.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plcscanner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PLCScanner_t {
    QByteArrayData data[15];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PLCScanner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PLCScanner_t qt_meta_stringdata_PLCScanner = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PLCScanner"
QT_MOC_LITERAL(1, 11, 11), // "updateBlock"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "memType"
QT_MOC_LITERAL(4, 32, 4), // "addr"
QT_MOC_LITERAL(5, 37, 4), // "data"
QT_MOC_LITERAL(6, 42, 23), // "updateCorrectRequestCnt"
QT_MOC_LITERAL(7, 66, 3), // "cnt"
QT_MOC_LITERAL(8, 70, 21), // "updateErrorRequestCnt"
QT_MOC_LITERAL(9, 92, 10), // "addMessage"
QT_MOC_LITERAL(10, 103, 7), // "message"
QT_MOC_LITERAL(11, 111, 10), // "errMessage"
QT_MOC_LITERAL(12, 122, 13), // "updateTimeStr"
QT_MOC_LITERAL(13, 136, 7), // "timeStr"
QT_MOC_LITERAL(14, 144, 11) // "scanProcess"

    },
    "PLCScanner\0updateBlock\0\0memType\0addr\0"
    "data\0updateCorrectRequestCnt\0cnt\0"
    "updateErrorRequestCnt\0addMessage\0"
    "message\0errMessage\0updateTimeStr\0"
    "timeStr\0scanProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PLCScanner[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    1,   56,    2, 0x06 /* Public */,
       8,    1,   59,    2, 0x06 /* Public */,
       9,    1,   62,    2, 0x06 /* Public */,
      11,    1,   65,    2, 0x06 /* Public */,
      12,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QByteArray,    3,    4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PLCScanner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PLCScanner *_t = static_cast<PLCScanner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateBlock((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 1: _t->updateCorrectRequestCnt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateErrorRequestCnt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->errMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->updateTimeStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->scanProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PLCScanner::*)(QString , int , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::updateBlock)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PLCScanner::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::updateCorrectRequestCnt)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PLCScanner::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::updateErrorRequestCnt)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PLCScanner::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::addMessage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PLCScanner::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::errMessage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PLCScanner::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PLCScanner::updateTimeStr)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PLCScanner::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PLCScanner.data,
      qt_meta_data_PLCScanner,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PLCScanner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLCScanner::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PLCScanner.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PLCScanner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PLCScanner::updateBlock(QString _t1, int _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PLCScanner::updateCorrectRequestCnt(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PLCScanner::updateErrorRequestCnt(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PLCScanner::addMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PLCScanner::errMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PLCScanner::updateTimeStr(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
