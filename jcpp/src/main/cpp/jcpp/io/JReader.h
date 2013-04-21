#ifndef JREADER_H
#define JREADER_H

#include "JObject.h"
#include "JReadable.h"
#include "JCloseable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JReader : public JObject  , public JReadable  , public JCloseable  {
            protected:
                JObject* lock;
                jchar* skipBuffer;
                jint length;
                JReader(JClass* _class);
                JReader(JClass* _class,JObject* lock);

            public:
                static JClass* getClazz();
                virtual jint read();
                virtual jint read(jchar b[], jint off, jint len)=0;
                virtual jlong skip(jlong n);
                virtual jbool ready();
                virtual jbool markSupported();
                virtual void  mark(jint);
                virtual void  reset();
                virtual void  close()=0;
                virtual ~JReader();
        };
    }
}

#endif // JREADER_H
