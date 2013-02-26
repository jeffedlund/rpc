#ifndef OBJECT_H
#define OBJECT_H

#include <QtGlobal>
namespace jcpp{
    namespace lang{
        //TODO is it correct values cross OS?
        #define jint qint32
        #define juint quint32
        #define jbool bool
        #define jbyte qint8
        #define jubyte quint8
        #define jchar quint16
        #define jdouble double
        #define jfloat float
        #define jlong qint64
        #define julong quint64
        #define jshort qint16
        #define jushort quint16
    }
}

#endif // OBJECT_H
