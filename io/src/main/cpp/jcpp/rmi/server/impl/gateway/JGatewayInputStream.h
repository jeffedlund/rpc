#ifndef JGATEWAYINPUTSTREAM_H
#define JGATEWAYINPUTSTREAM_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JRoute.h"
using namespace std;
using namespace jcpp::lang;

//TODO add compression later
namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JGatewayInputStream : public JObjectInputStream{
                    protected:
                        JRoute* route;

                    public:
                        JGatewayInputStream(JInputStream* in);

                        static JClass* getClazz();

                        JRoute* getRoute();

                        ~JGatewayInputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYINPUTSTREAM_H
