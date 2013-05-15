#include "JAddress.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    class JAddressClass : public JClass{
                      protected:
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

                      public:
                        JAddressClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.Address";
                            this->name="jcpp.rmi.server.impl.gateway.Address";
                            this->simpleName="Address";
                            addInterface(JSerializable::getClazz());
                            addInterface(JCloneable::getClazz());
                            addField(new JField("hostName",JString::getClazz(),this,staticGetHostName,staticSetHostName));
                            addField(new JField("port",JPrimitiveInt::getClazz(),this,staticGetPort,staticSetPort));
                            serialVersionUID=1;
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

                    JAddress::JAddress(JString host, jint port):JObject(getClazz()){
                        this->hostName=new JString(host);
                        this->port=new JPrimitiveInt(port);
                    }

                    JAddress::JAddress(JAddress* adr):JObject(getClazz()){
                        this->hostName=new JString(adr->hostName);
                        this->port=new JPrimitiveInt(adr->port);
                    }

                    bool JAddress::equals(JObject* other){
                        if (other->getClass()!=getClazz()){
                            return false;
                        }
                        JAddress* s=dynamic_cast<JAddress*>(other);
                        return (*s->hostName)==(*hostName) && (*s->port)==(*port);
                    }

                    void JAddress::setHostName(JString host){
                        delete this->hostName;
                        hostName=new JString(host);
                    }

                    JString* JAddress::getHostName(){
                        return hostName;
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

                    void JAddress::write(JDataOutputStream* out){
                        out->writeUTF(getPHostName());
                        out->writeInt(getPPort());
                    }

                    jint JAddress::hashCode(){
                        return (hostName!=NULL?hostName->hashCode()*37+port->get():port->get());
                    }

                    JAddress* JAddress::clone(){
                        JAddress* a=new JAddress(this);
                        return a;
                    }

                    JString JAddress::toString(){
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
