/****************************************************************************
** Meta object code from reading C++ file 'ymodemthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Reloader/Loader/ymodemthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ymodemthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_YmodemThread_t {
    QByteArrayData data[10];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_YmodemThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_YmodemThread_t qt_meta_stringdata_YmodemThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "YmodemThread"
QT_MOC_LITERAL(1, 13, 12), // "startProcess"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "pName"
QT_MOC_LITERAL(4, 33, 8), // "filePath"
QT_MOC_LITERAL(5, 42, 8), // "finished"
QT_MOC_LITERAL(6, 51, 13), // "percentUpdate"
QT_MOC_LITERAL(7, 65, 5), // "value"
QT_MOC_LITERAL(8, 71, 9), // "bootError"
QT_MOC_LITERAL(9, 81, 7) // "message"

    },
    "YmodemThread\0startProcess\0\0pName\0"
    "filePath\0finished\0percentUpdate\0value\0"
    "bootError\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YmodemThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void YmodemThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        YmodemThread *_t = static_cast<YmodemThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->finished(); break;
        case 2: _t->percentUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->bootError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (YmodemThread::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&YmodemThread::startProcess)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject YmodemThread::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_YmodemThread.data,
      qt_meta_data_YmodemThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *YmodemThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YmodemThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_YmodemThread.stringdata0))
        return static_cast<void*>(const_cast< YmodemThread*>(this));
    return QDialog::qt_metacast(_clname);
}

int YmodemThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void YmodemThread::startProcess(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
