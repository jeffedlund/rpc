#ifndef JDATAINPUTSTREAM_H
#define JDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JClass.h"
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JDataInputStream : public JInputStream{
            JInputStream *in;

        public:
            JDataInputStream();
            JDataInputStream(JInputStream *in);

            static JClass* getClazz();

            void setInputStream(JInputStream *in);

            void readFully(jbyte b[], jint off, jint len);
            virtual string readUTF();

            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jbyte read();
            virtual jint read(jbyte b[], int off, int len);
            virtual jbyte peekByte();
            virtual jbyte readByte();
            virtual jshort readShort();
            virtual jshort readUnsignedShort();
            virtual jint readInt();
            virtual jlong readLong();
            virtual jfloat readFloat();
            virtual jdouble readDouble();
            virtual jchar readChar();
            virtual jbool readBool();
            virtual void close();
            virtual ~JDataInputStream();
        };
    }
}

#endif // JDATAINPUTSTREAM_H
