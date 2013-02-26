#ifndef JINVOCATIONHANDLER_H
#define JINVOCATIONHANDLER_H

#include "JObject.h"
#include "JMethod.h"
#include "JInterface.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JInvocationHandler : public JInterface{//TODO implement getClazz pr cpp
            public:
                virtual JObject *invoke(JObject* proxy, JMethod* method, vector<JObject*>* args) = 0;
                virtual ~JInvocationHandler();
            };
        }
    }
}
#endif // JINVOCATIONHANDLER_H
