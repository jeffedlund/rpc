#ifndef JGATEWAYOUTPUTSTREAM_H
#define JGATEWAYOUTPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JObjectOutputStream.h"
#include "JRoute.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayOutputStream : public JObjectOutputStream{
                    protected:
                        JRoute* route;

                    public:
                        JGatewayOutputStream(JOutputStream* out,JRoute* route);
                        static JClass* getClazz();
                        JRoute* getRoute();
                        ~JGatewayOutputStream();
                    };
                }
            }
        }
    }
}


#endif // JGATEWAYOUTPUTSTREAM_H
