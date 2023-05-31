/****************************************************************************
** Meta object code from reading C++ file 'sysframreadwrite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Reloader/Loader/sysframreadwrite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sysframreadwrite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SysFramReadWrite_t {
    QByteArrayData data[15];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SysFramReadWrite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SysFramReadWrite_t qt_meta_stringdata_SysFramReadWrite = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SysFramReadWrite"
QT_MOC_LITERAL(1, 17, 10), // "startWrite"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "data"
QT_MOC_LITERAL(4, 34, 9), // "startRead"
QT_MOC_LITERAL(5, 44, 6), // "readOK"
QT_MOC_LITERAL(6, 51, 7), // "inpData"
QT_MOC_LITERAL(7, 59, 17), // "startWriteProcess"
QT_MOC_LITERAL(8, 77, 16), // "startReadProcess"
QT_MOC_LITERAL(9, 94, 13), // "writeFinished"
QT_MOC_LITERAL(10, 108, 12), // "readFinished"
QT_MOC_LITERAL(11, 121, 5), // "error"
QT_MOC_LITERAL(12, 127, 7), // "message"
QT_MOC_LITERAL(13, 135, 13), // "percentUpdate"
QT_MOC_LITERAL(14, 149, 5) // "value"

    },
    "SysFramReadWrite\0startWrite\0\0data\0"
    "startRead\0readOK\0inpData\0startWriteProcess\0"
    "startReadProcess\0writeFinished\0"
    "readFinished\0error\0message\0percentUpdate\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SysFramReadWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   66,    2, 0x0a /* Public */,
       8,    0,   69,    2, 0x0a /* Public */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    1,   71,    2, 0x08 /* Private */,
      11,    1,   74,    2, 0x08 /* Private */,
      13,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Float,   14,

       0        // eod
};

void SysFramReadWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SysFramReadWrite *_t = static_cast<SysFramReadWrite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startWrite((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->startRead(); break;
        case 2: _t->readOK((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->startWriteProcess((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->startReadProcess(); break;
        case 5: _t->writeFinished(); break;
        case 6: _t->readFinished((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SysFramReadWrite::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysFramReadWrite::startWrite)) {
                *result = 0;
            }
        }
        {
            typedef void (SysFramReadWrite::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysFramReadWrite::startRead)) {
                *result = 1;
            }
        }
        {
            typedef void (SysFramReadWrite::*_t)(const QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysFramReadWrite::readOK)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SysFramReadWrite::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SysFramReadWrite.data,
      qt_meta_data_SysFramReadWrite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SysFramReadWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SysFramReadWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SysFramReadWrite.stringdata0))
        return static_cast<void*>(const_cast< SysFramReadWrite*>(this));
    return QDialog::qt_metacast(_clname);
}

int SysFramReadWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SysFramReadWrite::startWrite(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SysFramReadWrite::startRead()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SysFramReadWrite::readOK(const QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
