/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.5.1
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // D:/ZIP/CSV Read/exampleTable.csv
  0x0,0x0,0x0,0x32,
  0x42,
  0x4d,0x57,0x20,0x20,0x20,0x2c,0x20,0x46,0x35,0x2c,0x33,0x30,0x30,0x30,0x30,0x30,
  0x30,0x2c,0x35,0x35,0xd,0xa,0x4c,0x61,0x64,0x61,0x20,0x20,0x20,0x20,0x20,0x2c,
  0x4b,0x61,0x6c,0x69,0x6e,0x61,0x2c,0x32,0x35,0x30,0x30,0x30,0x30,0x2c,0x34,0xd,
  0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // exampleTable.csv
  0x0,0x10,
  0x1,0xda,0x24,0x46,
  0x0,0x65,
  0x0,0x78,0x0,0x61,0x0,0x6d,0x0,0x70,0x0,0x6c,0x0,0x65,0x0,0x54,0x0,0x61,0x0,0x62,0x0,0x6c,0x0,0x65,0x0,0x2e,0x0,0x63,0x0,0x73,0x0,0x76,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/exampleTable.csv
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_files)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_files)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_files)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_files)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_files)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_files)(); }
   } dummy;
}
