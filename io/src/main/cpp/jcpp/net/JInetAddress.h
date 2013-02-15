#ifndef JINETADDRESS_H
#define JINETADDRESS_H

#include "JLANG.h"
#include "JIO.h"

namespace jcpp{
    namespace net{
        class JInetAddress : public JObject{
        protected:
            JString* hostName;
            JPrimitiveInt* address;
            JPrimitiveInt* family;


        public:
            JInetAddress(JString* host, JPrimitiveInt* port);

            //TODO getClazz+toString+operator==
            JString* getHostName();
            void setHostName(JString* h);
            JPrimitiveInt* getAddress();
            void setAddress(JPrimitiveInt* a);
            JPrimitiveInt* getFamily();
            void setFamily(JPrimitiveInt* f);

        };
    }
}
#endif // JINETADDRESS_H
