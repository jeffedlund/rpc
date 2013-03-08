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
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

//TODO add compression later
namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JGatewayInputStream : public JObjectInputStream{
                    protected:
                        JRoute* route;

                    public:
                        JGatewayInputStream(JInputStream* in);
                        static JClass* getClazz();
                        JRoute* getRoute();
                        virtual ~JGatewayInputStream();
                    };
                }
            }
        }
    }
}

#endif // JGATEWAYINPUTSTREAM_H
