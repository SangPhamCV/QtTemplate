/****************************************************************************
** Meta object code from reading C++ file 'hermitecurve.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/hermitecurve.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hermitecurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HermiteCurve_t {
    QByteArrayData data[13];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HermiteCurve_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HermiteCurve_t qt_meta_stringdata_HermiteCurve = {
    {
QT_MOC_LITERAL(0, 0, 12), // "HermiteCurve"
QT_MOC_LITERAL(1, 13, 18), // "curvePointsChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "clearLamdmarkPoints"
QT_MOC_LITERAL(4, 53, 16), // "clearCurvePoints"
QT_MOC_LITERAL(5, 70, 11), // "removePoint"
QT_MOC_LITERAL(6, 82, 5), // "index"
QT_MOC_LITERAL(7, 88, 8), // "addPoint"
QT_MOC_LITERAL(8, 97, 1), // "x"
QT_MOC_LITERAL(9, 99, 1), // "y"
QT_MOC_LITERAL(10, 101, 11), // "updatePoint"
QT_MOC_LITERAL(11, 113, 11), // "createCurve"
QT_MOC_LITERAL(12, 125, 14) // "curvePointsQml"

    },
    "HermiteCurve\0curvePointsChanged\0\0"
    "clearLamdmarkPoints\0clearCurvePoints\0"
    "removePoint\0index\0addPoint\0x\0y\0"
    "updatePoint\0createCurve\0curvePointsQml"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HermiteCurve[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x02 /* Public */,
       4,    0,   51,    2, 0x02 /* Public */,
       5,    1,   52,    2, 0x02 /* Public */,
       7,    2,   55,    2, 0x02 /* Public */,
      10,    3,   60,    2, 0x02 /* Public */,
      11,    0,   67,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    6,    8,    9,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QVariantList, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void HermiteCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HermiteCurve *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->curvePointsChanged(); break;
        case 1: _t->clearLamdmarkPoints(); break;
        case 2: _t->clearCurvePoints(); break;
        case 3: _t->removePoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->addPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->updatePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 6: _t->createCurve(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HermiteCurve::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HermiteCurve::curvePointsChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<HermiteCurve *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->getCurvePointsQml(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject HermiteCurve::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_HermiteCurve.data,
    qt_meta_data_HermiteCurve,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HermiteCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HermiteCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HermiteCurve.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HermiteCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void HermiteCurve::curvePointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
