#ifndef JFILTERINPUTSTREAM_H
#define JFILTERINPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
#include "JInputStream.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFilterInputStream : public JInputStream{
        protected:
            JInputStream* in;
            JFilterInputStream(JInputStream* in,JClass* _class);

        public:
            static JClass* getClazz();
            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jbyte read();
            virtual jbyte peekByte();
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint read(jbyte b[], int off, int len);
            virtual jlong skip(jlong n);
            virtual void mark(int readlimit);
            virtual void reset();
            virtual bool markSupported();
            virtual void close();
            virtual ~JFilterInputStream();
        };
    }
}


#endif // JFILTERINPUTSTREAM_H
