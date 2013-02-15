#ifndef JADDRESS_H
#define JADDRESS_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JAddress : public JObject{
                        protected:
                            JString* hostName;
                            JPrimitiveInt* port;

                        public:
                            JAddress();
                            bool operator==(JObject &other);

                            static JClass* getClazz();

                            void setHostName(string host);

                            string getHostName();

                            void setPHostName(JString* host);

                            JString* getPHostName();

                            void setPort(jint port);

                            jint getPort();

                            void setPPort(JPrimitiveInt* port);

                            JPrimitiveInt* getPPort();

                            string toString();

                            ~JAddress();
                    };
                }
            }
        }
    }
}

#endif // JADDRESS_H