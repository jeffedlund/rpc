#ifndef JDATAOUTPUT_H
#define JDATAOUTPUT_H

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
        class JCPP_LIBRARY_EXPORT JDataOutput : public JInterface{
        public:
            static JClass* getClazz();
            virtual void write(jint b)=0;
            virtual void write(jbyte b[], jint off, jint len)=0;
            virtual void writeBoolean(jbool v)=0;
            virtual void writeBoolean(JPrimitiveBoolean* v)=0;
            virtual void writeByte(jint v)=0;
            virtual void writeByte(JPrimitiveByte* v)=0;
            virtual void writeShort(jint v)=0;
            virtual void writeShort(JPrimitiveShort* v)=0;
            virtual void writeChar(jint v)=0;
            virtual void writeChar(JPrimitiveChar* v)=0;
            virtual void writeInt(jint v)=0;
            virtual void writeInt(JPrimitiveInt* v)=0;
            virtual void writeLong(jlong v)=0;
            virtual void writeLong(JPrimitiveLong* v)=0;
            virtual void writeFloat(jfloat v)=0;
            virtual void writeFloat(JPrimitiveFloat* v)=0;
            virtual void writeDouble(jdouble v)=0;
            virtual void writeDouble(JPrimitiveDouble* v)=0;
            virtual void writeBytes(string s)=0;
            virtual void writeChars(string s)=0;
            virtual void writeUTF(string str)=0;
            virtual ~JDataOutput();
        };
    }
}

#endif // JDATAOUTPUT_H
