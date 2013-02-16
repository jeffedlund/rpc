#ifndef JINETADDRESS_H
#define JINETADDRESS_H

#include "JLANG.h"
#include "JIO.h"

//TODO implement inet4, inet6 + io
namespace jcpp{
    namespace net{
        class JInetAddress : public JObject{
        protected:
            JString* hostName;
            JPrimitiveInt* address;
            JPrimitiveInt* family;

        public:
            JInetAddress();
            JInetAddress(JString* host, JPrimitiveInt* address,JPrimitiveInt* family);
            static JClass* getClazz();
            bool operator==(JObject &other);
            JString* getHostName();
            void setHostName(JString* h);
            JPrimitiveInt* getAddress();
            void setAddress(JPrimitiveInt* a);
            JPrimitiveInt* getFamily();
            void setFamily(JPrimitiveInt* f);
            string toString();
            ~JInetAddress();
        };
    }
}
#endif // JINETADDRESS_H
