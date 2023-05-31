/****************************************************************************
** Meta object code from reading C++ file 'scancontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AutoSearch/scancontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scancontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanController_t {
    QByteArrayData data[14];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanController_t qt_meta_stringdata_ScanController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ScanController"
QT_MOC_LITERAL(1, 15, 7), // "updated"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "percValue"
QT_MOC_LITERAL(4, 34, 5), // "pName"
QT_MOC_LITERAL(5, 40, 8), // "finished"
QT_MOC_LITERAL(6, 49, 7), // "message"
QT_MOC_LITERAL(7, 57, 5), // "found"
QT_MOC_LITERAL(8, 63, 16), // "SearchController"
QT_MOC_LITERAL(9, 80, 3), // "plc"
QT_MOC_LITERAL(10, 84, 9), // "startScan"
QT_MOC_LITERAL(11, 94, 10), // "portIsBusy"
QT_MOC_LITERAL(12, 105, 13), // "percentUpdate"
QT_MOC_LITERAL(13, 119, 15) // "plcHasBeenFound"

    },
    "ScanController\0updated\0\0percValue\0"
    "pName\0finished\0message\0found\0"
    "SearchController\0plc\0startScan\0"
    "portIsBusy\0percentUpdate\0plcHasBeenFound"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    2,   62,    2, 0x06 /* Public */,
      10,    1,   67,    2, 0x06 /* Public */,
      11,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   73,    2, 0x08 /* Private */,
      13,    1,   76,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void ScanController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanController *_t = static_cast<ScanController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->finished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->found((*reinterpret_cast< SearchController(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->startScan((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->portIsBusy((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->plcHasBeenFound((*reinterpret_cast< SearchController(*)>(_a[1]))); break;
        case 7: _t->portIsBusy(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanController::*)(float , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanController::updated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScanController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanController::finished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ScanController::*)(SearchController , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanController::found)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ScanController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanController::startScan)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ScanController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanController::portIsBusy)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScanController.data,
      qt_meta_data_ScanController,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScanController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScanController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ScanController::updated(float _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScanController::finished(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScanController::found(SearchController _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScanController::startScan(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScanController::portIsBusy(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
