/****************************************************************************
** Meta object code from reading C++ file 'rrt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rrt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rrt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RRT_t {
    QByteArrayData data[11];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RRT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RRT_t qt_meta_stringdata_RRT = {
    {
QT_MOC_LITERAL(0, 0, 3), // "RRT"
QT_MOC_LITERAL(1, 4, 21), // "on_LoadButton_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "mousePressed"
QT_MOC_LITERAL(4, 40, 1), // "x"
QT_MOC_LITERAL(5, 42, 1), // "y"
QT_MOC_LITERAL(6, 44, 11), // "leftOrRight"
QT_MOC_LITERAL(7, 56, 22), // "on_resetButton_clicked"
QT_MOC_LITERAL(8, 79, 22), // "on_startButton_clicked"
QT_MOC_LITERAL(9, 102, 31), // "on_distanceInputBox_textChanged"
QT_MOC_LITERAL(10, 134, 4) // "arg1"

    },
    "RRT\0on_LoadButton_clicked\0\0mousePressed\0"
    "x\0y\0leftOrRight\0on_resetButton_clicked\0"
    "on_startButton_clicked\0"
    "on_distanceInputBox_textChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RRT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    3,   40,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,
       8,    0,   48,    2, 0x08 /* Private */,
       9,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void RRT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RRT *_t = static_cast<RRT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_LoadButton_clicked(); break;
        case 1: _t->mousePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->on_resetButton_clicked(); break;
        case 3: _t->on_startButton_clicked(); break;
        case 4: _t->on_distanceInputBox_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject RRT::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RRT.data,
      qt_meta_data_RRT,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RRT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RRT::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RRT.stringdata0))
        return static_cast<void*>(const_cast< RRT*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RRT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
