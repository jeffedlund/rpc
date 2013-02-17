#include "JEndPoint.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    static JObject* staticGetAddress(JObject* object){
                        JEndPoint* s=(JEndPoint*)object;
                        return s->getAddress();
                    }

                    static void staticSetAddress(JObject* object,JObject* value){
                        JEndPoint* s=(JEndPoint*)object;
                        s->setAddress((JAddress*)value);
                    }

                    static JObject* staticGetSite(JObject* object){
                        JEndPoint* s=(JEndPoint*)object;
                        return s->getSite();
                    }

                    static void staticSetSite(JObject* object,JObject* value){
                        JEndPoint* s=(JEndPoint*)object;
                        s->setSite((JString*)value);
                    }

                    class JEndPointClass : public JClass{
                      public:
                        JEndPointClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.JEndPoint";
                            this->name="jcpp.rmi.server.impl.transport.JEndPoint";
                            this->simpleName="JEndPoint";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("address",JAddress::getClazz(),staticGetAddress,staticSetAddress));
                            addField(new JField("site",JString::getClazz(),staticGetSite,staticSetSite));
                            //TODO define serialVersionIUD
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JEndPoint();
                        }
                    };

                    static JClass* clazz;

                    JClass* JEndPoint::getClazz(){
                        if (clazz==NULL){
                            clazz=new JEndPointClass();
                        }
                        return clazz;
                    }

                    JEndPoint::JEndPoint(){
                    }

                    JEndPoint::JEndPoint(JAddress* a, JString* s){
                        this->address=a;
                        this->site=s;
                    }

                    bool JEndPoint::operator==(JObject &other){
                        if (other.getClass()!=getClazz()){
                            return false;
                        }
                        JEndPoint* s=dynamic_cast<JEndPoint*>(&other);
                        return (*s->address)==(*address) && (*s->site)==(*site);
                    }

                    void JEndPoint::setAddress(JAddress* a){
                        delete this->address;
                        this->address=a;
                    }

                    JAddress* JEndPoint::getAddress(){
                        return address;
                    }

                    void JEndPoint::setSite(JString* site){
                        delete this->site;
                        this->site=site;
                    }

                    JString* JEndPoint::getSite(){
                        return site;
                    }

                    string JEndPoint::toString(){
                        return "EndPoint["+address->toString()+":"+site->toString()+"]";
                    }

                    JEndPoint::~JEndPoint(){
                        delete address;
                        delete site;
                    }
                }
            }
        }
    }
}
