#ifndef JDATAOUTPUTSTREAM_H
#define JDATAOUTPUTSTREAM_H

#include <QDataStream>
#include "JOutputStream.h"
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JDataOutputStream : public JOutputStream{
        private:
            jint length;
            jbyte* bytearr;
            jbyte writeBuffer[8];
            jint written;
            void incCount(jint value);

        protected:
            JOutputStream* out;

        public:
            JDataOutputStream();
            JDataOutputStream(JOutputStream* out);
            static JClass* getClazz();
            void setOutputStream(JOutputStream* out);
            virtual void write(jbyte b);
            virtual void write(jbyte b[], int off, int len);
            virtual void flush() ;
            virtual void close();

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
            virtual jint writeUTF(string str, JOutputStream* out);
            virtual jint size();
            virtual ~JDataOutputStream();
        };
    }
}

#endif // JDATAOUTPUTSTREAM_H