/****************************************************************************
** Meta object code from reading C++ file 'varwatchermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QuickWatch/varwatchermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'varwatchermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VarWatcherManager_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VarWatcherManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VarWatcherManager_t qt_meta_stringdata_VarWatcherManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "VarWatcherManager"
QT_MOC_LITERAL(1, 18, 12), // "startProcess"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "quickInfoRequest"
QT_MOC_LITERAL(4, 49, 10), // "closeWatch"
QT_MOC_LITERAL(5, 60, 9), // "quickInfo"
QT_MOC_LITERAL(6, 70, 5), // "names"
QT_MOC_LITERAL(7, 76, 6) // "values"

    },
    "VarWatcherManager\0startProcess\0\0"
    "quickInfoRequest\0closeWatch\0quickInfo\0"
    "names\0values"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VarWatcherManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList,    6,    7,

       0        // eod
};

void VarWatcherManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VarWatcherManager *_t = static_cast<VarWatcherManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startProcess(); break;
        case 1: _t->quickInfoRequest(); break;
        case 2: _t->closeWatch(); break;
        case 3: _t->quickInfo((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VarWatcherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VarWatcherManager::startProcess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VarWatcherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VarWatcherManager::quickInfoRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VarWatcherManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VarWatcherManager::closeWatch)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VarWatcherManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VarWatcherManager.data,
      qt_meta_data_VarWatcherManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VarWatcherManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VarWatcherManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VarWatcherManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VarWatcherManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void VarWatcherManager::startProcess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VarWatcherManager::quickInfoRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VarWatcherManager::closeWatch()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
