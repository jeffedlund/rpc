#ifndef JTRANSPORTROUTER_H
#define JTRANSPORTROUTER_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JITransportRouter.h"
#include "JAddress.h"
#include <map>
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::rmi::server::impl::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTransportRouter : public JObject, public JITransportRouter{
                        protected:
                            map<string, map<string, JRoute*>*>* routes;

                        public:
                            JTransportRouter();
                            static JClass* getClazz();

                            void addRoute(JString* localSite,JString* remoteSite, JRoute* route);

                            virtual JRoute* findRoute(JString* localSite, JEndPoint* remoteEndpoint);

                            ~JTransportRouter();
                    };
                }
            }
        }
    }
}

#endif // JTRANSPORTROUTER_H
