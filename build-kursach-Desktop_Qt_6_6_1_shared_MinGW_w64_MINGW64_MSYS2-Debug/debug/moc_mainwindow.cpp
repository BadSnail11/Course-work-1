/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../kursach/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_auth_closed",
    "",
    "id",
    "on_ordersButton_clicked",
    "on_passagesButton_clicked",
    "on_transportsButton_clicked",
    "on_tableView_doubleClicked",
    "QModelIndex",
    "index",
    "on_order_change_accepted",
    "on_passage_change_accepted",
    "on_transport_change_accepted",
    "on_account_change_accepted",
    "on_addButton_clicked",
    "on_deleteButton_clicked",
    "type",
    "on_sortOBox_activated",
    "on_sortTBox_activated",
    "on_sortPBox_activated",
    "on_orderButton_clicked",
    "on_accountsButton_clicked",
    "on_logoutButton_clicked",
    "on_findButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[48];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[3];
    char stringdata4[24];
    char stringdata5[26];
    char stringdata6[28];
    char stringdata7[27];
    char stringdata8[12];
    char stringdata9[6];
    char stringdata10[25];
    char stringdata11[27];
    char stringdata12[29];
    char stringdata13[27];
    char stringdata14[21];
    char stringdata15[24];
    char stringdata16[5];
    char stringdata17[22];
    char stringdata18[22];
    char stringdata19[22];
    char stringdata20[23];
    char stringdata21[26];
    char stringdata22[24];
    char stringdata23[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 14),  // "on_auth_closed"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 2),  // "id"
        QT_MOC_LITERAL(30, 23),  // "on_ordersButton_clicked"
        QT_MOC_LITERAL(54, 25),  // "on_passagesButton_clicked"
        QT_MOC_LITERAL(80, 27),  // "on_transportsButton_clicked"
        QT_MOC_LITERAL(108, 26),  // "on_tableView_doubleClicked"
        QT_MOC_LITERAL(135, 11),  // "QModelIndex"
        QT_MOC_LITERAL(147, 5),  // "index"
        QT_MOC_LITERAL(153, 24),  // "on_order_change_accepted"
        QT_MOC_LITERAL(178, 26),  // "on_passage_change_accepted"
        QT_MOC_LITERAL(205, 28),  // "on_transport_change_accepted"
        QT_MOC_LITERAL(234, 26),  // "on_account_change_accepted"
        QT_MOC_LITERAL(261, 20),  // "on_addButton_clicked"
        QT_MOC_LITERAL(282, 23),  // "on_deleteButton_clicked"
        QT_MOC_LITERAL(306, 4),  // "type"
        QT_MOC_LITERAL(311, 21),  // "on_sortOBox_activated"
        QT_MOC_LITERAL(333, 21),  // "on_sortTBox_activated"
        QT_MOC_LITERAL(355, 21),  // "on_sortPBox_activated"
        QT_MOC_LITERAL(377, 22),  // "on_orderButton_clicked"
        QT_MOC_LITERAL(400, 25),  // "on_accountsButton_clicked"
        QT_MOC_LITERAL(426, 23),  // "on_logoutButton_clicked"
        QT_MOC_LITERAL(450, 21)   // "on_findButton_clicked"
    },
    "MainWindow",
    "on_auth_closed",
    "",
    "id",
    "on_ordersButton_clicked",
    "on_passagesButton_clicked",
    "on_transportsButton_clicked",
    "on_tableView_doubleClicked",
    "QModelIndex",
    "index",
    "on_order_change_accepted",
    "on_passage_change_accepted",
    "on_transport_change_accepted",
    "on_account_change_accepted",
    "on_addButton_clicked",
    "on_deleteButton_clicked",
    "type",
    "on_sortOBox_activated",
    "on_sortTBox_activated",
    "on_sortPBox_activated",
    "on_orderButton_clicked",
    "on_accountsButton_clicked",
    "on_logoutButton_clicked",
    "on_findButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  122,    2, 0x0a,    1 /* Public */,
       4,    0,  125,    2, 0x08,    3 /* Private */,
       5,    0,  126,    2, 0x08,    4 /* Private */,
       6,    0,  127,    2, 0x08,    5 /* Private */,
       7,    1,  128,    2, 0x08,    6 /* Private */,
      10,    0,  131,    2, 0x08,    8 /* Private */,
      11,    0,  132,    2, 0x08,    9 /* Private */,
      12,    0,  133,    2, 0x08,   10 /* Private */,
      13,    0,  134,    2, 0x08,   11 /* Private */,
      14,    0,  135,    2, 0x08,   12 /* Private */,
      15,    2,  136,    2, 0x08,   13 /* Private */,
      17,    1,  141,    2, 0x08,   16 /* Private */,
      18,    1,  144,    2, 0x08,   18 /* Private */,
      19,    1,  147,    2, 0x08,   20 /* Private */,
      20,    0,  150,    2, 0x08,   22 /* Private */,
      21,    0,  151,    2, 0x08,   23 /* Private */,
      22,    0,  152,    2, 0x08,   24 /* Private */,
      23,    0,  153,    2, 0x08,   25 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   16,    3,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_auth_closed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ordersButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_passagesButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_transportsButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableView_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_order_change_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_passage_change_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_transport_change_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_account_change_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_addButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_sortOBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_sortTBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_sortPBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_orderButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_accountsButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_logoutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_findButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_auth_closed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->on_ordersButton_clicked(); break;
        case 2: _t->on_passagesButton_clicked(); break;
        case 3: _t->on_transportsButton_clicked(); break;
        case 4: _t->on_tableView_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 5: _t->on_order_change_accepted(); break;
        case 6: _t->on_passage_change_accepted(); break;
        case 7: _t->on_transport_change_accepted(); break;
        case 8: _t->on_account_change_accepted(); break;
        case 9: _t->on_addButton_clicked(); break;
        case 10: _t->on_deleteButton_clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->on_sortOBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_sortTBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->on_sortPBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->on_orderButton_clicked(); break;
        case 15: _t->on_accountsButton_clicked(); break;
        case 16: _t->on_logoutButton_clicked(); break;
        case 17: _t->on_findButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
