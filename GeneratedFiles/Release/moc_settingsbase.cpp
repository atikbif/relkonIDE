/****************************************************************************
** Meta object code from reading C++ file 'settingsbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../settingsbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsBase_t {
    QByteArrayData data[16];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsBase_t qt_meta_stringdata_SettingsBase = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SettingsBase"
QT_MOC_LITERAL(1, 13, 10), // "writeToPLC"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "binData"
QT_MOC_LITERAL(4, 33, 11), // "readFromPLC"
QT_MOC_LITERAL(5, 45, 14), // "emuModeChanged"
QT_MOC_LITERAL(6, 60, 21), // "SettingsBase::emuType"
QT_MOC_LITERAL(7, 82, 5), // "value"
QT_MOC_LITERAL(8, 88, 10), // "newPLCType"
QT_MOC_LITERAL(9, 99, 7), // "plcType"
QT_MOC_LITERAL(10, 107, 11), // "readFromBin"
QT_MOC_LITERAL(11, 119, 7), // "inpData"
QT_MOC_LITERAL(12, 127, 12), // "writeSysFram"
QT_MOC_LITERAL(13, 140, 11), // "readSysFram"
QT_MOC_LITERAL(14, 152, 12), // "readUserFram"
QT_MOC_LITERAL(15, 165, 13) // "writeUserFram"

    },
    "SettingsBase\0writeToPLC\0\0binData\0"
    "readFromPLC\0emuModeChanged\0"
    "SettingsBase::emuType\0value\0newPLCType\0"
    "plcType\0readFromBin\0inpData\0writeSysFram\0"
    "readSysFram\0readUserFram\0writeUserFram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,
       8,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   69,    2, 0x0a /* Public */,
      12,    0,   72,    2, 0x0a /* Public */,
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingsBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingsBase *_t = static_cast<SettingsBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->writeToPLC((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->readFromPLC(); break;
        case 2: _t->emuModeChanged((*reinterpret_cast< SettingsBase::emuType(*)>(_a[1]))); break;
        case 3: _t->newPLCType((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->readFromBin((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 5: _t->writeSysFram(); break;
        case 6: _t->readSysFram(); break;
        case 7: _t->readUserFram(); break;
        case 8: _t->writeUserFram(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsBase::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsBase::writeToPLC)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsBase::readFromPLC)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsBase::*)(SettingsBase::emuType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsBase::emuModeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsBase::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsBase::newPLCType)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingsBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingsBase.data,
      qt_meta_data_SettingsBase,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SettingsBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsBase.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SettingsBase::writeToPLC(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingsBase::readFromPLC()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SettingsBase::emuModeChanged(SettingsBase::emuType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingsBase::newPLCType(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
