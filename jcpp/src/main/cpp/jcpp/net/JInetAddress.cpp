#include "JInetAddress.h"
#include <QHostInfo>

namespace jcpp{
    namespace net{
        class JInetAddressClass : public JClass{
        protected:
            static JObject* staticGetHostName(JObject* object){
                JInetAddress* s=(JInetAddress*)object;
                return s->getHostName();
            }

            static void staticSetHostName(JObject* object,JObject* value){
                JInetAddress* s=(JInetAddress*)object;
                s->setHostName((JString*)value);
            }

            static JObject* staticGetAddress(JObject* object){
                JInetAddress* s=(JInetAddress*)object;
                return s->getPAddress();
            }

            static void staticSetAddress(JObject* object,JObject* value){
                JInetAddress* s=(JInetAddress*)object;
                s->setPAddress((JPrimitiveInt*)value);
            }

            static JObject* staticGetFamily(JObject* object){
                JInetAddress* s=(JInetAddress*)object;
                return s->getPFamily();
            }

            static void staticSetFamily(JObject* object,JObject* value){
                JInetAddress* s=(JInetAddress*)object;
                s->setPFamily((JPrimitiveInt*)value);
            }
        public:
          JInetAddressClass(){
              this->canonicalName="java.net.InetAddress";
              this->name="java.lang.InetAddress";
              this->simpleName="InetAddress";
              this->serialVersionUID=3286316764910316507ULL;
              addInterface(JSerializable::getClazz());
              addField(new JField("hostName",JString::getClazz(),this,staticGetHostName,staticSetHostName));
              addField(new JField("address",JPrimitiveInt::getClazz(),this,staticGetAddress,staticSetAddress));
              addField(new JField("family",JPrimitiveInt::getClazz(),this,staticGetFamily,staticSetFamily));
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              return new JInetAddress();
          }
        };

        static JClass* clazz;

        JClass* JInetAddress::getClazz(){
            if (clazz==NULL){
                clazz=new JInetAddressClass();
            }
            return clazz;
        }

        jbool JInetAddress::equals(JObject* other){
            if (!(other->getClazz()==getClass())){
                return false;
            }
            JInetAddress* ia=dynamic_cast<JInetAddress*>(other);
            return (*hostName==*ia->hostName) && (*address==*ia->address) && (*family==*ia->family);
        }

        JInetAddress::JInetAddress():JObject(getClazz()){
            this->hostName=NULL;
            this->address=NULL;
            this->family=NULL;
        }

        JInetAddress::JInetAddress(JClass* _class):JObject(_class){
            this->hostName=NULL;
            this->address=NULL;
            this->family=NULL;
        }

        JInetAddress::JInetAddress(JString host):JObject(getClazz()){
            this->hostName=new JString(host);
            this->address=NULL;
            this->family=NULL;
        }

        JInetAddress* JInetAddress::getByName(JString host){
            QHostInfo h=QHostInfo::fromName(QString::fromStdString(host.getString()));
            return new JInetAddress(new JString(h.hostName().toStdString()));
        }

        static JInetAddress* localHost=NULL;

        JInetAddress* JInetAddress::getLocalHost(){
            if (localHost==NULL){
                localHost=new JInetAddress(new JString(QHostInfo::localHostName().toStdString()));
            }
            return localHost;
        }

        JString* JInetAddress::getHostName(){
            return hostName;
        }

        void JInetAddress::setHostName(JString* h){
            delete hostName;
            this->hostName=h;
        }

        JPrimitiveInt* JInetAddress::getPAddress(){
            return this->address;
        }

        void JInetAddress::setPAddress(JPrimitiveInt* a){
            delete this->address;
            this->address=a;
        }

        JPrimitiveInt* JInetAddress::getPFamily(){
            return family;
        }

        void JInetAddress::setPFamily(JPrimitiveInt* f){
            delete this->family;
            this->family=f;
        }

        jint JInetAddress::getAddress(){
            return this->address->get();
        }

        void JInetAddress::setAddress(jint a){
            this->address->set(a);
        }

        jint JInetAddress::getFamily(){
            return family->get();
        }

        void JInetAddress::setFamily(jint f){
            this->family->set(f);
        }

        //TODO all these ones
        jbool JInetAddress::isAnyLocalAddress(){
            return false;
        }

        jbool JInetAddress::isLinkLocalAddress(){
            return false;
        }

        jbool JInetAddress::isLoopbackAddress(){
            return false;
        }

        jbool JInetAddress::isMCGlobal(){
            return false;
        }

        jbool JInetAddress::isMCLinkLocal(){
            return false;
        }

        jbool JInetAddress::isMCNodeLocal(){
            return false;
        }

        jbool JInetAddress::isMCOrgLocal(){
            return false;
        }

        jbool JInetAddress::isMCSiteLocal(){
            return false;
        }

        jbool JInetAddress::isMulticastAddress(){
            return false;
        }

        jbool JInetAddress::isReachable(int){
            return false;
        }

        jbool JInetAddress::isSiteLocalAddress(){
            return false;
        }

        JString JInetAddress::toString(){
            return "InetAddress[HostName:"+hostName->toString()+" , Address:"+address->toString()+" , Family:"+family->toString()+"]";
        }

        JInetAddress::~JInetAddress() {
            delete hostName;
            delete address;
            delete family;
        }
    }
}
