#ifndef JDATAOUTPUTSTREAM_H
#define JDATAOUTPUTSTREAM_H

#include <QDataStream>
#include "JOutputStream.h"
#include "Object.h"
#include "JCPP.h"
#include "JFilterOutputStream.h"
#include "JDataOutput.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveShort.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JDataOutputStream : public JFilterOutputStream, public JDataOutput{
        private:
            jint length;
            jbyte* bytearr;
            jbyte writeBuffer[8];
            jint written;
            void incCount(jint value);

        public:
            JDataOutputStream();
            JDataOutputStream(JOutputStream* out);
            static JClass* getClazz();
            void setOutputStream(JOutputStream* out);
            virtual void write(jint b);
            virtual void write(jbyte b[], int off, int len);
            virtual void flush() ;
            virtual void close();
            virtual void writeBoolean(jbool v);
            virtual void writeByte(jint v);
            virtual void writeShort(jint v);
            virtual void writeChar(jint v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual void writeBoolean(JPrimitiveBoolean* v);
            virtual void writeByte(JPrimitiveByte* v);
            virtual void writeShort(JPrimitiveShort* v);
            virtual void writeChar(JPrimitiveChar* v);
            virtual void writeInt(JPrimitiveInt* v);
            virtual void writeLong(JPrimitiveLong* v);
            virtual void writeFloat(JPrimitiveFloat* v);
            virtual void writeDouble(JPrimitiveDouble* v);
            virtual void writeBytes(string s);
            virtual void writeChars(string s);
            virtual void writeUTF(string str);
            virtual jint writeUTF(string str, JOutputStream* out);
            virtual jint size();
            virtual ~JDataOutputStream();
        };
    }
}

#endif // JDATAOUTPUTSTREAM_H
