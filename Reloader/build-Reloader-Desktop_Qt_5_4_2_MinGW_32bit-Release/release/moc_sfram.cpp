/****************************************************************************
** Meta object code from reading C++ file 'sfram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Reloader/Loader/sfram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sfram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sFram_t {
    QByteArrayData data[12];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sFram_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sFram_t qt_meta_stringdata_sFram = {
    {
QT_MOC_LITERAL(0, 0, 5), // "sFram"
QT_MOC_LITERAL(1, 6, 13), // "writeFinished"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "readFinished"
QT_MOC_LITERAL(4, 34, 4), // "data"
QT_MOC_LITERAL(5, 39, 5), // "error"
QT_MOC_LITERAL(6, 45, 7), // "message"
QT_MOC_LITERAL(7, 53, 13), // "percentUpdate"
QT_MOC_LITERAL(8, 67, 5), // "value"
QT_MOC_LITERAL(9, 73, 10), // "startWrite"
QT_MOC_LITERAL(10, 84, 9), // "startRead"
QT_MOC_LITERAL(11, 94, 11) // "stopProcess"

    },
    "sFram\0writeFinished\0\0readFinished\0"
    "data\0error\0message\0percentUpdate\0value\0"
    "startWrite\0startRead\0stopProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sFram[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       7,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   59,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Float,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sFram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sFram *_t = static_cast<sFram *>(_o);
        switch (_id) {
        case 0: _t->writeFinished(); break;
        case 1: _t->readFinished((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->startWrite((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->startRead(); break;
        case 6: _t->stopProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sFram::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sFram::writeFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (sFram::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sFram::readFinished)) {
                *result = 1;
            }
        }
        {
            typedef void (sFram::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sFram::error)) {
                *result = 2;
            }
        }
        {
            typedef void (sFram::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sFram::percentUpdate)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject sFram::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_sFram.data,
      qt_meta_data_sFram,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *sFram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sFram::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_sFram.stringdata))
        return static_cast<void*>(const_cast< sFram*>(this));
    return QObject::qt_metacast(_clname);
}

int sFram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void sFram::writeFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void sFram::readFinished(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void sFram::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void sFram::percentUpdate(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
