#ifndef JCHARSEQUENCE_H
#define JCHARSEQUENCE_H

#include "JCharSequence.h"
#include "JInterface.h"
#include "JString.h"

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JCharSequence : public JInterface  {
            public:
                static JClass* getClazz();
                virtual jchar charAt(jint i)=0;
                virtual jint length()=0;
                virtual JCharSequence * subSequence(jint start, jint end)=0;
                virtual string toString()=0;
                virtual ~JCharSequence();
        };
    }
}

#endif // JCHARSEQUENCE_H
