#ifndef JBYTEARRAYOUTPUTSTREAM_H
#define JBYTEARRAYOUTPUTSTREAM_H

#include "JString.h"
#include "JOutputStream.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JByteArrayOutputStream : public JOutputStream  {
            protected:
                vector<jbyte>* buf;

            public:
                static JClass* getClazz();
                JByteArrayOutputStream();
                virtual void  write(jint b);
                virtual void  write(jbyte b[], jint off, jint l);
                virtual void  writeTo(JOutputStream* out);
                virtual void  reset();
                virtual vector<jbyte>* toByteArray();
                virtual jint size();
                virtual string toString();
                virtual void  close();
                virtual ~JByteArrayOutputStream();
        };
    }
}

#endif // JBYTEARRAYOUTPUTSTREAM_H
