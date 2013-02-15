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
            void write(jint b);
            void write(jbyte b[], int off, int len);
            void flush() ;
            void close();

            virtual void writeBoolean(bool v);
            virtual void writeByte(jbyte v);
            virtual void writeShort(jshort v);
            virtual void writeChar(jushort v);
            virtual void writeInt(jint v);
            virtual void writeLong(jlong v);
            virtual void writeFloat(float v);
            virtual void writeDouble(double v);
            virtual void writeBytes(std::string s);
            virtual void writeChars(std::string s);
            virtual void writeUTF(std::string str);
            jint writeUTF(std::string str, JOutputStream* out);
            jint size();
            ~JDataOutputStream();
        };
    }
}

#endif // JDATAOUTPUTSTREAM_H
