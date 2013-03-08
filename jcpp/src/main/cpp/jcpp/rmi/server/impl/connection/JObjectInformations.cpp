#include "JObjectInformations.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "Collections.h"
#include "JConnectionException.h"
#include "JObjectInformation.h"
#include "JGCClient.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JObjectInformationsClass : public JClass{
                      public:
                        JObjectInformationsClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectInformations";
                            this->name="jcpp.rmi.server.impl.connection.ObjectInformations";
                            this->simpleName="ObjectInformations";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JObjectInformations::getClazz(){
                        if (clazz==NULL){
                            clazz=new JObjectInformationsClass();
                        }
                        return clazz;
                    }

                    JObjectInformations::JObjectInformations(JILifecycle* lifecycle, JServer* server, JGC* gc, JGCClient* gcClient,JIInvocationListener* invListener){
                        this->idMap = new map<JString*, JObjectInformation*,JString::POINTER_COMPARATOR>();
                        this->objectMap = new map<JObject*, JObjectInformation*>();
                        this->lifecycle = lifecycle;
                        this->server = server;
                        this->gc = gc;
                        this->gcClient = gcClient;
                        this->invocationListener=invListener;
                        this->methodDigester = new JMethodDigester();
                    }

                    void JObjectInformations::setTransport(JTransport* transport){
                        this->transport=transport;
                    }

                    JTransport* JObjectInformations::getTransport(){
                        return transport;
                    }

                    JServer* JObjectInformations::getServer(){
                        return server;
                    }

                    JGC* JObjectInformations::getGC(){
                        return gc;
                    }

                    JGCClient* JObjectInformations::getGCClient(){
                        return gcClient;
                    }

                    JIInvocationListener* JObjectInformations::getInvocationListener(){
                        return this->invocationListener;
                    }

                    JMethodDigester* JObjectInformations::getMethodDigester(){
                        return methodDigester;
                    }

                    void JObjectInformations::doExport(JString* id, JObject* object, vector<JClass*>* interfaces){
                        JObjectInformation* objInfo;
                        lock();
                        objInfo=getFromMap(idMap,id);
                        if (objInfo != NULL) {
                            throw new JConnectionException("Object[" + object->toString() + "] with ID[" + id->toString() + "] already exists in ObjectInformations idMap");
                        }
                        objInfo=getFromMap(objectMap,object);
                        if ( objInfo!= NULL) {
                            throw new JConnectionException("Object[" + object->toString() + "] with ID[" + id->toString() + "] already exists in ObjectInformations objectMap");
                        }
                        objInfo = new JObjectInformation(id, object, interfaces, this, lifecycle, gc);
                        idMap->insert(pair<JString*,JObjectInformation*>(id, objInfo));
                        objectMap->insert(pair<JObject*,JObjectInformation*>(object, objInfo));
                        if (idMap->size() == 1) {
                            transport->startExport();
                        }
                        unlock();
                        objInfo->exported();
                    }

                    JObjectInformation* JObjectInformations::unexport(JString* id){
                        JObjectInformation* objInfo = remove(id);
                        if (objInfo != NULL) {
                            objInfo->unexport();
                        }
                        return objInfo;
                    }

                    JObjectInformation* JObjectInformations::unexport(JObject* object){
                        JObjectInformation* objInfo;
                        lock();
                        objInfo = getFromMap(objectMap,object);
                        unlock();
                        if (objInfo != NULL) {
                            return unexport(objInfo->getId());
                        }
                        return NULL;
                    }

                    void JObjectInformations::unexport(){
                        map<JObject*,JObjectInformation*>* objInfoArray;
                        lock();
                        objInfoArray=new map<JObject*,JObjectInformation*>(*objectMap);
                        objectMap->clear();
                        idMap->clear();
                        unlock();
                        map<JObject*,JObjectInformation*>::iterator it=objInfoArray->begin();
                        for (;it!=objInfoArray->end();it++){
                            (*it).second->unexport();
                        }
                        transport->stopExport();
                        methodDigester->clear();
                    }

                    JPrimitiveArray* JObjectInformations::list(){
                        vector<JString*>* k;
                        lock();
                        k=getKeys(idMap);
                        unlock();
                        return new JPrimitiveArray(JString::getClazz(),(vector<JObject*>*)k);
                    }

                    JObjectInformation* JObjectInformations::getObjectInformation(JString* id){
                        JObjectInformation* oi;
                        lock();
                        oi=getFromMap(idMap,id);
                        unlock();
                        return oi;
                    }

                    JObjectInformation* JObjectInformations::getObjectInformation(JObject* object){
                        JObjectInformation* oi;
                        lock();
                        oi=getFromMap(objectMap,object);
                        unlock();
                        return oi;
                    }

                    JObjectInformation* JObjectInformations::remove(JString* id){
                        JObjectInformation* objInfo;
                        lock();
                        objInfo = getFromMap(idMap,id);
                        if (objInfo != NULL) {
                            idMap->erase(id);
                            objectMap->erase(objInfo->getObject());
                            if (idMap->size() == 0) {
                                transport->stopExport();
                            }
                        }
                        unlock();
                        return objInfo;
                    }

                    JObjectInformations::~JObjectInformations(){
                        delete idMap;
                        delete objectMap;//TODO delete inside the map??
                        delete methodDigester;
                    }
                }
            }
        }
    }
}



