#ifndef JENDPOINT_H
#define JENDPOINT_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JEndPoint : public JObject, public JSerializable{
                        protected:
                            JAddress* address;
                            JString* site;

                        public:
                            JEndPoint();
                            JEndPoint(JAddress* a, JString* s);
                            bool operator==(JObject &other);

                            static JClass* getClazz();

                            void setAddress(JAddress* a);

                            JAddress* getAddress();

                            void setSite(JString* site);

                            JString* getSite();

                            string toString();

                            ~JEndPoint();
                    };
                }
            }
        }
    }
}

#endif // JENDPOINT_H
