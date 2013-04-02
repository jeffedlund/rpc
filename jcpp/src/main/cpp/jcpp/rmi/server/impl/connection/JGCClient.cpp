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
                    JObject* invokeGetEndPoints(JObject* object,vector<JObject*>*){
                        JGCClient* gcClient=(JGCClient*)object;
                        return gcClient->getEndPoints();
                    }

                    class JGCClientClass : public JClass{
                      public:
                        JGCClientClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.GCClient";
                            this->name="jcpp.rmi.server.impl.connection.GCClient";
                            this->simpleName="GCClient";
                            addInterface(JIGCClient::getClazz());
                            vector<JClass*>* param=new vector<JClass*>();
                            addMethod(new JMethod("getEndPoints",this,JPrimitiveArray::getClazz(JEndPoint::getClazz()),param,invokeGetEndPoints));
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
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
                        this->endPointInfos=new map<JEndPoint*,JGCClientEndPointInfo*,JEndPoint::POINTER_COMPARATOR>();
                        this->gcClientListener=gcClientListener;
                    }

                    JPrimitiveArray* JGCClient::getEndPoints(){
                        JPrimitiveArray* ar;
                        lock();
                        ar=new JPrimitiveArray(JEndPoint::getClazz(),endPointInfos->size());
                        int i=0;
                        map<JEndPoint*,JGCClientEndPointInfo*,JEndPoint::POINTER_COMPARATOR>::iterator it=endPointInfos->begin();
                        for (;it!=endPointInfos->end();it++){
                            ar->set(i,(*it).first);
                            i++;
                        }
                        unlock();
                        return ar;
                    }

                    void JGCClient::add(map<JObjectPointer*, JObject*,JObjectPointer::POINTER_COMPARATOR>* objectPointers){
                        lock();
                        map<JObjectPointer*,JObject*,JObjectPointer::POINTER_COMPARATOR>::iterator it=objectPointers->begin();
                        for (;it!=objectPointers->end();it++){
                            JEndPoint* remoteEndPoint = (*it).first->getEndPoint();
                            JGCClientEndPointInfo* endPointInfo = getFromMap(endPointInfos,remoteEndPoint);
                            if (endPointInfo == NULL) {
                                endPointInfo = new JGCClientEndPointInfo(this,localServer,remoteEndPoint);
                                endPointInfos->insert(pair<JEndPoint*,JGCClientEndPointInfo*>(remoteEndPoint, endPointInfo));
                            }
                            endPointInfo->doExport((*it).first->getId(), (*it).second);
                        }
                        unlock();
                    }

                    void JGCClient::remove(JEndPoint* endPoint){
                        lock();
                        endPointInfos->erase(endPoint);
                        unlock();
                    }

                    void JGCClient::unexport(){
                        lock();
                        vector<JGCClientEndPointInfo*>* vec=getValues(endPointInfos);
                        unlock();
                        for (unsigned int i=0;i<vec->size();i++){
                            JGCClientEndPointInfo* epi=vec->at(i);
                            epi->unexport();
                        }
                        delete vec;
                    }

                    JIGCClientListener* JGCClient::getGCClientListener(){
                        return gcClientListener;
                    }

                    JGCClient::~JGCClient(){
                        delete endPointInfos;
                    }

                }
            }
        }
    }
}


