#include "JConnectionTransportDispatcher.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnectionInputStream.h"
#include "JConnectionOutputStream.h"
#include "JIInvocationExceptionHandler.h"
#include "JConnectionException.h"
#include "JServer.h"
using namespace jcpp::io;

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

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
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

                    void JConnectionTransportDispatcher::dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndPoint, JConnection* connection){
                        JConnectionInputStream* ois = new JConnectionInputStream(connection->getInputStream(), objectInformations, fromEndPoint);
                        JString* objectId = NULL;
                        jlong digest = 0;
                        JPrimitiveArray* args = NULL;
                        JThrowable* readException = NULL;
                        try {
                            objectId = NULL;//TODO ois->readUTF();
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
                            InvocationResult* invocationResult = invokeMethod(objectId, digest, NULL/*TODO args*/, fromEndPoint);
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
                            //log
                        }
                    }

                    JConnectionTransportDispatcher::InvocationResult* JConnectionTransportDispatcher::invokeMethod(JString* id, jlong digest, vector<JObject*>* args, JEndPoint* endPoint){
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
                            method = 0;//TODO objectInformations->getMethodDigester()->getMethodFromDigest(object, digest);
                            if (method == NULL) {
                                exceptionThrown = true;
//                                Method[] methods = objectInformations.getMethodDigester().getMethods(object);
//                                String classDescription = "Methods available for type " + object.getClass() + ":\n";
//                                for (Method classMethod : methods) {
//                                    classDescription += "\t" + classMethod.toString() + ";\n";
//                                } TODO
                                result = NULL;//TODO new JConnectionException("No method found for digest: " + digest + " on object: " + object->toString() + "\n");//TODO + classDescription);
                            } else {
                                try {
                                    result = method->invoke(object, args);
                                } catch (JThrowable* e) {
                                    exceptionThrown = true;
                                    JIInvocationExceptionHandler* handler = NULL;//TODO objectInformations->getServer()->getInvocationExceptionHandler();
                                    if (handler != NULL) {
                                        result = handler->handleException(object, method,NULL/* args*/, e);
                                    } else {
//                                        if (e instanceof InvocationTargetException) {
//                                            result = e.getCause();
//                                        } else {//TODO
                                            result = e;
                                        //}
                                    }
                                }
                            }
                        }
                        return new InvocationResult(object, method, result, exceptionThrown);
                    }
                }
            }
        }
    }
}


