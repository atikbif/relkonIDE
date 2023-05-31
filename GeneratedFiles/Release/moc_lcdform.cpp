/****************************************************************************
** Meta object code from reading C++ file 'lcdform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LCD/lcdform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lcdform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LCDForm_t {
    QByteArrayData data[10];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LCDForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LCDForm_t qt_meta_stringdata_LCDForm = {
    {
QT_MOC_LITERAL(0, 0, 7), // "LCDForm"
QT_MOC_LITERAL(1, 8, 10), // "newProject"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "openProject"
QT_MOC_LITERAL(4, 32, 11), // "saveProject"
QT_MOC_LITERAL(5, 44, 7), // "updTree"
QT_MOC_LITERAL(6, 52, 8), // "updFocus"
QT_MOC_LITERAL(7, 61, 7), // "saveLCD"
QT_MOC_LITERAL(8, 69, 7), // "openLCD"
QT_MOC_LITERAL(9, 77, 6) // "newLCD"

    },
    "LCDForm\0newProject\0\0openProject\0"
    "saveProject\0updTree\0updFocus\0saveLCD\0"
    "openLCD\0newLCD"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LCDForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LCDForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LCDForm *_t = static_cast<LCDForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newProject(); break;
        case 1: _t->openProject(); break;
        case 2: _t->saveProject(); break;
        case 3: _t->updTree(); break;
        case 4: _t->updFocus(); break;
        case 5: _t->saveLCD(); break;
        case 6: _t->openLCD(); break;
        case 7: _t->newLCD(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LCDForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LCDForm::newProject)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LCDForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LCDForm::openProject)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LCDForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LCDForm::saveProject)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LCDForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LCDForm::updTree)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LCDForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LCDForm.data,
      qt_meta_data_LCDForm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LCDForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LCDForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LCDForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LCDForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void LCDForm::newProject()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LCDForm::openProject()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LCDForm::saveProject()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LCDForm::updTree()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
