/****************************************************************************
** Meta object code from reading C++ file 'scanuart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Reloader/AutoSearch/scanuart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanuart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScanUART_t {
    QByteArrayData data[12];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanUART_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanUART_t qt_meta_stringdata_ScanUART = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ScanUART"
QT_MOC_LITERAL(1, 9, 13), // "percentUpdate"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "percValue"
QT_MOC_LITERAL(4, 34, 14), // "scanIsFinished"
QT_MOC_LITERAL(5, 49, 7), // "message"
QT_MOC_LITERAL(6, 57, 15), // "plcHasBeenFound"
QT_MOC_LITERAL(7, 73, 19), // "DetectedController*"
QT_MOC_LITERAL(8, 93, 3), // "plc"
QT_MOC_LITERAL(9, 97, 9), // "startScan"
QT_MOC_LITERAL(10, 107, 5), // "pName"
QT_MOC_LITERAL(11, 113, 8) // "stopScan"

    },
    "ScanUART\0percentUpdate\0\0percValue\0"
    "scanIsFinished\0message\0plcHasBeenFound\0"
    "DetectedController*\0plc\0startScan\0"
    "pName\0stopScan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanUART[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   48,    2, 0x0a /* Public */,
      11,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void ScanUART::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanUART *_t = static_cast<ScanUART *>(_o);
        switch (_id) {
        case 0: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->scanIsFinished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->plcHasBeenFound((*reinterpret_cast< DetectedController*(*)>(_a[1]))); break;
        case 3: _t->startScan((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->stopScan(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScanUART::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanUART::percentUpdate)) {
                *result = 0;
            }
        }
        {
            typedef void (ScanUART::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanUART::scanIsFinished)) {
                *result = 1;
            }
        }
        {
            typedef void (ScanUART::*_t)(DetectedController * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanUART::plcHasBeenFound)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ScanUART::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScanUART.data,
      qt_meta_data_ScanUART,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScanUART::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanUART::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScanUART.stringdata))
        return static_cast<void*>(const_cast< ScanUART*>(this));
    return QObject::qt_metacast(_clname);
}

int ScanUART::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ScanUART::percentUpdate(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScanUART::scanIsFinished(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScanUART::plcHasBeenFound(DetectedController * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
