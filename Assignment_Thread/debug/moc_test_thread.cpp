/****************************************************************************
** Meta object code from reading C++ file 'test_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../test_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Test_Thread_t {
    QByteArrayData data[7];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test_Thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test_Thread_t qt_meta_stringdata_Test_Thread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Test_Thread"
QT_MOC_LITERAL(1, 12, 20), // "onBufferValueChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 22), // "onProducerValueChanged"
QT_MOC_LITERAL(4, 57, 22), // "onConsumerValueChanged"
QT_MOC_LITERAL(5, 80, 19), // "on_PB_Start_clicked"
QT_MOC_LITERAL(6, 100, 18) // "on_PB_Stop_clicked"

    },
    "Test_Thread\0onBufferValueChanged\0\0"
    "onProducerValueChanged\0onConsumerValueChanged\0"
    "on_PB_Start_clicked\0on_PB_Stop_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test_Thread[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       3,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Test_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Test_Thread *_t = static_cast<Test_Thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBufferValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onProducerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onConsumerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_PB_Start_clicked(); break;
        case 4: _t->on_PB_Stop_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Test_Thread::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Test_Thread.data,
      qt_meta_data_Test_Thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Test_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Test_Thread.stringdata0))
        return static_cast<void*>(const_cast< Test_Thread*>(this));
    return QDialog::qt_metacast(_clname);
}

int Test_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
