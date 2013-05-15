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
                            addInterface(JITransportRouter::getClazz());
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
                        this->routes=new map<JString, map<JString, JRoute*>*>();
                    }

                    void JTransportRouter::addRoute(JString localSite,JString remoteSite, JRoute* route){
                        lock();
                        map<JString,JRoute*>* internalMap=getFromMap(routes,localSite);
                        if (internalMap==NULL){
                            internalMap=new map<JString,JRoute*>();
                            routes->insert(pair<JString,map<JString,JRoute*>*>(localSite,internalMap));
                        }
                        internalMap->insert(pair<JString,JRoute*>(remoteSite,route));
                        unlock();
                    }

                    JRoute* JTransportRouter::findRoute(JString localSite, JEndPoint* remoteEndpoint){
                        JRoute* route=NULL;
                        lock();
                        if (remoteEndpoint!=NULL){
                            if (localSite==remoteEndpoint->getSite()){
                                route=new JRoute();
                                route->addAddress(new JAddress(remoteEndpoint->getAddress()));
                            }else{
                                map<JString,JRoute*>* internalMap=getFromMap(routes,localSite);
                                if (internalMap!=NULL){
                                    route=getFromMap(internalMap,remoteEndpoint->getSite());
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
                        map<JString, map<JString, JRoute*>*>::iterator it=routes->begin();
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
