#include "JConnectionTransportDispatcher.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnectionInputStream.h"
#include "JConnectionOutputStream.h"
#include "JIInvocationExceptionHandler.h"
#include "JConnectionException.h"
#include "JServer.h"
#include <sstream>
using namespace jcpp::io;
using namespace std;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JConnectionTransportDispatcherClass : public JClass{
                      public:
                        JConnectionTransportDispatcherClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ConnectionTransportDispatcher";
                            this->name="jcpp.rmi.server.impl.connection.ConnectionTransportDispatcher";
                            this->simpleName="ConnectionTransportDispatcher";
                            addInterface(JITransportDispatcher::getClazz());
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionTransportDispatcher::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionTransportDispatcherClass();
                        }
                        return clazz;
                    }

                    JConnectionTransportDispatcher::InvocationResult::InvocationResult(JObject* object, JMethod* method, JObject* result, bool exceptionThrown){
                        this->object=object;
                        this->method=method;
                        this->result=result;
                        this->exceptionThrown=exceptionThrown;
                    }

                    JObject* JConnectionTransportDispatcher::InvocationResult::getObject(){
                        return object;
                    }

                    JMethod* JConnectionTransportDispatcher::InvocationResult::getMethod(){
                        return method;
                    }

                    JObject* JConnectionTransportDispatcher::InvocationResult::getResult(){
                        return result;
                    }

                    bool JConnectionTransportDispatcher::InvocationResult::isExceptionThrown(){
                        return exceptionThrown;
                    }

                    JConnectionTransportDispatcher::JConnectionTransportDispatcher(JObjectInformations* objectInformations):JObject(getClazz()){
                        this->objectInformations=objectInformations;
                    }

                    void JConnectionTransportDispatcher::dispatch(JEndPoint* fromEndPoint, JEndPoint*, JConnection* connection){
                        JConnectionInputStream* ois = new JConnectionInputStream(connection->getInputStream(), objectInformations, fromEndPoint);
                        JString* objectId = NULL;
                        jlong digest = 0;
                        JPrimitiveArray* args = NULL;
                        JThrowable* readException = NULL;
                        try {
                            objectId = new JString(ois->readUTF());
                            digest = ois->readLong();
                            args = (JPrimitiveArray*) ois->readObject();
                        } catch (JThrowable* e) {
                            readException = e;
                        }
                        ois->done();

                        JConnectionOutputStream* oos = new JConnectionOutputStream(connection->getOutputStream(), objectInformations, fromEndPoint);
                        try {
                            if (readException != NULL) {
                                throw readException;
                            }
                            //TODO think when to delete created objects, lifecycle in general of unmarshalled objects
                            InvocationResult* invocationResult = invokeMethod(objectId, digest, args->getObjects(), fromEndPoint);
                            JObject* result = invocationResult->getResult();
                            if (invocationResult->isExceptionThrown()) {
                                throw (JThrowable*) result;
                            }
                            oos->writeByte((jint) JTransportConfiguration::MSG_TYPE_OK);
                            oos->writeObject(result);
                            connection->sendOk(); // for the Call
                        } catch (JThrowable* throwable) {
                            oos->writeByte((jint) JTransportConfiguration::MSG_TYPE_EXCEPTION);
                            oos->writeObject(throwable);
                            oos->flush();
                            connection->sendOk(); // for the Call
                        }
                        try {
                            oos->done();
                        } catch (JThrowable* throwable) {
                            //TODO log
                        }
                    }

                    JConnectionTransportDispatcher::InvocationResult* JConnectionTransportDispatcher::invokeMethod(JString* id, jlong digest, vector<JObject*>* args, JEndPoint*){
                        JObject* object = NULL;
                        JMethod* method = NULL;
                        JObject* result = NULL;
                        bool exceptionThrown = false;

                        JObjectInformation* objectInformation = objectInformations->getObjectInformation(id);
                        if (objectInformation == NULL) {
                            exceptionThrown = true;
                            result = new JConnectionException("Object of ID: " + id->toString() + " has not been exported in " + objectInformations->getTransport()->getLocalEndPoint()->toString());
                        } else {
                            object = objectInformation->getObject();
                            method = objectInformations->getMethodDigester()->getMethodFromDigest(object, digest);
                            if (method == NULL) {
                                exceptionThrown = true;
                                vector<JMethod*>* methods = objectInformations->getMethodDigester()->getMethods(object);
                                stringstream ss;
                                ss<<"No method found for digest: ";
                                ss<< digest;
                                ss<< " on object: ";
                                ss<< object->toString();
                                ss<< "\n";
                                ss<<"Methods available for type ";
                                ss<< object->getClass()->toString();
                                ss<< ":\n";
                                for (unsigned int i=0;i<methods->size();i++){
                                    JMethod* m=methods->at(i);
                                    ss<< "\t" << m->toString() << ";\n";
                                }
                                result = new JConnectionException(ss.str());
                            } else {
                                try {
                                    result = method->invoke(object, args);
                                } catch (JThrowable* e) {
                                    exceptionThrown = true;
                                    JIInvocationExceptionHandler* handler = objectInformations->getServer()->getInvocationExceptionHandler();
                                    if (handler != NULL) {
                                        result = handler->handleException(object, method,args, e);
                                    } else {
                                        result = e;
                                    }
                                }
                            }
                        }
                        return new InvocationResult(object, method, result, exceptionThrown);
                    }

                    JConnectionTransportDispatcher::~JConnectionTransportDispatcher(){
                    }
                }
            }
        }
    }
}
