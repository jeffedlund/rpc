#ifndef JFILTEROUTPUTSTREAM_H
#define JFILTEROUTPUTSTREAM_H

#include <string>
#include "JObject.h"
#include "JClass.h"
#include "Object.h"
#include "JCPP.h"
#include "JOutputStream.h"
using namespace jcpp::lang;

//TODO extends QObjectAware
namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JFilterOutputStream : public JOutputStream{
        protected:
            JOutputStream* out;
            JFilterOutputStream(JOutputStream* out,JClass* _class);

        public:
            static JClass* getClazz();
            virtual void write(jint b);
            virtual void write(jbyte b[], jint off, jint len);
            virtual void flush();
            virtual void close();
            virtual ~JFilterOutputStream();
        };
    }
}

#endif // JFILTEROUTPUTSTREAM_H
