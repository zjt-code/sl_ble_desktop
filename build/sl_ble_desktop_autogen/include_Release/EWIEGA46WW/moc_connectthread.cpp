/****************************************************************************
** Meta object code from reading C++ file 'connectthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../connectthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectThread_t {
    QByteArrayData data[10];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectThread_t qt_meta_stringdata_ConnectThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConnectThread"
QT_MOC_LITERAL(1, 14, 18), // "SignalBleDebugInfo"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "std::string"
QT_MOC_LITERAL(4, 46, 9), // "debuginfo"
QT_MOC_LITERAL(5, 56, 19), // "SignalBleMeasNotify"
QT_MOC_LITERAL(6, 76, 24), // "std::vector<T_CGMS_DATA>"
QT_MOC_LITERAL(7, 101, 7), // "payload"
QT_MOC_LITERAL(8, 109, 17), // "SignalMeasureData"
QT_MOC_LITERAL(9, 127, 1) // "x"

    },
    "ConnectThread\0SignalBleDebugInfo\0\0"
    "std::string\0debuginfo\0SignalBleMeasNotify\0"
    "std::vector<T_CGMS_DATA>\0payload\0"
    "SignalMeasureData\0x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,
       8,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Float,    9,

       0        // eod
};

void ConnectThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalBleDebugInfo((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->SignalBleMeasNotify((*reinterpret_cast< std::vector<T_CGMS_DATA>(*)>(_a[1]))); break;
        case 2: _t->SignalMeasureData((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectThread::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectThread::SignalBleDebugInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectThread::*)(std::vector<T_CGMS_DATA> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectThread::SignalBleMeasNotify)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConnectThread::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectThread::SignalMeasureData)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ConnectThread.data,
    qt_meta_data_ConnectThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ConnectThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ConnectThread::SignalBleDebugInfo(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectThread::SignalBleMeasNotify(std::vector<T_CGMS_DATA> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectThread::SignalMeasureData(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
