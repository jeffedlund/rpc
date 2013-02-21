#include "JAddress.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    static JObject* staticGetHostName(JObject* object){
                        JAddress* s=(JAddress*)object;
                        return s->getPHostName();
                    }

                    static void staticSetHostName(JObject* object,JObject* value){
                        JAddress* s=(JAddress*)object;
                        s->setPHostName((JString*)value);
                    }

                    static JObject* staticGetPort(JObject* object){
                        JAddress* s=(JAddress*)object;
                        return s->getPPort();
                    }

                    static void staticSetPort(JObject* object,JObject* value){
                        JAddress* s=(JAddress*)object;
                        s->setPPort((JPrimitiveInt*)value);
                    }

                    class JAddressClass : public JClass{
                      public:
                        JAddressClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.Address";
                            this->name="jcpp.rmi.server.impl.gateway.Address";
                            this->simpleName="Address";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("hostName",JString::getClazz(),staticGetHostName,staticSetHostName));
                            addField(new JField("port",JPrimitiveInt::getClazz(),staticGetPort,staticSetPort));
                            //TODO define serialVersionIUD
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JAddress();
                        }
                    };

                    static JClass* clazz;

                    JClass* JAddress::getClazz(){
                        if (clazz==NULL){
                            clazz=new JAddressClass();
                        }
                        return clazz;
                    }


                    JAddress::JAddress():JObject(getClazz()){
                        this->hostName=new JString();
                        this->port=new JPrimitiveInt();
                    }

                    JAddress::JAddress(JAddress* adr):JObject(getClazz()){
                        this->hostName=new JString(adr->hostName);
                        this->port=new JPrimitiveInt(adr->port);
                    }

                    bool JAddress::operator==(JObject &other){
                        if (other.getClass()!=getClazz()){
                            return false;
                        }
                        JAddress* s=dynamic_cast<JAddress*>(&other);
                        return (*s->hostName)==(*hostName) && (*s->port)==(*port);
                    }

                    void JAddress::setHostName(string host){
                        hostName->setString(host);
                    }

                    string JAddress::getHostName(){
                        return hostName->getString();
                    }

                    void JAddress::setPHostName(JString* host){
                        delete this->hostName;
                        this->hostName=host;
                    }

                    JString* JAddress::getPHostName(){
                        return hostName;
                    }

                    void JAddress::setPort(jint port){
                        this->port->set(port);
                    }

                    jint JAddress::getPort(){
                        return port->get();
                    }

                    void JAddress::setPPort(JPrimitiveInt* port){
                        delete this->port;
                        this->port=port;
                    }

                    JPrimitiveInt* JAddress::getPPort(){
                        return port;
                    }

                    JAddress* JAddress::clone(){
                        JAddress* a=new JAddress();
                        a->hostName=hostName->clone();
                        a->port=port->clone();
                        return a;
                    }

                    string JAddress::toString(){
                        return "Address["+hostName->toString()+":"+port->toString()+"]";
                    }

                    JAddress::~JAddress(){
                        delete hostName;
                        delete port;
                    }
                }
            }
        }
    }
}
