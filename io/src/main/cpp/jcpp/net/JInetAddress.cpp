#include "JInetAddress.h"
#include <QHostInfo>

namespace jcpp{
    namespace net{
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
            return s->getAddress();
        }

        static void staticSetAddress(JObject* object,JObject* value){
            JInetAddress* s=(JInetAddress*)object;
            s->setAddress((JPrimitiveInt*)value);
        }

        static JObject* staticGetFamily(JObject* object){
            JInetAddress* s=(JInetAddress*)object;
            return s->getFamily();
        }

        static void staticSetFamily(JObject* object,JObject* value){
            JInetAddress* s=(JInetAddress*)object;
            s->setFamily((JPrimitiveInt*)value);
        }

        class JInetAddressClass : public JClass{
        public:
          JInetAddressClass(){
              this->canonicalName="java.net.InetAddress";
              this->name="java.lang.InetAddress";
              this->simpleName="InetAddress";
              this->serialVersionUID=3286316764910316507ULL;
              addInterface(JSerializable::getClazz());
              addField(new JField("hostName",JString::getClazz(),staticGetHostName,staticSetHostName));
              addField(new JField("address",JPrimitiveInt::getClazz(),staticGetAddress,staticSetAddress));
              addField(new JField("family",JPrimitiveInt::getClazz(),staticGetFamily,staticSetFamily));
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

        bool JInetAddress::operator==(JObject &other){
            if (!(other.getClazz()==getClass())){
                return false;
            }
            JInetAddress* ia=dynamic_cast<JInetAddress*>(&other);
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

        JInetAddress::JInetAddress(JString* host):JObject(getClazz()){
            this->hostName=host;
            this->address=NULL;
            this->family=NULL;
        }

        JInetAddress* JInetAddress::getByName(string host){
            QHostInfo h=QHostInfo::fromName(QString::fromStdString(host));
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

        JPrimitiveInt* JInetAddress::getAddress(){
            return this->address;
        }

        void JInetAddress::setAddress(JPrimitiveInt* a){
            delete this->address;
            this->address=a;
        }

        JPrimitiveInt* JInetAddress::getFamily(){
            return family;
        }

        void JInetAddress::setFamily(JPrimitiveInt* f){
            delete this->family;
            this->family=f;
        }

        //TODO all these ones
        bool JInetAddress::isAnyLocalAddress(){
            return false;
        }

        bool JInetAddress::isLinkLocalAddress(){
            return false;
        }

        bool JInetAddress::isLoopbackAddress(){
            return false;
        }

        bool JInetAddress::isMCGlobal(){
            return false;
        }

        bool JInetAddress::isMCLinkLocal(){
            return false;
        }

        bool JInetAddress::isMCNodeLocal(){
            return false;
        }

        bool JInetAddress::isMCOrgLocal(){
            return false;
        }

        bool JInetAddress::isMCSiteLocal(){
            return false;
        }

        bool JInetAddress::isMulticastAddress(){
            return false;
        }

        bool JInetAddress::isReachable(int){
            return false;
        }

        bool JInetAddress::isSiteLocalAddress(){
            return false;
        }

        string JInetAddress::toString(){
            return "InetAddress[HostName:"+hostName->toString()+" , Address:"+address->toString()+" , Family:"+family->toString()+"]";
        }

        JInetAddress::~JInetAddress() {
            delete hostName;
            delete address;
            delete family;
        }
    }
}
