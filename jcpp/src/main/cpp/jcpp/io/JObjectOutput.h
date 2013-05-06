#ifndef JOBJECTOUTPUT_H
#define JOBJECTOUTPUT_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
#include "JClass.h"
#include "JDataOutput.h"
#include "JAutoCloseable.h"
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JObjectOutput : public JDataOutput, public JAutoCloseable{
        public:
            static JClass* getClazz();
            virtual void writeObject(JObject* object)=0;
            virtual void write(jint b)=0;
            virtual void write(jbyte b[], jint off, jint len)=0;
            virtual void flush()=0;
            virtual void close()=0;
            virtual ~JObjectOutput();
        };
    }
}

#endif // JOBJECTOUTPUT_H
