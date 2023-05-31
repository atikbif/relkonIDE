/****************************************************************************
** Meta object code from reading C++ file 'prbuilder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../prbuilder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'prbuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrBuilder_t {
    QByteArrayData data[13];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrBuilder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrBuilder_t qt_meta_stringdata_PrBuilder = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PrBuilder"
QT_MOC_LITERAL(1, 10, 12), // "printMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "str"
QT_MOC_LITERAL(4, 28, 15), // "buildIsFinished"
QT_MOC_LITERAL(5, 44, 9), // "buildIsOk"
QT_MOC_LITERAL(6, 54, 12), // "buildRequest"
QT_MOC_LITERAL(7, 67, 6), // "prPath"
QT_MOC_LITERAL(8, 74, 6), // "prName"
QT_MOC_LITERAL(9, 81, 12), // "FCUCSettings"
QT_MOC_LITERAL(10, 94, 4), // "conf"
QT_MOC_LITERAL(11, 99, 11), // "setFileText"
QT_MOC_LITERAL(12, 111, 3) // "plc"

    },
    "PrBuilder\0printMessage\0\0str\0buildIsFinished\0"
    "buildIsOk\0buildRequest\0prPath\0prName\0"
    "FCUCSettings\0conf\0setFileText\0plc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrBuilder[] = {

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
       4,    0,   42,    2, 0x06 /* Public */,
       5,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   44,    2, 0x0a /* Public */,
      11,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 9,    7,    8,   10,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,    3,   12,

       0        // eod
};

void PrBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PrBuilder *_t = static_cast<PrBuilder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->printMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->buildIsFinished(); break;
        case 2: _t->buildIsOk(); break;
        case 3: _t->buildRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< FCUCSettings(*)>(_a[3]))); break;
        case 4: _t->setFileText((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrBuilder::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrBuilder::printMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PrBuilder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrBuilder::buildIsFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PrBuilder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrBuilder::buildIsOk)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PrBuilder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PrBuilder.data,
      qt_meta_data_PrBuilder,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PrBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrBuilder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PrBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PrBuilder::printMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PrBuilder::buildIsFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PrBuilder::buildIsOk()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
