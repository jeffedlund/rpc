#include "JSerializableTest.h"
#include "JSampleObject.h"

namespace jcpp{
    namespace io{
        JSerializableTest::JSerializableTest():JTest(){
        }

        JString JSerializableTest::getFileName(){
            return "Serializable.ser";
        }

        JObject* JSerializableTest::testReflect(){
            JSampleObject* o=new JSampleObject();
            o->setBool1(new JPrimitiveBoolean(false));
            o->setByte1(new JPrimitiveByte(123));
            o->setC1(new JPrimitiveChar('c'));
            o->setD1(new JPrimitiveDouble(456));
            o->setF1(new JPrimitiveFloat(789));
            o->setL1(new JPrimitiveLong(124));
            o->setS1(new JPrimitiveShort(235));
            o->setI1(new JPrimitiveInt(345));
            return o;
        }

        JSerializableTest::~JSerializableTest(){
        }
    }
}








