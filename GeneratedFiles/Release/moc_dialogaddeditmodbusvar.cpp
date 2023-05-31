/****************************************************************************
** Meta object code from reading C++ file 'dialogaddeditmodbusvar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ModbusMaster/dialogaddeditmodbusvar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogaddeditmodbusvar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogAddEditModbusVar_t {
    QByteArrayData data[12];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogAddEditModbusVar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogAddEditModbusVar_t qt_meta_stringdata_DialogAddEditModbusVar = {
    {
QT_MOC_LITERAL(0, 0, 22), // "DialogAddEditModbusVar"
QT_MOC_LITERAL(1, 23, 38), // "on_comboBoxMemType_currentInd..."
QT_MOC_LITERAL(2, 62, 0), // ""
QT_MOC_LITERAL(3, 63, 5), // "index"
QT_MOC_LITERAL(4, 69, 26), // "on_radioButtonRead_clicked"
QT_MOC_LITERAL(5, 96, 27), // "on_radioButtonWrite_clicked"
QT_MOC_LITERAL(6, 124, 33), // "on_spinBoxNetAddress_valueCha..."
QT_MOC_LITERAL(7, 158, 4), // "arg1"
QT_MOC_LITERAL(8, 163, 30), // "on_spinBoxMemAddr_valueChanged"
QT_MOC_LITERAL(9, 194, 25), // "on_checkBoxEnable_clicked"
QT_MOC_LITERAL(10, 220, 30), // "on_lineEditVarName_textChanged"
QT_MOC_LITERAL(11, 251, 30) // "on_lineEditComment_textChanged"

    },
    "DialogAddEditModbusVar\0"
    "on_comboBoxMemType_currentIndexChanged\0"
    "\0index\0on_radioButtonRead_clicked\0"
    "on_radioButtonWrite_clicked\0"
    "on_spinBoxNetAddress_valueChanged\0"
    "arg1\0on_spinBoxMemAddr_valueChanged\0"
    "on_checkBoxEnable_clicked\0"
    "on_lineEditVarName_textChanged\0"
    "on_lineEditComment_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogAddEditModbusVar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    0,   58,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void DialogAddEditModbusVar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogAddEditModbusVar *_t = static_cast<DialogAddEditModbusVar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBoxMemType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_radioButtonRead_clicked(); break;
        case 2: _t->on_radioButtonWrite_clicked(); break;
        case 3: _t->on_spinBoxNetAddress_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_spinBoxMemAddr_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkBoxEnable_clicked(); break;
        case 6: _t->on_lineEditVarName_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_lineEditComment_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DialogAddEditModbusVar::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogAddEditModbusVar.data,
      qt_meta_data_DialogAddEditModbusVar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogAddEditModbusVar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogAddEditModbusVar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogAddEditModbusVar.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogAddEditModbusVar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
