/****************************************************************************
** Meta object code from reading C++ file 'viewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/websocket/viewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewModel_t {
    QByteArrayData data[24];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewModel_t qt_meta_stringdata_ViewModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ViewModel"
QT_MOC_LITERAL(1, 10, 16), // "robotPoseChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "batteryStatusChanged"
QT_MOC_LITERAL(4, 49, 16), // "waypointsChanged"
QT_MOC_LITERAL(5, 66, 13), // "onImageLoader"
QT_MOC_LITERAL(6, 80, 5), // "width"
QT_MOC_LITERAL(7, 86, 6), // "height"
QT_MOC_LITERAL(8, 93, 15), // "sourcesizeWidth"
QT_MOC_LITERAL(9, 109, 16), // "sourcesizeHeight"
QT_MOC_LITERAL(10, 126, 13), // "updateRosData"
QT_MOC_LITERAL(11, 140, 5), // "topic"
QT_MOC_LITERAL(12, 146, 3), // "msg"
QT_MOC_LITERAL(13, 150, 19), // "sendVelocityCommand"
QT_MOC_LITERAL(14, 170, 8), // "linear_x"
QT_MOC_LITERAL(15, 179, 9), // "angular_z"
QT_MOC_LITERAL(16, 189, 8), // "sendGoal"
QT_MOC_LITERAL(17, 198, 5), // "index"
QT_MOC_LITERAL(18, 204, 15), // "sendMoveCommand"
QT_MOC_LITERAL(19, 220, 4), // "data"
QT_MOC_LITERAL(20, 225, 12), // "getWaypoints"
QT_MOC_LITERAL(21, 238, 9), // "robotPose"
QT_MOC_LITERAL(22, 248, 13), // "batteryStatus"
QT_MOC_LITERAL(23, 262, 12) // "waypointsQml"

    },
    "ViewModel\0robotPoseChanged\0\0"
    "batteryStatusChanged\0waypointsChanged\0"
    "onImageLoader\0width\0height\0sourcesizeWidth\0"
    "sourcesizeHeight\0updateRosData\0topic\0"
    "msg\0sendVelocityCommand\0linear_x\0"
    "angular_z\0sendGoal\0index\0sendMoveCommand\0"
    "data\0getWaypoints\0robotPose\0batteryStatus\0"
    "waypointsQml"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   88, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    4,   62,    2, 0x0a /* Public */,
      10,    2,   71,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      13,    2,   76,    2, 0x02 /* Public */,
      16,    1,   81,    2, 0x02 /* Public */,
      18,    1,   84,    2, 0x02 /* Public */,
      20,    0,   87,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,   11,   12,

 // methods: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::QVariantList,

 // properties: name, type, flags
      21, QMetaType::QVariantMap, 0x00495001,
      22, QMetaType::Float, 0x00495001,
      23, QMetaType::QVariantList, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void ViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->robotPoseChanged(); break;
        case 1: _t->batteryStatusChanged(); break;
        case 2: _t->waypointsChanged(); break;
        case 3: _t->onImageLoader((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 4: _t->updateRosData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 5: _t->sendVelocityCommand((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: _t->sendGoal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->sendMoveCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { QVariantList _r = _t->getWaypoints();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::robotPoseChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::batteryStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::waypointsChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ViewModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = _t->robotPose(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->batteryStatus(); break;
        case 2: *reinterpret_cast< QVariantList*>(_v) = _t->getWaypoints(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ViewModel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ViewModel.data,
    qt_meta_data_ViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ViewModel::robotPoseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ViewModel::batteryStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ViewModel::waypointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
