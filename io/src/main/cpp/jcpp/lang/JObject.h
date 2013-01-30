#ifndef JOBJECT_H
#define JOBJECT_H

class JClass;

#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

//TODO creer tous les primitives+wrapper type de Java
/*
simpleboolean, boolean      =>bool
simpleByte, Byte            => qint8
simplecharacter, character  =>char
simpledouble, double        =>double
simplefloat, float          =>float
simpleinteger, integer      =>qint32
simplelong, long            =>qint64
simpleshort, short          =>qint16


*/
class JObject{

    protected:
        JClass* _class;
        JObject(JClass* _class);

    public:
        JObject();

        static JClass* clazz;

        JClass* getClass();

        qint64 getSerialVersionUID();

        string toString();

        ~JObject();
};

#endif // JOBJECT_H
