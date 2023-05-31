/****************************************************************************
** Meta object code from reading C++ file 'strlistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LCD/strlistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'strlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StrListWidget_t {
    QByteArrayData data[22];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StrListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StrListWidget_t qt_meta_stringdata_StrListWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "StrListWidget"
QT_MOC_LITERAL(1, 14, 8), // "updFocus"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "strChanged"
QT_MOC_LITERAL(4, 35, 6), // "strNum"
QT_MOC_LITERAL(5, 42, 9), // "subStrNum"
QT_MOC_LITERAL(6, 52, 14), // "strListChanged"
QT_MOC_LITERAL(7, 67, 11), // "itemClicked"
QT_MOC_LITERAL(8, 79, 11), // "QModelIndex"
QT_MOC_LITERAL(9, 91, 5), // "index"
QT_MOC_LITERAL(10, 97, 16), // "curStrNumChanged"
QT_MOC_LITERAL(11, 114, 22), // "showContextMenuForList"
QT_MOC_LITERAL(12, 137, 3), // "pos"
QT_MOC_LITERAL(13, 141, 18), // "insertStringBefore"
QT_MOC_LITERAL(14, 160, 17), // "insertStringAfter"
QT_MOC_LITERAL(15, 178, 12), // "deleteString"
QT_MOC_LITERAL(16, 191, 20), // "activateDesactString"
QT_MOC_LITERAL(17, 212, 10), // "copyString"
QT_MOC_LITERAL(18, 223, 11), // "pasteString"
QT_MOC_LITERAL(19, 235, 9), // "cutString"
QT_MOC_LITERAL(20, 245, 13), // "activateGroup"
QT_MOC_LITERAL(21, 259, 16) // "desactivateGroup"

    },
    "StrListWidget\0updFocus\0\0strChanged\0"
    "strNum\0subStrNum\0strListChanged\0"
    "itemClicked\0QModelIndex\0index\0"
    "curStrNumChanged\0showContextMenuForList\0"
    "pos\0insertStringBefore\0insertStringAfter\0"
    "deleteString\0activateDesactString\0"
    "copyString\0pasteString\0cutString\0"
    "activateGroup\0desactivateGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StrListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   90,    2, 0x0a /* Public */,
       6,    1,   95,    2, 0x0a /* Public */,
       7,    1,   98,    2, 0x08 /* Private */,
      10,    2,  101,    2, 0x08 /* Private */,
      11,    1,  106,    2, 0x08 /* Private */,
      13,    0,  109,    2, 0x08 /* Private */,
      14,    0,  110,    2, 0x08 /* Private */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    0,  112,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    0,  115,    2, 0x08 /* Private */,
      20,    0,  116,    2, 0x08 /* Private */,
      21,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QPoint,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StrListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StrListWidget *_t = static_cast<StrListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updFocus(); break;
        case 1: _t->strChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->strListChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->itemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->curStrNumChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->showContextMenuForList((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->insertStringBefore(); break;
        case 7: _t->insertStringAfter(); break;
        case 8: _t->deleteString(); break;
        case 9: _t->activateDesactString(); break;
        case 10: _t->copyString(); break;
        case 11: _t->pasteString(); break;
        case 12: _t->cutString(); break;
        case 13: _t->activateGroup(); break;
        case 14: _t->desactivateGroup(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StrListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StrListWidget::updFocus)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StrListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StrListWidget.data,
      qt_meta_data_StrListWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StrListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StrListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StrListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StrListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void StrListWidget::updFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
