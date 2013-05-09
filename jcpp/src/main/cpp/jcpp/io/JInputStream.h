#ifndef JINPUTSTREAM_H
#define JINPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        //TODO create socket+serversocket adapeters?
        class JCPP_LIBRARY_EXPORT JInputStream : public JObject{
        protected:
            static const jint SKIP_BUFFER_SIZE = 2048;
            jbyte* skipBuffer;
            JInputStream(JClass* _class);

        public:
            JInputStream();
            static JClass* getClazz();
            virtual jint available()=0;
            virtual jint read()=0;
            virtual jint peek()=0;//TODO create a JPeekInputStream
            virtual jbyte peekByte();
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint read(jbyte b[], jint off, jint len);
            virtual jlong skip(jlong n);
            virtual void mark(jint readlimit);
            virtual void reset();
            virtual jbool markSupported();
            virtual void close()=0;
            virtual ~JInputStream();
        };
    }
}

#endif // JINPUTSTREAM_H
