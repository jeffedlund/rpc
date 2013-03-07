#ifndef JCPP_H
#define JCPP_H
#include <QtCore/QtGlobal>

 #if defined(JCPP_LIBRARY)
 #  define JCPP_LIBRARY_EXPORT Q_DECL_EXPORT
 #else
 #  define JCPP_LIBRARY_EXPORT Q_DECL_IMPORT
 #endif


#endif // JCPP_H
