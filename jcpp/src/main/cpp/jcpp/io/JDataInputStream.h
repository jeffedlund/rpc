#ifndef JDATAINPUTSTREAM_H
#define JDATAINPUTSTREAM_H

#include "JInputStream.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
#include "JFilterInputStream.h"
using namespace std;

namespace jcpp{
    namespace io{
        //TODO implement readLine
        class JCPP_LIBRARY_EXPORT JDataInputStream : public JFilterInputStream{

        public:
            JDataInputStream();
            JDataInputStream(JInputStream *in);

            static JClass* getClazz();

            void setInputStream(JInputStream *in);
            virtual jint read(jbyte b[], int off, int len);
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint skipBytes(jint n);
            virtual jbool readBool();
            virtual jbyte readByte();
            virtual jint readUnsignedByte();
            virtual jshort readShort();
            virtual jint readUnsignedShort();
            virtual jchar readChar();
            virtual jint readInt();
            virtual jlong readLong();
            virtual jfloat readFloat();
            virtual jdouble readDouble();
            virtual string readUTF();
            virtual jint available();
            virtual bool waitForReadyRead(int = 30000);//TODO use readtimeout
            virtual jint peek();
            virtual void close();
            virtual ~JDataInputStream();
        };
    }
}

#endif // JDATAINPUTSTREAM_H
