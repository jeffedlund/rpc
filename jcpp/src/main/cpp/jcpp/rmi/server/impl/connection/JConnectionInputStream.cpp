#include "JConnectionInputStream.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnectionException.h"
#include "JProxy.h"
#include "JObjectHandler.h"
#include "JGCClient.h"
#include "JInvoker.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JConnectionInputStreamClass : public JClass{
                      public:
                        JConnectionInputStreamClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ConnectionInputStream";
                            this->name="jcpp.rmi.server.impl.connection.ConnectionInputStream";
                            this->simpleName="ConnectionInputStream";
                        }

                        JClass* getSuperclass(){
                            return JObjectInputStream::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionInputStream::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionInputStreamClass();
                        }
                        return clazz;
                    }

                    JConnectionInputStream::JConnectionInputStream(JInputStream* in, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint):JObjectInputStream(in,getClazz()){
                        this->enableResolveObject(true);
                        this->objectInformations = objectInformations;
                        this->gcObjectPointers = new map<JObjectPointer*, JObject*,JObjectPointer::POINTER_COMPARATOR>();
                        this->remoteEndPoint = remoteEndPoint;
                    }

                    void JConnectionInputStream::done(){
                        objectInformations->getGCClient()->add(gcObjectPointers);
                        gcObjectPointers->clear();
                    }

                    JObject* JConnectionInputStream::resolveObject(JObject* obj){
                        if (obj->getClass()->isProxy()) {
                            JInvocationHandler* invocationHandler = ((JProxy*)obj)->getInvocationHandler();
                            if (((JObject*)invocationHandler)->getClass()==JObjectHandler::getClazz()) {
                                JObjectHandler* objectHandler = (JObjectHandler*) invocationHandler;
                                objectHandler->setObjectInformations(objectInformations);
                                JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                                if ((*objectPointer->getEndPoint())==(*objectInformations->getTransport()->getLocalEndPoint())) {
                                    return objectInformations->getObjectInformation(objectPointer->getId())->getObject();
                                }
                                gcObjectPointers->insert(pair<JObjectPointer*,JObject*>(objectPointer, obj));
                                return obj;
                            }
                        } else if (obj->getClass()==JNotSerializableException::getClazz()) {
                            throw (JNotSerializableException*) obj;
                        }
                        return obj;
                    }

                    JConnectionInputStream::~JConnectionInputStream(){
                        delete gcObjectPointers;
                    }
                }
            }
        }
    }
}


