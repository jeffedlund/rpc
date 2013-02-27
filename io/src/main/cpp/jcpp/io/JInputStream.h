#ifndef JINPUTSTREAM_H
#define JINPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        //TODO implement skip(long n),mark,reset,markSupported
        //TODO create JInputStreamAdapter(JInputStream), same for out+socket+serversocket
        class JInputStream : public JObject{
        protected:
            JInputStream(JClass* _class);

        public:
            JInputStream();

            static JClass* getClazz();

            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jbyte read();
            virtual jint read(jbyte b[], int off, int len);
            virtual jbyte peekByte();
            virtual jbyte readByte();
            virtual jshort readShort();
            virtual jushort readUnsignedShort();
            virtual jint readInt();
            virtual jlong readLong();
            virtual jfloat readFloat();
            virtual jdouble readDouble();
            virtual jchar readChar();
            virtual jbool readBool();
            virtual void close();
            virtual ~JInputStream();
        };
    }
}

#endif // JINPUTSTREAM_H
