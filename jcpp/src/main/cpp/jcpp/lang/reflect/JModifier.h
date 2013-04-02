#ifndef JMODIFIER_H
#define JMODIFIER_H


#include "JObject.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JModifier: public JObject{
            public:
                static JClass* getClazz();
                static jint PUBLIC;
                static jint PRIVATE;
                static jint PROTECTED;
                static jint STATIC;
                static jint FINAL;
                static jint SYNCHRONIZED;
                static jint VOLATILE;
                static jint TRANSIENT;
                static jint NATIVE;
                static jint INTERFACE;
                static jint ABSTRACT;
                static jint STRICT;
                static jbool isSynthetic(jint mod);
                static jbool isPublic(jint mod);
                virtual ~JModifier();
            };
        }
    }
}
#endif // JMODIFIER_H
