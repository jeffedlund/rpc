#ifndef JADDRESS_H
#define JADDRESS_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JCPP.h"
#include "JCloneable.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JCPP_LIBRARY_EXPORT JAddress : public JObject, public JSerializable, public JCloneable{
                        protected:
                            JString* hostName;
                            JPrimitiveInt* port;

                        public:
                            JAddress();
                            JAddress(JAddress* adr);
                            static JClass* getClazz();
                            void setHostName(JString host);
                            JString getHostName();
                            void setPHostName(JString* host);
                            JString* getPHostName();
                            void setPort(jint port);
                            jint getPort();
                            void setPPort(JPrimitiveInt* port);
                            JPrimitiveInt* getPPort();
                            virtual bool equals(JObject* other);
                            virtual jint hashCode();
                            virtual JAddress* clone();
                            virtual JString toString();
                            virtual ~JAddress();
                    };
                }
            }
        }
    }
}

#endif // JADDRESS_H
