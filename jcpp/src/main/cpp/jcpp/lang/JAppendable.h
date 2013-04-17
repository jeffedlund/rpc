#ifndef JAPPENDABLE_H
#define JAPPENDABLE_H

#include "JCharSequence.h"
#include "JInterface.h"
#include "JAppendable.h"

namespace jcpp{
    namespace lang{
        class JAppendable : public JInterface  {
        public:
            static JClass* getClazz();
            virtual JAppendable* append(jchar c)=0;
            virtual JAppendable* append(JCharSequence* csq)=0;
            virtual JAppendable* append(JCharSequence* csq,jint start,jint end)=0;
            virtual ~JAppendable();
        };
    }
}

#endif // JAPPENDABLE_H
