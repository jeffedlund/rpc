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
#include "JDataOutputStream.h"
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
                            void setPHostName(JString* host);
                            JString* getPHostName();
                            void setPPort(JPrimitiveInt* port);
                            JPrimitiveInt* getPPort();
                            friend class JAddressClass;

                        public:
                            JAddress();
                            JAddress(const JString& host, jint port);
                            JAddress(JAddress* adr);
                            static JClass* getClazz();
                            void setHostName(const JString& host);
                            JString* getHostName();
                            void setPort(jint port);
                            jint getPort();
                            void write(JDataOutputStream* out);
                            virtual jbool equals(JObject* other);
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
