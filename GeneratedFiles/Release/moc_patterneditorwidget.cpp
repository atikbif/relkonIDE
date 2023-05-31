/****************************************************************************
** Meta object code from reading C++ file 'patterneditorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LCD/patterneditorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patterneditorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PatternEditorWidget_t {
    QByteArrayData data[18];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatternEditorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatternEditorWidget_t qt_meta_stringdata_PatternEditorWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PatternEditorWidget"
QT_MOC_LITERAL(1, 20, 8), // "updFocus"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "newProject"
QT_MOC_LITERAL(4, 41, 11), // "saveProject"
QT_MOC_LITERAL(5, 53, 11), // "openProject"
QT_MOC_LITERAL(6, 65, 7), // "updTree"
QT_MOC_LITERAL(7, 73, 16), // "cursorPosChanged"
QT_MOC_LITERAL(8, 90, 1), // "x"
QT_MOC_LITERAL(9, 92, 1), // "y"
QT_MOC_LITERAL(10, 94, 16), // "doubleClickedVar"
QT_MOC_LITERAL(11, 111, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(12, 128, 4), // "item"
QT_MOC_LITERAL(13, 133, 6), // "column"
QT_MOC_LITERAL(14, 140, 8), // "applyVar"
QT_MOC_LITERAL(15, 149, 13), // "patternUpdate"
QT_MOC_LITERAL(16, 163, 14), // "varPatternText"
QT_MOC_LITERAL(17, 178, 8) // "startPos"

    },
    "PatternEditorWidget\0updFocus\0\0newProject\0"
    "saveProject\0openProject\0updTree\0"
    "cursorPosChanged\0x\0y\0doubleClickedVar\0"
    "QTreeWidgetItem*\0item\0column\0applyVar\0"
    "patternUpdate\0varPatternText\0startPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatternEditorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    2,   64,    2, 0x0a /* Public */,
      10,    2,   69,    2, 0x08 /* Private */,
      14,    0,   74,    2, 0x08 /* Private */,
      15,    2,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   16,   17,

       0        // eod
};

void PatternEditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PatternEditorWidget *_t = static_cast<PatternEditorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updFocus(); break;
        case 1: _t->newProject(); break;
        case 2: _t->saveProject(); break;
        case 3: _t->openProject(); break;
        case 4: _t->updTree(); break;
        case 5: _t->cursorPosChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->doubleClickedVar((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->applyVar(); break;
        case 8: _t->patternUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PatternEditorWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatternEditorWidget::updFocus)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PatternEditorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PatternEditorWidget.data,
      qt_meta_data_PatternEditorWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PatternEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatternEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatternEditorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PatternEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PatternEditorWidget::updFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
