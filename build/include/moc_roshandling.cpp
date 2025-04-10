/****************************************************************************
** Meta object code from reading C++ file 'roshandling.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/roshandling.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'roshandling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RosHandling_t {
    QByteArrayData data[29];
    char stringdata0[402];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RosHandling_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RosHandling_t qt_meta_stringdata_RosHandling = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RosHandling"
QT_MOC_LITERAL(1, 12, 16), // "robotPoseChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "waypointsChanged"
QT_MOC_LITERAL(4, 47, 12), // "speedChanged"
QT_MOC_LITERAL(5, 60, 20), // "batteryStatusChanged"
QT_MOC_LITERAL(6, 81, 23), // "estimateDistanceChanged"
QT_MOC_LITERAL(7, 105, 24), // "remainingDistanceChanged"
QT_MOC_LITERAL(8, 130, 21), // "updateRosDataReceived"
QT_MOC_LITERAL(9, 152, 5), // "topic"
QT_MOC_LITERAL(10, 158, 3), // "msg"
QT_MOC_LITERAL(11, 162, 22), // "publishVelocityCommand"
QT_MOC_LITERAL(12, 185, 8), // "linear_x"
QT_MOC_LITERAL(13, 194, 9), // "angular_z"
QT_MOC_LITERAL(14, 204, 11), // "publishGoal"
QT_MOC_LITERAL(15, 216, 5), // "index"
QT_MOC_LITERAL(16, 222, 18), // "publishMoveCommand"
QT_MOC_LITERAL(17, 241, 4), // "data"
QT_MOC_LITERAL(18, 246, 18), // "publishHermitePath"
QT_MOC_LITERAL(19, 265, 18), // "publishVirtualWall"
QT_MOC_LITERAL(20, 284, 17), // "getRobotPosePixel"
QT_MOC_LITERAL(21, 302, 1), // "x"
QT_MOC_LITERAL(22, 304, 1), // "y"
QT_MOC_LITERAL(23, 306, 14), // "clearWaypoints"
QT_MOC_LITERAL(24, 321, 17), // "robotPoseMeterQml"
QT_MOC_LITERAL(25, 339, 12), // "waypointsQml"
QT_MOC_LITERAL(26, 352, 8), // "speedQml"
QT_MOC_LITERAL(27, 361, 19), // "estimateDistanceQml"
QT_MOC_LITERAL(28, 381, 20) // "remainingDistanceQml"

    },
    "RosHandling\0robotPoseChanged\0\0"
    "waypointsChanged\0speedChanged\0"
    "batteryStatusChanged\0estimateDistanceChanged\0"
    "remainingDistanceChanged\0updateRosDataReceived\0"
    "topic\0msg\0publishVelocityCommand\0"
    "linear_x\0angular_z\0publishGoal\0index\0"
    "publishMoveCommand\0data\0publishHermitePath\0"
    "publishVirtualWall\0getRobotPosePixel\0"
    "x\0y\0clearWaypoints\0robotPoseMeterQml\0"
    "waypointsQml\0speedQml\0estimateDistanceQml\0"
    "remainingDistanceQml"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RosHandling[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       5,  114, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    0,   87,    2, 0x06 /* Public */,
       6,    0,   88,    2, 0x06 /* Public */,
       7,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   90,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      11,    2,   95,    2, 0x02 /* Public */,
      14,    1,  100,    2, 0x02 /* Public */,
      16,    1,  103,    2, 0x02 /* Public */,
      18,    0,  106,    2, 0x02 /* Public */,
      19,    0,  107,    2, 0x02 /* Public */,
      20,    2,  108,    2, 0x02 /* Public */,
      23,    0,  113,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,    9,   10,

 // methods: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QVariantList, QMetaType::Double, QMetaType::Double,   21,   22,
    QMetaType::Void,

 // properties: name, type, flags
      24, QMetaType::QVariantList, 0x00495001,
      25, QMetaType::QVariantList, 0x00495001,
      26, QMetaType::QVariantList, 0x00495001,
      27, QMetaType::Double, 0x00495001,
      28, QMetaType::Double, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       4,
       5,

       0        // eod
};

void RosHandling::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RosHandling *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->robotPoseChanged(); break;
        case 1: _t->waypointsChanged(); break;
        case 2: _t->speedChanged(); break;
        case 3: _t->batteryStatusChanged(); break;
        case 4: _t->estimateDistanceChanged(); break;
        case 5: _t->remainingDistanceChanged(); break;
        case 6: _t->updateRosDataReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 7: _t->publishVelocityCommand((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->publishGoal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 9: _t->publishMoveCommand((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->publishHermitePath(); break;
        case 11: _t->publishVirtualWall(); break;
        case 12: { QVariantList _r = _t->getRobotPosePixel((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->clearWaypoints(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::robotPoseChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::waypointsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::speedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::batteryStatusChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::estimateDistanceChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RosHandling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RosHandling::remainingDistanceChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<RosHandling *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->getRobotPoseMeterQml(); break;
        case 1: *reinterpret_cast< QVariantList*>(_v) = _t->getWaypointsQml(); break;
        case 2: *reinterpret_cast< QVariantList*>(_v) = _t->speedQml(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->getEstimateDistanceQml(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->getRemainingDistanceQml(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject RosHandling::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_RosHandling.data,
    qt_meta_data_RosHandling,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RosHandling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RosHandling::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RosHandling.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RosHandling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RosHandling::robotPoseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RosHandling::waypointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RosHandling::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void RosHandling::batteryStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void RosHandling::estimateDistanceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void RosHandling::remainingDistanceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
