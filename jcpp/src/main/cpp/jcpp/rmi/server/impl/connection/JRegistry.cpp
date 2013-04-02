#include "JRegistry.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnectionException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                //TODO not extra, method duplication with interface ....
                    static JObject* invokeBind(JObject* object,vector<JObject*>*args){
                        JRegistry* r=(JRegistry*)object;
                        r->bind((JString*)args->at(0),(JObject*)args->at(1),(JPrimitiveArray*)args->at(2));
                        return NULL;
                    }

                    static JObject* invokeList(JObject* object,vector<JObject*>*){
                        JRegistry* r=(JRegistry*)object;
                        return r->list();
                    }

                    static JObject* invokeLookup(JObject* object,vector<JObject*>*args){
                        JRegistry* r=(JRegistry*)object;
                        return r->lookup((JString*)args->at(0));
                    }

                    static JObject* invokeRebind(JObject* object,vector<JObject*>*args){
                        JRegistry* r=(JRegistry*)object;
                        r->rebind((JString*)args->at(0),(JObject*)args->at(1),(JPrimitiveArray*)args->at(2));
                        return NULL;
                    }

                    static JObject* invokeUnbind(JObject* object,vector<JObject*>*args){
                        JRegistry* r=(JRegistry*)object;
                        r->unbind((JString*)args->at(0));
                        return NULL;
                    }

                    class JRegistryClass : public JClass{
                      public:
                        JRegistryClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.Registry";
                            this->name="jcpp.rmi.server.impl.connection.Registry";
                            this->simpleName="Registry";

                            vector<JClass*>* param=new vector<JClass*>();
                            param->push_back(JString::getClazz());
                            param->push_back(JObject::getClazz());
                            param->push_back(JPrimitiveArray::getClazz(JClass::getClazz()));
                            addMethod(new JMethod("bind",this,JVoid::getClazz(),param,invokeBind));

                            param=new vector<JClass*>();
                            addMethod(new JMethod("list",this,JPrimitiveArray::getClazz(JString::getClazz()),param,invokeList));

                            param=new vector<JClass*>();
                            param->push_back(JString::getClazz());
                            addMethod(new JMethod("lookup",this,JObject::getClazz(),param,invokeLookup));

                            param=new vector<JClass*>();
                            param->push_back(JString::getClazz());
                            param->push_back(JObject::getClazz());
                            param->push_back(JPrimitiveArray::getClazz(JClass::getClazz()));
                            addMethod(new JMethod("rebind",this,JVoid::getClazz(),param,invokeRebind));

                            param=new vector<JClass*>();
                            param->push_back(JString::getClazz());
                            addMethod(new JMethod("unbind",this,JVoid::getClazz(),param,invokeUnbind));
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JRegistry::getClazz(){
                        if (clazz==NULL){
                            clazz=new JRegistryClass();
                        }
                        return clazz;
                    }

                    JRegistry::JRegistry(JObjectInformations* objectInformations):JObject(getClazz()){
                        this->objectInformations=objectInformations;
                    }

                    void JRegistry::bind(JString* id, JObject* object, JPrimitiveArray* interfaces){
                        bind(id, object, (vector<JClass*>*)interfaces->getObjects());
                    }

                    void JRegistry::bind(JString* id, JObject* object, vector<JClass*>* interfaces){
                        if(object == NULL) {
                            throw new JConnectionException("Bind Error: Attempting to bind a null object");
                        }
                        if(id == NULL) {
                            throw new JConnectionException("Bind Error: Attempting to bind an object with an invalid id.");
                        }
                        if(interfaces == NULL || interfaces->size()==0) {
                            throw new JConnectionException("Bind Error: Attempting to bind and object without any specified interfaces.");
                        }
                        JObjectInformation* objInfo = objectInformations->getObjectInformation(id);
                        if (objInfo == NULL) {
                            objectInformations->doExport(id, object, interfaces);
                        } else {
                            throw new JConnectionException("Bind Error: Object already bound: " + objInfo->toString() + " at: " + objectInformations->getTransport()->getLocalEndPoint()->toString());
                        }
                    }

                    JPrimitiveArray* JRegistry::list(){
                        return objectInformations->list();
                    }

                    JObject* JRegistry::lookup(JString* id){
                        JObjectInformation* objInfo = objectInformations->getObjectInformation(id);
                        if(objInfo == NULL) {
                            throw new JConnectionException("Object of ID: " + id->toString() + " is not bound in registry at: " + objectInformations->getTransport()->getLocalEndPoint()->toString());
                        }
                        return objInfo->getObject();
                    }

                    void JRegistry::rebind(JString* id, JObject* object, JPrimitiveArray* interfaces){
                        rebind(id, object, (vector<JClass*>*)interfaces->getObjects());
                    }

                    void JRegistry::rebind(JString* id, JObject* object, vector<JClass*>* interfaces){
                        if(object == NULL) {
                            throw new JConnectionException("Bind Error: Attempting to bind a null object");
                        }
                        if(id == NULL) {
                            throw new JConnectionException("Bind Error: Attempting to bind an object with an invalid id.");
                        }
                        if(interfaces == NULL || interfaces->size()==0) {
                            throw new JConnectionException("Bind Error: Attempting to bind and object without any specified interfaces.");
                        }
                        objectInformations->doExport(id, object,interfaces);
                    }

                    void JRegistry::unbind(JString* id){
                        if (objectInformations->unexport(id) == NULL) {
                            throw new JConnectionException("Object of ID: " + id->toString() + " is not bound in registry at: " + objectInformations->getTransport()->getLocalEndPoint()->toString());
                        }
                    }

                    JRegistry::~JRegistry(){
                    }
                }
            }
        }
    }
}

