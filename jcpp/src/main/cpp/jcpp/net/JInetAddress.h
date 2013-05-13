#ifndef JINETADDRESS_H
#define JINETADDRESS_H

#include "JCPP.h"
#include "JString.h"
#include "JPrimitiveInt.h"
#include "JObject.h"
#include "JSerializable.h"

//TODO implement other
namespace jcpp{
    namespace net{
        class JCPP_LIBRARY_EXPORT JInetAddress : public JObject, public JSerializable{
        protected:
            JString* hostName;
            JPrimitiveInt* address;
            JPrimitiveInt* family;
            JInetAddress(JClass* _class);
            virtual JPrimitiveInt* getPAddress();
            virtual void setPAddress(JPrimitiveInt* a);
            virtual JPrimitiveInt* getPFamily();
            virtual void setPFamily(JPrimitiveInt* f);
            friend class JInetAddressClass;

        public:
            static const int IPv4 = 1;
            static const int IPv6 = 2;
            JInetAddress();
            JInetAddress(JString host);
            static JInetAddress* getByName(JString host);
            static JInetAddress* getLocalHost();
            static JClass* getClazz();
            virtual JString* getHostName();
            virtual void setHostName(JString* h);
            virtual jint getAddress();
            virtual void setAddress(jint a);
            virtual jint getFamily();
            virtual void setFamily(jint f);
            virtual jbool isAnyLocalAddress();
            virtual jbool isLinkLocalAddress();
            virtual jbool isLoopbackAddress();
            virtual jbool isMCGlobal();
            virtual jbool isMCLinkLocal();
            virtual jbool isMCNodeLocal();
            virtual jbool isMCOrgLocal();
            virtual jbool isMCSiteLocal();
            virtual jbool isMulticastAddress();
            virtual jbool isReachable(jint timeout);
            virtual jbool isSiteLocalAddress();
            virtual jbool equals(JObject* other);//TODO hashcode
            virtual JString toString();
            virtual ~JInetAddress();
        };
    }
}
#endif // JINETADDRESS_H
