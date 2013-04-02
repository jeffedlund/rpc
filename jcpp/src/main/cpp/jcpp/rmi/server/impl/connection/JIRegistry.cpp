#include "JIRegistry.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JVoid.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    static JObject* invokeBind(JObject* object,vector<JObject*>*args){
                        JIRegistry* r=(JIRegistry*)object;
                        r->bind((JString*)args->at(0),(JObject*)args->at(1),(JPrimitiveArray*)args->at(2));
                        return NULL;
                    }

                    static JObject* invokeList(JObject* object,vector<JObject*>*){
                        JIRegistry* r=(JIRegistry*)object;
                        return r->list();
                    }

                    static JObject* invokeLookup(JObject* object,vector<JObject*>*args){
                        JIRegistry* r=(JIRegistry*)object;
                        return r->lookup((JString*)args->at(0));
                    }

                    static JObject* invokeRebind(JObject* object,vector<JObject*>*args){
                        JIRegistry* r=(JIRegistry*)object;
                        r->rebind((JString*)args->at(0),(JObject*)args->at(1),(JPrimitiveArray*)args->at(2));
                        return NULL;
                    }

                    static JObject* invokeUnbind(JObject* object,vector<JObject*>*args){
                        JIRegistry* r=(JIRegistry*)object;
                        r->unbind((JString*)args->at(0));
                        return NULL;
                    }

                    class JIRegistryClass : public JClass{
                      public:
                        JIRegistryClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IRegistry";
                            this->name="jcpp.rmi.server.impl.connection.IRegistry";
                            this->simpleName="IRegistry";
                            this->bIsInterface=true;
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
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JIRegistry::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIRegistryClass();
                        }
                        return clazz;
                    }

                    JIRegistry::~JIRegistry(){
                    }
                }
            }
        }
    }
}
