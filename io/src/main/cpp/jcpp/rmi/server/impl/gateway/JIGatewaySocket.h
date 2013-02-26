#ifndef JIGATEWAYSOCKET_H
#define JIGATEWAYSOCKET_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
#include "JArrayList.h"
#include "JString.h"
#include "Object.h"
#include "JAddress.h"
#include "JRoute.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JIGatewaySocket : public JInterface{
                        public:
                        static JClass* getClazz();
                        virtual JRoute* getRoute()=0;
                        virtual bool isReusable()=0;
                        virtual ~JIGatewaySocket();
                    };
                }
            }
        }
    }
}

#endif // JIGATEWAYSOCKET_H
