/****************************************************************************
** Meta object code from reading C++ file 'scanmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Debugger/Scanner/scanmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanManager_t {
    QByteArrayData data[15];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanManager_t qt_meta_stringdata_ScanManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ScanManager"
QT_MOC_LITERAL(1, 12, 12), // "startProcess"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "updateAnswerCnt"
QT_MOC_LITERAL(4, 42, 3), // "cnt"
QT_MOC_LITERAL(5, 46, 13), // "correctAnswer"
QT_MOC_LITERAL(6, 60, 10), // "addMessage"
QT_MOC_LITERAL(7, 71, 7), // "message"
QT_MOC_LITERAL(8, 79, 10), // "errMessage"
QT_MOC_LITERAL(9, 90, 13), // "updateTimeStr"
QT_MOC_LITERAL(10, 104, 7), // "timeStr"
QT_MOC_LITERAL(11, 112, 16), // "updCorrAnswerCnt"
QT_MOC_LITERAL(12, 129, 15), // "updErrAnswerCnt"
QT_MOC_LITERAL(13, 145, 13), // "startDebugger"
QT_MOC_LITERAL(14, 159, 12) // "stopDebugger"

    },
    "ScanManager\0startProcess\0\0updateAnswerCnt\0"
    "cnt\0correctAnswer\0addMessage\0message\0"
    "errMessage\0updateTimeStr\0timeStr\0"
    "updCorrAnswerCnt\0updErrAnswerCnt\0"
    "startDebugger\0stopDebugger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    2,   60,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,
       9,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   74,    2, 0x08 /* Private */,
      12,    1,   77,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScanManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanManager *_t = static_cast<ScanManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startProcess(); break;
        case 1: _t->updateAnswerCnt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->addMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->errMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->updateTimeStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->updCorrAnswerCnt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updErrAnswerCnt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->startDebugger(); break;
        case 8: _t->stopDebugger(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanManager::startProcess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScanManager::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanManager::updateAnswerCnt)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ScanManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanManager::addMessage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ScanManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanManager::errMessage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ScanManager::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanManager::updateTimeStr)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScanManager.data,
      qt_meta_data_ScanManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScanManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScanManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ScanManager::startProcess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ScanManager::updateAnswerCnt(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScanManager::addMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScanManager::errMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScanManager::updateTimeStr(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
