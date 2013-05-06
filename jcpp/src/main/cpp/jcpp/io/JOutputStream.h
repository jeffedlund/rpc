#ifndef JOUTPUTSTREAM_H
#define JOUTPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JOutputStream : public JObject{
        protected:
            JOutputStream(JClass* _class);

        public:
            JOutputStream();
            static JClass* getClazz();
            virtual void write(jint b)=0;
            virtual void write(jbyte b[], jint off, jint len);
            virtual void flush()=0;
            virtual void close()=0;
            virtual ~JOutputStream();
        };
    }
}

#endif // JOUTPUTSTREAM_H
