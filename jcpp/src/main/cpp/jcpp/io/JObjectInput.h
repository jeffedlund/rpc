#ifndef JOBJECTINPUT_H
#define JOBJECTINPUT_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
#include "JClass.h"
#include "JDataInput.h"
#include "JAutoCloseable.h"
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JObjectInput : public JDataInput, public JAutoCloseable{
        public:
            static JClass* getClazz();
            virtual JObject* readObject()=0;
            virtual jint read()=0;
            virtual jint read(jbyte b[], jint off, jint len)=0;
            virtual jlong skip(jlong n)=0;
            virtual jint available()=0;
            virtual void close()=0;
            virtual ~JObjectInput();
        };
    }
}

#endif // JOBJECTINPUT_H
