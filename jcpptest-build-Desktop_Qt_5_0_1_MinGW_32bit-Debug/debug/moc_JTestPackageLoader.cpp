/****************************************************************************
** Meta object code from reading C++ file 'JTestPackageLoader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jcpp/src/test/cpp/jcpp/JTestPackageLoader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JTestPackageLoader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JTestPackageLoader_t {
    QByteArrayData data[1];
    char stringdata[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_JTestPackageLoader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_JTestPackageLoader_t qt_meta_stringdata_JTestPackageLoader = {
    {
QT_MOC_LITERAL(0, 0, 18)
    },
    "JTestPackageLoader\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JTestPackageLoader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void JTestPackageLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JTestPackageLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JTestPackageLoader.data,
      qt_meta_data_JTestPackageLoader,  qt_static_metacall, 0, 0}
};


const QMetaObject *JTestPackageLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JTestPackageLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JTestPackageLoader.stringdata))
        return static_cast<void*>(const_cast< JTestPackageLoader*>(this));
    if (!strcmp(_clname, "JIPackageLoader"))
        return static_cast< JIPackageLoader*>(const_cast< JTestPackageLoader*>(this));
    if (!strcmp(_clname, "jipackageloader"))
        return static_cast< jcpp::lang::reflect::JIPackageLoader*>(const_cast< JTestPackageLoader*>(this));
    return QObject::qt_metacast(_clname);
}

int JTestPackageLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    0x71, 0x62, 0x6a, 0x73, 0x01, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 0x49, 0x49, 0x44, 0x00, 0x00, 0x00,
    0x12, 0x00, 0x6a, 0x74, 0x65, 0x73, 0x74, 0x70,
    0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x6c, 0x6f,
    0x61, 0x64, 0x65, 0x72, 0x9b, 0x07, 0x00, 0x00,
    0x09, 0x00, 0x63, 0x6c, 0x61, 0x73, 0x73, 0x4e,
    0x61, 0x6d, 0x65, 0x00, 0x12, 0x00, 0x4a, 0x54,
    0x65, 0x73, 0x74, 0x50, 0x61, 0x63, 0x6b, 0x61,
    0x67, 0x65, 0x4c, 0x6f, 0x61, 0x64, 0x65, 0x72,
    0x3a, 0x00, 0xa0, 0x00, 0x07, 0x00, 0x76, 0x65,
    0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 0x64, 0x65,
    0x62, 0x75, 0x67, 0x00, 0x95, 0x0f, 0x00, 0x00,
    0x08, 0x00, 0x4d, 0x65, 0x74, 0x61, 0x44, 0x61,
    0x74, 0x61, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
    0x2c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
    0x50, 0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    0x71, 0x62, 0x6a, 0x73, 0x01, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 0x49, 0x49, 0x44, 0x00, 0x00, 0x00,
    0x12, 0x00, 0x6a, 0x74, 0x65, 0x73, 0x74, 0x70,
    0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x6c, 0x6f,
    0x61, 0x64, 0x65, 0x72, 0x95, 0x07, 0x00, 0x00,
    0x08, 0x00, 0x4d, 0x65, 0x74, 0x61, 0x44, 0x61,
    0x74, 0x61, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1b, 0x0b, 0x00, 0x00, 0x09, 0x00, 0x63, 0x6c,
    0x61, 0x73, 0x73, 0x4e, 0x61, 0x6d, 0x65, 0x00,
    0x12, 0x00, 0x4a, 0x54, 0x65, 0x73, 0x74, 0x50,
    0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0x4c, 0x6f,
    0x61, 0x64, 0x65, 0x72, 0x31, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x64, 0x65, 0x62, 0x75, 0x67, 0x00,
    0x3a, 0x00, 0xa0, 0x00, 0x07, 0x00, 0x76, 0x65,
    0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x48, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
    0x78, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(JTestPackageLoader, JTestPackageLoader)

QT_END_MOC_NAMESPACE
