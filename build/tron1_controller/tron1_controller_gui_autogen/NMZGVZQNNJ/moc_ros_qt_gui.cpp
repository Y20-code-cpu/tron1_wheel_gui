/****************************************************************************
** Meta object code from reading C++ file 'ros_qt_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/tron1_controller/ros_qt_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ros_qt_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RosQtGUI_t {
    QByteArrayData data[16];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RosQtGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RosQtGUI_t qt_meta_stringdata_RosQtGUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RosQtGUI"
QT_MOC_LITERAL(1, 9, 14), // "onStandPressed"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "onWalkPressed"
QT_MOC_LITERAL(4, 39, 12), // "onSitPressed"
QT_MOC_LITERAL(5, 52, 13), // "onStopPressed"
QT_MOC_LITERAL(6, 66, 16), // "onRecoverPressed"
QT_MOC_LITERAL(7, 83, 20), // "onLinearSpeedChanged"
QT_MOC_LITERAL(8, 104, 5), // "value"
QT_MOC_LITERAL(9, 110, 21), // "onAngularSpeedChanged"
QT_MOC_LITERAL(10, 132, 16), // "onForwardPressed"
QT_MOC_LITERAL(11, 149, 17), // "onBackwardPressed"
QT_MOC_LITERAL(12, 167, 13), // "onLeftPressed"
QT_MOC_LITERAL(13, 181, 14), // "onRightPressed"
QT_MOC_LITERAL(14, 196, 20), // "onLightEffectChanged"
QT_MOC_LITERAL(15, 217, 6) // "effect"

    },
    "RosQtGUI\0onStandPressed\0\0onWalkPressed\0"
    "onSitPressed\0onStopPressed\0onRecoverPressed\0"
    "onLinearSpeedChanged\0value\0"
    "onAngularSpeedChanged\0onForwardPressed\0"
    "onBackwardPressed\0onLeftPressed\0"
    "onRightPressed\0onLightEffectChanged\0"
    "effect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RosQtGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    1,   82,    2, 0x08 /* Private */,
      10,    0,   85,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void RosQtGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RosQtGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStandPressed(); break;
        case 1: _t->onWalkPressed(); break;
        case 2: _t->onSitPressed(); break;
        case 3: _t->onStopPressed(); break;
        case 4: _t->onRecoverPressed(); break;
        case 5: _t->onLinearSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onAngularSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onForwardPressed(); break;
        case 8: _t->onBackwardPressed(); break;
        case 9: _t->onLeftPressed(); break;
        case 10: _t->onRightPressed(); break;
        case 11: _t->onLightEffectChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RosQtGUI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_RosQtGUI.data,
    qt_meta_data_RosQtGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RosQtGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RosQtGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RosQtGUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RosQtGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
