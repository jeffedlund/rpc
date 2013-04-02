#ifndef JMEMBER_H
#define JMEMBER_H

#include "JObject.h"
#include "JCPP.h"
#include "JInterface.h"
using namespace std;

//TODO implement reflect.JArray
namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JMember: public JInterface{
            public:
                static JClass* getClazz();
                static jint PUBLIC;
                static jint DECLARED;
                virtual JClass* getDeclaringClass()=0;
                virtual string getName()=0;
                virtual jint getModifiers()=0;
                virtual jbool isSynthetic()=0;
                virtual ~JMember();
            };
        }
    }
}
#endif // JMEMBER_H
