#ifndef JINETADDRESS_H
#define JINETADDRESS_H

#include "JLANG.h"
#include "JIO.h"
#include "JCPP.h"

//TODO implement other
namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JInetAddress : public JObject, public JSerializable{
        protected:
            JString* hostName;
            JPrimitiveInt* address;
            JPrimitiveInt* family;
            JInetAddress(JClass* _class);

        public:
            static const int IPv4 = 1;
            static const int IPv6 = 2;
            JInetAddress();
            JInetAddress(JString* host);
            static JInetAddress* getByName(JString host);
            static JInetAddress* getLocalHost();
            static JClass* getClazz();
            JString* getHostName();
            void setHostName(JString* h);
            JPrimitiveInt* getAddress();
            void setAddress(JPrimitiveInt* a);
            JPrimitiveInt* getFamily();
            void setFamily(JPrimitiveInt* f);
            bool isAnyLocalAddress();
            bool isLinkLocalAddress();
            bool isLoopbackAddress();
            bool isMCGlobal();
            bool isMCLinkLocal();
            bool isMCNodeLocal();
            bool isMCOrgLocal();
            bool isMCSiteLocal();
            bool isMulticastAddress();
            bool isReachable(int timeout);
            bool isSiteLocalAddress();
            virtual bool equals(JObject* other);//TODO hashcode
            virtual JString toString();
            virtual ~JInetAddress();
        };
    }
}
#endif // JINETADDRESS_H
