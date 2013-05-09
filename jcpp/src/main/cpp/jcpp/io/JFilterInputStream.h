#ifndef JFILTERINPUTSTREAM_H
#define JFILTERINPUTSTREAM_H

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
            virtual jint available();
            virtual jint read();
            virtual jint peek();
            virtual void readFully(jbyte b[], jint off, jint len);
            virtual jint read(jbyte b[], jint off, jint len);
            virtual jlong skip(jlong n);
            virtual void mark(jint readlimit);
            virtual void reset();
            virtual jbool markSupported();
            virtual void close();
            virtual ~JFilterInputStream();
        };
    }
}


#endif // JFILTERINPUTSTREAM_H
