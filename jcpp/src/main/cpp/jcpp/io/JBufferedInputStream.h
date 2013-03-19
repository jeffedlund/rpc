#ifndef JBUFFEREDINPUTSTREAM_H
#define JBUFFEREDINPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
#include "JFilterInputStream.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JBufferedInputStream : public JFilterInputStream{
        protected:
            vector<jbyte>* buf;
            jint length;
            jint count;
            jint pos;
            jint markpos;
            jint marklimit;
            JInputStream* getInIfOpen();
            vector<jbyte>* getBufIfOpen();
            void fill();
            jint read1(jbyte b[], jint off, jint len);

        public:
            JBufferedInputStream(JInputStream* in, jint size=8192);
            static JClass* getClazz();
            virtual jbyte read();
            virtual jint read(jbyte b[], int off, int len);
            virtual jlong skip(jlong n);
            virtual jlong available();
            virtual bool waitForReadyRead(int = 30000);
            virtual jbyte peekByte();
            virtual void mark(int readlimit);
            virtual void reset();
            virtual bool markSupported();
            virtual void close();
            virtual ~JBufferedInputStream();
        };
    }
}

#endif // JBUFFEREDINPUTSTREAM_H