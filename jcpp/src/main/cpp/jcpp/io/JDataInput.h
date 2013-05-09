#ifndef JDATAINPUT_H
#define JDATAINPUT_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
#include "JClass.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveShort.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JDataInput : public JInterface{
        public:
            static JClass* getClazz();
            virtual void readFully(jbyte b[], jint off, jint len)=0;
            virtual jint skipBytes(jint n)=0;
            virtual jbool readBool()=0;
            virtual jbyte readByte()=0;
            virtual jint readUnsignedByte()=0;
            virtual jshort readShort()=0;
            virtual jint readUnsignedShort()=0;
            virtual jchar readChar()=0;
            virtual jint readInt()=0;
            virtual jlong readLong()=0;
            virtual jfloat readFloat()=0;
            virtual jdouble readDouble()=0;
            virtual JString readUTF()=0;
            virtual JPrimitiveByte* readPrimitiveByte()=0;
            virtual JPrimitiveChar* readPrimitiveChar()=0;
            virtual JPrimitiveDouble* readPrimitiveDouble()=0;
            virtual JPrimitiveFloat* readPrimitiveFloat()=0;
            virtual JPrimitiveInt* readPrimitiveInt()=0;
            virtual JPrimitiveLong* readPrimitiveLong()=0;
            virtual JPrimitiveShort* readPrimitiveShort()=0;
            virtual JPrimitiveBoolean* readPrimitiveBool()=0;
            virtual ~JDataInput();
        };
    }
}

#endif // JDATAINPUT_H
