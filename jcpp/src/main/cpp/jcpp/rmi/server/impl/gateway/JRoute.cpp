#include "JRoute.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace gateway{
                    static JObject* staticGetAddressList(JObject* object){
                        JRoute* s=(JRoute*)object;
                        return s->getAddressList();
                    }

                    static void staticSetAddressList(JObject* object,JObject* value){
                        JRoute* s=(JRoute*)object;
                        s->setAddressList((JArrayList*)value);
                    }

                    static JObject* staticGetIsHttp(JObject* object){
                        JRoute* s=(JRoute*)object;
                        return s->getPIsHttp();
                    }

                    static void staticSetIsHttp(JObject* object,JObject* value){
                        JRoute* s=(JRoute*)object;
                        s->setPIsHttp((JPrimitiveBoolean*)value);
                    }

                    class JRouteClass : public JClass{
                      public:
                        JRouteClass(){
                            this->canonicalName="jcpp.rmi.server.impl.gateway.Route";
                            this->name="jcpp.rmi.server.impl.gateway.Route";
                            this->simpleName="Route";
                            this->serialVersionUID=2731749507109405573ULL;
                            addInterface(JSerializable::getClazz());
                            addInterface(JCloneable::getClazz());
                            addField(new JField("addressList",JArrayList::getClazz(),this,staticGetAddressList,staticSetAddressList));
                            addField(new JField("isHttp",JPrimitiveBoolean::getClazz(),this,staticGetIsHttp,staticSetIsHttp));
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JRoute();
                        }
                    };

                    static JClass* clazz;

                    JClass* JRoute::getClazz(){
                        if (clazz==NULL){
                            clazz=new JRouteClass();
                        }
                        return clazz;
                    }


                    JRoute::JRoute():JObject(getClazz()){
                        this->addressList=new JArrayList(0);
                        this->bIsHttp=new JPrimitiveBoolean();
                    }

                    bool JRoute::equals(JObject* other){
                        if (other->getClass()!=getClazz()){
                            return false;
                        }
                        JRoute* s=dynamic_cast<JRoute*>(other);
                        return (*s->addressList)==(*addressList) && (*s->bIsHttp)==(*bIsHttp);
                    }

                    void JRoute::setIsHttp(bool h){
                        bIsHttp->set(h);
                    }

                    bool JRoute::isHttp(){
                        return bIsHttp->get();
                    }

                    JPrimitiveBoolean* JRoute::getPIsHttp(){
                        return bIsHttp;
                    }

                    void JRoute::setPIsHttp(JPrimitiveBoolean* h){
                        delete this->bIsHttp;
                        this->bIsHttp=h;
                    }

                    void JRoute::addAddress(JAddress* a){
                        addressList->add(a);
                    }

                    void JRoute::removeAddress(JAddress* a){
                        addressList->remove(a);
                    }

                    JArrayList* JRoute::getAddressList(){
                        return addressList;
                    }

                    void JRoute::setAddressList(JArrayList* al){
                        delete this->addressList;
                        this->addressList=al;
                    }

                    JAddress* JRoute::peakAddress(){
                        if (addressList->size() > 0) {
                            return (JAddress*)addressList->get(0);
                        }
                        return NULL;
                    }

                    JAddress* JRoute::popAddress(){
                        if (addressList->size() > 0) {
                            JAddress* a=(JAddress*)addressList->remove(0);
                            return a;
                        }
                        return NULL;
                    }

                    void JRoute::pushAddress(JAddress* a){
                        addressList->add(0,a);
                    }

                    int JRoute::addressSize(){
                        return addressList->size();
                    }

                    void JRoute::clearAddress(){
                        addressList->clear();
                    }

                    JRoute* JRoute::clone(){
                        JRoute* route=new JRoute();
                        route->addressList=addressList->clone();
                        return route;
                    }

                    JString JRoute::toString(){
                        return "AddressList["+addressList->toString()+"][IsHttp:"+bIsHttp->toString()+"]";
                    }

                    JRoute::~JRoute(){
                        delete addressList;
                        delete bIsHttp;
                    }
                }
            }
        }
    }
}

