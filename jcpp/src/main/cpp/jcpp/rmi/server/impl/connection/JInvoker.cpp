#include "JInvoker.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnection.h"
#include "JConnectionException.h"
#include "JConnectionOutputStream.h"
#include "JConnectionInputStream.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    static JObject* staticGetObjectPointer(JObject* object){
                        JInvoker* s=(JInvoker*)object;
                        return s->getObjectPointer();
                    }

                    static void staticSetObjectPointer(JObject* object,JObject* value){
                        JInvoker* s=(JInvoker*)object;
                        s->setObjectPointer((JObjectPointer*)value);
                    }

                    class JInvokerClass : public JClass{
                      public:
                        JInvokerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.Invoker";
                            this->name="jcpp.rmi.server.impl.connection.Invoker";
                            this->simpleName="Invoker";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("objectPointer",JObjectPointer::getClazz(),this,staticGetObjectPointer,staticSetObjectPointer));
                            serialVersionUID=-5888955964943945437ULL;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInvoker();
                        }
                    };

                    static JClass* clazz;

                    JClass* JInvoker::getClazz(){
                        if (clazz==NULL){
                            clazz=new JInvokerClass();
                        }
                        return clazz;
                    }

                    JInvoker::JInvoker():JObject(getClazz()){
                        this->objectInformations=NULL;
                        this->objectPointer=NULL;
                    }

                    JInvoker::JInvoker(JObjectInformations* objectInformations, JObjectPointer* objectPointer):JObject(getClazz()){
                        this->objectInformations=objectInformations;
                        this->objectPointer=objectPointer;
                    }

                    void JInvoker::setObjectPointer(JObjectPointer* o){
                        this->objectPointer=o;
                    }

                    JObjectPointer* JInvoker::getObjectPointer(){
                        return objectPointer;
                    }

                    void JInvoker::setObjectInformations(JObjectInformations* objectInformations){
                        this->objectInformations=objectInformations;
                    }

                    JObjectInformations* JInvoker::getObjectInformations(){
                        return objectInformations;
                    }

                    JObject* JInvoker::invoke(JMethod* method, vector<JObject*>* args){
                        jlong digest = objectInformations->getMethodDigester()->getDigestFromMethod(method);
                        JConnections* connections = objectInformations->getTransport()->getConnections(objectPointer->getEndPoint());
                        JConnection* connection = connections->createConnection();
                        if (!connection->openConnection()) {
                            connection->kill();
                            throw new JConnectionException("Unable to open a connection to " + objectPointer->getEndPoint()->toString());
                        }
                        connection->startCall();

                        JConnectionOutputStream* oos = new JConnectionOutputStream(connection->getOutputStream(), objectInformations, connection->getConnections()->getRemoteEndPoint());
                        oos->writeUTF(objectPointer->getId()->getString());
                        oos->writeLong(digest);
                        JPrimitiveArray* array=new JPrimitiveArray(JObject::getClazz(),args);
                        oos->writeObject(array);
                        connection->finishCall();
                        oos->done();
                        //TODO bug if delete called!!!!! delete array;

                        JObject* obj=NULL;
                        JThrowable* th=NULL;
                        JConnectionInputStream* ois = new JConnectionInputStream(connection->getInputStream(), objectInformations, objectPointer->getEndPoint());
                        jbyte exceptionCheck = ois->readByte();
                        if (exceptionCheck == JTransportConfiguration::MSG_TYPE_OK) {
                            obj = ois->readObject();
                            connection->readOk();

                        } else if (exceptionCheck == JTransportConfiguration::MSG_TYPE_EXCEPTION) {
                            th = (JThrowable*) ois->readObject();
                            connection->readOk();

                        } else {
                            th=new JEOFException("Invalid exception checking byte received while invoking method: " + method->toString() + " on object: " + objectPointer->toString());
                        }

                        ois->done();
                        connection->free();//TODO always close it even after failure
                        if (th!=NULL){
                            throw th;
                        }
                        return obj;
                    }

                    JInvoker::~JInvoker(){
                    }
                }
            }
        }
    }
}

