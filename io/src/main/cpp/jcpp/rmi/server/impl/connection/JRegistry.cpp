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
                    class JRegistryClass : public JClass{
                      public:
                        JRegistryClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.Registry";
                            this->name="jcpp.rmi.server.impl.connection.Registry";
                            this->simpleName="Registry";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JRegistry::getClazz(){
                        if (clazz==NULL){
                            clazz=new JRegistryClass();
                        }
                        return clazz;
                    }

                    JRegistry::JRegistry(JObjectInformations* objectInformations){
                        this->objectInformations=objectInformations;
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

                    vector<JString*>* JRegistry::list(){
                        return objectInformations->list();
                    }

                    JObject* JRegistry::lookup(JString* id){
                        JObjectInformation* objInfo = objectInformations->getObjectInformation(id);
                        if(objInfo == NULL) {
                            throw new JConnectionException("Object of ID: " + id->toString() + " is not bound in registry at: " + objectInformations->getTransport()->getLocalEndPoint()->toString());
                        }
                        return objInfo->getObject();
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
                        objectInformations->doExport(id, object, interfaces);
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

