#include "JInetAddress.h"

namespace jcpp{
    namespace net{
        JInetAddress::JInetAddress(JString* host, JPrimitiveInt* port){
        }

        JString* JInetAddress::getHostName(){
            return hostName;
        }

        void JInetAddress::setHostName(JString* h){
            delete hostName;
            this->hostName=h;
        }

        JPrimitiveInt* JInetAddress::getAddress(){
            return this->address;
        }

        void JInetAddress::setAddress(JPrimitiveInt* a){
            this->address=a;
        }

        JPrimitiveInt* JInetAddress::getFamily(){
            return family;
        }

        void JInetAddress::setFamily(JPrimitiveInt* f){
            this->family=f;
        }
    }
}

