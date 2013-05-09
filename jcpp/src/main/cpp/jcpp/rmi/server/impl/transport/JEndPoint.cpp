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
                            this->canonicalName="jcpp.rmi.server.impl.transport.EndPoint";
                            this->name="jcpp.rmi.server.impl.transport.EndPoint";
                            this->simpleName="EndPoint";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("address",JAddress::getClazz(),this,staticGetAddress,staticSetAddress));
                            addField(new JField("site",JString::getClazz(),this,staticGetSite,staticSetSite));
                            serialVersionUID=1L;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JEndPoint();
                        }
                    };

                    static JClass* clazz;

                    JClass* JEndPoint::getClazz(){
                        if (clazz==NULL){
                            clazz=new JEndPointClass();
                        }
                        return clazz;
                    }

                    JEndPoint::JEndPoint():JObject(getClazz()){
                        this->site=new JString("");
                        this->address=new JAddress();
                    }

                    JEndPoint::JEndPoint(JDataInputStream* in):JObject(getClazz()){
                        JString host=in->readUTF();
                        int port=in->readInt();
                        this->site=new JString(in->readUTF());
                        this->address=new JAddress();
                        address->setHostName(host);
                        address->setPort(port);
                    }

                    JEndPoint::JEndPoint(JAddress* a, JString* s):JObject(getClazz()){
                        this->address=a;
                        this->site=s;
                    }

                    bool JEndPoint::equals(JObject* other){
                        if (other->getClass()!=getClazz()){
                            return false;
                        }
                        JEndPoint* s=dynamic_cast<JEndPoint*>(other);
                        return (*s->address)==(*address) && (*s->site)==(*site);
                    }

                    bool JEndPoint::operator<(JEndPoint &other){
                        if (getSite()->getString()<other.getSite()->getString()){
                            if (getAddress()->getHostName()<other.getAddress()->getHostName()){
                                if (getAddress()->getPort()<other.getAddress()->getPort()){
                                    return true;
                                }
                            }
                        }
                        return false;
                    }

                    void JEndPoint::write(JDataOutputStream* out){
                        out->writeUTF(address->getHostName());
                        out->writeInt(address->getPort());
                        out->writeUTF(site->getString());
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

                    jint JEndPoint::hashCode(){
                        return address->getPHostName()->hashCode()+address->getPPort()->get()+site->hashCode();
                    }

                    JString JEndPoint::toString(){
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
