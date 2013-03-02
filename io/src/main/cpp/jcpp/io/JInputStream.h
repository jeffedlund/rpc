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

            virtual jlong available()=0;
            virtual bool waitForReadyRead(int = 30000)=0;
            virtual jbyte read()=0;
            virtual jbyte peekByte()=0;//TODO not ideal
            virtual jint read(jbyte b[], int off, int len);
            virtual void close()=0;
            virtual ~JInputStream();
        };
    }
}

#endif // JINPUTSTREAM_H
