#include "JGCClient.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JGCClientClass : public JClass{
                      public:
                        JGCClientClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GCClient";
                            this->name="jcpp.rmi.server.impl.connection.GCClient";
                            this->simpleName="GCClient";
                            addInterface(JIGCClient::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JGCClient::getClazz(){
                        if (clazz==NULL){
                            clazz=new JGCClientClass();
                        }
                        return clazz;
                    }

                    JGCClient::JGCClient(JServer* localServer, JIGCClientListener* gcClientListener){
                        this->localServer=localServer;
                        this->endPointInfos=new map<JEndPoint*,JGCClientEndPointInfo*>();
                        this->gcClientListener=gcClientListener;
                    }

                    JPrimitiveArray* JGCClient::getEndPoints(){
                        return NULL;//TODO return endPointInfos.keySet().toArray(new EndPoint[0]);
                    }

                    void JGCClient::add(map<JObjectPointer*, JObject*>* objectPointers){
                        /*for (Entry<ObjectPointer, Object> entry : objectPointers.entrySet()) {
                            EndPoint remoteEndPoint = entry.getKey().getEndPoint();
                            EndPointInfo endPointInfo = endPointInfos.get(remoteEndPoint);
                            if (endPointInfo == null) {
                                endPointInfo = new EndPointInfo(remoteEndPoint);
                                endPointInfos.put(remoteEndPoint, endPointInfo);
                            }
                            endPointInfo.export(entry.getKey().getId(), entry.getValue());
                        }*/
                    }

                    void JGCClient::unexport(){
                        /*
                            EndPointInfo[] epis = null;
                            synchronized (this) {
                                epis = endPointInfos.values().toArray(new EndPointInfo[0]);
                            }
                            for (EndPointInfo epi : epis) {
                                epi.unexport();
                            }

                            */
                    }

                    JGCClient::~JGCClient(){
                        delete endPointInfos;
                    }

                }
            }
        }
    }
}


