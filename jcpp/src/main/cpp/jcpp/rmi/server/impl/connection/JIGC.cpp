#include "JIGC.h"
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
                    class JIGCClass : public JClass{
                    protected:
                        static JObject* invokePing(JObject* object,vector<JObject*>* args){
                            JIGC* gc=dynamic_cast<JIGC*>(object);
                            return gc->ping((JEndPoint*)args->at(0),(JPrimitiveArray*)args->at(1));
                        }

                        static JObject* invokeEndPointDead(JObject* object,vector<JObject*>* args){
                            JIGC* gc=dynamic_cast<JIGC*>(object);
                            gc->endPointDead((JEndPoint*)args->at(0));
                            return NULL;
                        }

                        static JObject* invokeGetExportedEndPoints(JObject* object,vector<JObject*>*){
                            JIGC* gc=dynamic_cast<JIGC*>(object);
                            return gc->getExportedEndPoints();
                        }

                      public:
                        JIGCClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IGC";
                            this->name="jcpp.rmi.server.impl.connection.IGC";
                            this->simpleName="IGC";
                            this->bIsInterface=true;

                            vector<JClass*>* param=new vector<JClass*>();
                            param->push_back(JEndPoint::getClazz());
                            param->push_back(JPrimitiveArray::getClazz(JString::getClazz()));
                            addMethod(new JMethod("ping",this,JPrimitiveArray::getClazz(JPrimitiveBoolean::getClazz()),param,invokePing));

                            param=new vector<JClass*>();
                            param->push_back(JEndPoint::getClazz());
                            addMethod(new JMethod("endPointDead",this,JVoid::getClazz(),param,invokeEndPointDead));

                            param=new vector<JClass*>();
                            addMethod(new JMethod("getExportedEndPoints",this,JPrimitiveArray::getClazz(JEndPoint::getClazz()),param,invokeGetExportedEndPoints));
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JIGC::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClass();
                        }
                        return clazz;
                    }

                    JIGC::~JIGC(){
                    }
                }
            }
        }
    }
}


