#ifndef JSAMPLEOBJECT_H
#define JSAMPLEOBJECT_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"

class JSampleObject : public JObject{
private:
    JPrimitiveBoolean* bool1;
    JPrimitiveByte* byte1;
    JPrimitiveChar* c1;
    JPrimitiveDouble* d1;
    JPrimitiveFloat* f1;
    JPrimitiveLong* l1;
    JPrimitiveShort* s1;
    JPrimitiveInt* i1;

public:
    JSampleObject();

    static JClass* getClazz();

    JPrimitiveBoolean* getBool1();

    void setBool1(JPrimitiveBoolean* bool1);

    JPrimitiveByte* getByte1();

    void setByte1(JPrimitiveByte* byte1);

    JPrimitiveChar* getC1();

    void setC1(JPrimitiveChar* c1);

    JPrimitiveDouble* getD1();

    void setD1(JPrimitiveDouble* d1);

    JPrimitiveFloat* getF1();

    void setF1(JPrimitiveFloat* f1);

    JPrimitiveLong* getL1();

    void setL1(JPrimitiveLong* l1);

    JPrimitiveShort* getS1();

    void setS1(JPrimitiveShort* s1);

    JPrimitiveInt* getI1();

    void setI1(JPrimitiveInt* i1);

    string toString();

    ~JSampleObject();
};

#endif // JSAMPLEOBJECT_H
