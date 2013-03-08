#ifndef JINPUTSTREAM_H
#define JINPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        //TODO create JInputStreamAdapter(JInputStream), same for out+socket+serversocket
        class JCPP_LIBRARY_EXPORT JInputStream : public JObject{
        protected:
            static const int SKIP_BUFFER_SIZE = 2048;
            jbyte* skipBuffer;
            JInputStream(JClass* _class);

        public:
            JInputStream();

            static JClass* getClazz();

            virtual jlong available()=0;
            virtual bool waitForReadyRead(int = 30000)=0;
            virtual jbyte read()=0;
            virtual jbyte peekByte()=0;//TODO create a JPeekInputStream
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint read(jbyte b[], int off, int len);
            virtual jlong skip(jlong n);
            virtual void mark(int readlimit);
            virtual void reset();
            virtual bool markSupported();
            virtual void close()=0;
            virtual ~JInputStream();
        };
    }
}

#endif // JINPUTSTREAM_H
