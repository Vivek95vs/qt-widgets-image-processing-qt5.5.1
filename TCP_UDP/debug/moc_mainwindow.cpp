/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[522];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "onTcpClientButtonClicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 24), // "onTcpClientNewConnection"
QT_MOC_LITERAL(4, 62, 4), // "from"
QT_MOC_LITERAL(5, 67, 4), // "port"
QT_MOC_LITERAL(6, 72, 28), // "onTcpClientStopButtonClicked"
QT_MOC_LITERAL(7, 101, 18), // "onTcpClientTimeOut"
QT_MOC_LITERAL(8, 120, 34), // "onTcpClientDisconnectButtonCl..."
QT_MOC_LITERAL(9, 155, 23), // "onTcpClientDisconnected"
QT_MOC_LITERAL(10, 179, 22), // "onTcpClientSendMessage"
QT_MOC_LITERAL(11, 202, 24), // "onTcpClientAppendMessage"
QT_MOC_LITERAL(12, 227, 7), // "message"
QT_MOC_LITERAL(13, 235, 24), // "onTcpServerButtonClicked"
QT_MOC_LITERAL(14, 260, 24), // "onTcpServerNewConnection"
QT_MOC_LITERAL(15, 285, 28), // "onTcpServerStopButtonClicked"
QT_MOC_LITERAL(16, 314, 34), // "onTcpServerDisconnectButtonCl..."
QT_MOC_LITERAL(17, 349, 23), // "onTcpServerDisconnected"
QT_MOC_LITERAL(18, 373, 22), // "onTcpServerSendMessage"
QT_MOC_LITERAL(19, 396, 24), // "onTcpServerAppendMessage"
QT_MOC_LITERAL(20, 421, 18), // "onUdpButtonClicked"
QT_MOC_LITERAL(21, 440, 22), // "onUdpStopButtonClicked"
QT_MOC_LITERAL(22, 463, 16), // "onUdpSendMessage"
QT_MOC_LITERAL(23, 480, 18), // "onUdpAppendMessage"
QT_MOC_LITERAL(24, 499, 22) // "onRefreshButtonClicked"

    },
    "MainWindow\0onTcpClientButtonClicked\0"
    "\0onTcpClientNewConnection\0from\0port\0"
    "onTcpClientStopButtonClicked\0"
    "onTcpClientTimeOut\0"
    "onTcpClientDisconnectButtonClicked\0"
    "onTcpClientDisconnected\0onTcpClientSendMessage\0"
    "onTcpClientAppendMessage\0message\0"
    "onTcpServerButtonClicked\0"
    "onTcpServerNewConnection\0"
    "onTcpServerStopButtonClicked\0"
    "onTcpServerDisconnectButtonClicked\0"
    "onTcpServerDisconnected\0onTcpServerSendMessage\0"
    "onTcpServerAppendMessage\0onUdpButtonClicked\0"
    "onUdpStopButtonClicked\0onUdpSendMessage\0"
    "onUdpAppendMessage\0onRefreshButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    2,  115,    2, 0x08 /* Private */,
       6,    0,  120,    2, 0x08 /* Private */,
       7,    0,  121,    2, 0x08 /* Private */,
       8,    0,  122,    2, 0x08 /* Private */,
       9,    0,  123,    2, 0x08 /* Private */,
      10,    0,  124,    2, 0x08 /* Private */,
      11,    2,  125,    2, 0x08 /* Private */,
      13,    0,  130,    2, 0x08 /* Private */,
      14,    2,  131,    2, 0x08 /* Private */,
      15,    0,  136,    2, 0x08 /* Private */,
      16,    0,  137,    2, 0x08 /* Private */,
      17,    0,  138,    2, 0x08 /* Private */,
      18,    0,  139,    2, 0x08 /* Private */,
      19,    2,  140,    2, 0x08 /* Private */,
      20,    0,  145,    2, 0x08 /* Private */,
      21,    0,  146,    2, 0x08 /* Private */,
      22,    0,  147,    2, 0x08 /* Private */,
      23,    2,  148,    2, 0x08 /* Private */,
      24,    0,  153,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,   12,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTcpClientButtonClicked(); break;
        case 1: _t->onTcpClientNewConnection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 2: _t->onTcpClientStopButtonClicked(); break;
        case 3: _t->onTcpClientTimeOut(); break;
        case 4: _t->onTcpClientDisconnectButtonClicked(); break;
        case 5: _t->onTcpClientDisconnected(); break;
        case 6: _t->onTcpClientSendMessage(); break;
        case 7: _t->onTcpClientAppendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->onTcpServerButtonClicked(); break;
        case 9: _t->onTcpServerNewConnection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 10: _t->onTcpServerStopButtonClicked(); break;
        case 11: _t->onTcpServerDisconnectButtonClicked(); break;
        case 12: _t->onTcpServerDisconnected(); break;
        case 13: _t->onTcpServerSendMessage(); break;
        case 14: _t->onTcpServerAppendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->onUdpButtonClicked(); break;
        case 16: _t->onUdpStopButtonClicked(); break;
        case 17: _t->onUdpSendMessage(); break;
        case 18: _t->onUdpAppendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 19: _t->onRefreshButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
