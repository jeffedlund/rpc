#ifndef JINVOCATIONHANDLER_H
#define JINVOCATIONHANDLER_H

#include "JObject.h"
#include "JMethod.h"
#include "JInterface.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JInvocationHandler : public JInterface{
            public:
                static JClass* getClazz();
                virtual JObject *invoke(JObject* proxy, JMethod* method, vector<JObject*>* args) = 0;
                virtual ~JInvocationHandler();
            };
        }
    }
}
#endif // JINVOCATIONHANDLER_H
