#ifndef JBUFFEREDOUTPUTSTREAM_H
#define JBUFFEREDOUTPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
#include "JFilterOutputStream.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JBufferedOutputStream : public JFilterOutputStream{
        protected:
            vector<jbyte>* buf;
            jint length;
            jint count;
            void flushBuffer();
        public:
            JBufferedOutputStream(JOutputStream* out, jint size=8192);
            static JClass* getClazz();
            virtual void write(jint b);
            virtual void write(jbyte b[], jint off, jint len);
            virtual void flush();
            virtual ~JBufferedOutputStream();
        };
    }
}

#endif // JBUFFEREDOUTPUTSTREAM_H
