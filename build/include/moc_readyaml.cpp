/****************************************************************************
** Meta object code from reading C++ file 'readyaml.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/readyaml.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'readyaml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReadYaml_t {
    QByteArrayData data[15];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReadYaml_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReadYaml_t qt_meta_stringdata_ReadYaml = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ReadYaml"
QT_MOC_LITERAL(1, 9, 13), // "onImageLoader"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "width"
QT_MOC_LITERAL(4, 30, 6), // "height"
QT_MOC_LITERAL(5, 37, 15), // "sourcesizeWidth"
QT_MOC_LITERAL(6, 53, 16), // "sourcesizeHeight"
QT_MOC_LITERAL(7, 70, 10), // "shapeWidth"
QT_MOC_LITERAL(8, 81, 11), // "shapeHeight"
QT_MOC_LITERAL(9, 93, 8), // "readYaml"
QT_MOC_LITERAL(10, 102, 8), // "filePath"
QT_MOC_LITERAL(11, 111, 12), // "getYamlValue"
QT_MOC_LITERAL(12, 124, 22), // "getConvertPixelToMeter"
QT_MOC_LITERAL(13, 147, 1), // "x"
QT_MOC_LITERAL(14, 149, 1) // "y"

    },
    "ReadYaml\0onImageLoader\0\0width\0height\0"
    "sourcesizeWidth\0sourcesizeHeight\0"
    "shapeWidth\0shapeHeight\0readYaml\0"
    "filePath\0getYamlValue\0getConvertPixelToMeter\0"
    "x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReadYaml[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    6,   34,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,   47,    2, 0x02 /* Public */,
      11,    0,   50,    2, 0x02 /* Public */,
      12,    2,   51,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::QVariantMap,
    QMetaType::QVariantList, QMetaType::Double, QMetaType::Double,   13,   14,

       0        // eod
};

void ReadYaml::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReadYaml *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onImageLoader((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5])),(*reinterpret_cast< const int(*)>(_a[6]))); break;
        case 1: _t->readYaml((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { QVariantMap _r = _t->getYamlValue();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariantList _r = _t->getConvertPixelToMeter((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ReadYaml::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ReadYaml.data,
    qt_meta_data_ReadYaml,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReadYaml::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReadYaml::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReadYaml.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ReadYaml::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
