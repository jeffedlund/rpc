#include "JTransportRouter.h"
#include "JSerializable.h"
#include "Collections.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JTransportRouterClass : public JClass{
                      public:
                        JTransportRouterClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.TransportRouter";
                            this->name="jcpp.rmi.server.impl.transport.TransportRouter";
                            this->simpleName="TransportRouter";
                            addInterface(JTransportRouter::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JTransportRouter();
                        }
                    };

                    static JClass* clazz;

                    JClass* JTransportRouter::getClazz(){
                        if (clazz==NULL){
                            clazz=new JTransportRouterClass();
                        }
                        return clazz;
                    }

                    JTransportRouter::JTransportRouter():JObject(getClazz()){
                        this->routes=new map<string, map<string, JRoute*>*>();
                    }

                    void JTransportRouter::addRoute(JString* localSite,JString* remoteSite, JRoute* route){
                        lock();
                        map<string,JRoute*>* internalMap=getFromMap(routes,localSite->getString());
                        if (internalMap==NULL){
                            internalMap=new map<string,JRoute*>();
                            routes->insert(pair<string,map<string,JRoute*>*>(localSite->getString(),internalMap));
                        }
                        internalMap->insert(pair<string,JRoute*>(remoteSite->getString(),route));
                        unlock();
                    }

                    JRoute* JTransportRouter::findRoute(JString* localSite, JEndPoint* remoteEndpoint){
                        JRoute* route=NULL;
                        lock();
                        if (localSite!=NULL && remoteEndpoint!=NULL){
                            if (localSite->getString()==remoteEndpoint->getSite()->getString()){
                                route=new JRoute();
                                route->addAddress(new JAddress(remoteEndpoint->getAddress()));
                            }else{
                                map<string,JRoute*>* internalMap=getFromMap(routes,localSite->getString());
                                if (internalMap!=NULL){
                                    route=getFromMap(internalMap,remoteEndpoint->getSite()->getString());
                                    if (route!=NULL){
                                        route=route->clone();
                                        route->addAddress(new JAddress(remoteEndpoint->getAddress()));
                                    }
                                }
                            }
                        }
                        unlock();
                        return route;
                    }

                    JTransportRouter::~JTransportRouter(){
                        map<string, map<string, JRoute*>*>::iterator it=routes->begin();
                        for (;it!=routes->end();it++){
                            deleteMapOfValuePointer((*it).second);
                        }
                        deleteMapOfValuePointer(routes);
                    }
                }
            }
        }
    }
}
