#ifndef JDATAOUTPUTSTREAM_H
#define JDATAOUTPUTSTREAM_H

#include <QDataStream>
#include "JOutputStream.h"
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JDataOutputStream : public JOutputStream{
        private:
            jint length;
            jbyte* bytearr;
            void incCount(jint value);
            jbyte writeBuffer[8];
        protected:
            JOutputStream* out;
            jint written;

        public:
            JDataOutputStream();
            JDataOutputStream(JOutputStream* out);
            static JClass* getClazz();
            void setOutputStream(JOutputStream* out);
            void write(jbyte b);
            void write(jbyte b[], int off, int len);
            void flush() ;
            void close();

            virtual void writeBoolean(jbool v);
            virtual void writeByte(jbyte v);
            virtual void writeShort(jshort v);
            virtual void writeChar(jchar v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(jfloat v);
            virtual void writeDouble(jdouble v);
            virtual void writeBytes(string s);
            virtual void writeChars(string s);
            virtual void writeUTF(string str);
            jint writeUTF(string str, JOutputStream* out);
            jint size();
            virtual ~JDataOutputStream();
        };
    }
}

#endif // JDATAOUTPUTSTREAM_H
