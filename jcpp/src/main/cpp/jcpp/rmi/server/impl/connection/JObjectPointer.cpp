#include "JObjectPointer.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    static JObject* staticGetEndPoint(JObject* object){
                        JObjectPointer* s=(JObjectPointer*)object;
                        return s->getEndPoint();
                    }

                    static void staticSetEndPoint(JObject* object,JObject* value){
                        JObjectPointer* s=(JObjectPointer*)object;
                        s->setEndPoint((JEndPoint*)value);
                    }

                    static JObject* staticGetId(JObject* object){
                        JObjectPointer* s=(JObjectPointer*)object;
                        return s->getId();
                    }

                    static void staticSetId(JObject* object,JObject* value){
                        JObjectPointer* s=(JObjectPointer*)object;
                        s->setId((JString*)value);
                    }

                    class JObjectPointerClass : public JClass{
                      public:
                        JObjectPointerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ObjectPointer";
                            this->name="jcpp.rmi.server.impl.connection.ObjectPointer";
                            this->simpleName="ObjectPointer";
                            addInterface(JSerializable::getClazz());
                            addField(new JField("endPoint",JEndPoint::getClazz(),this,staticGetEndPoint,staticSetEndPoint));
                            addField(new JField("id",JString::getClazz(),this,staticGetId,staticSetId));
                            serialVersionUID=1L;
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            return new JObjectPointer();
                        }
                    };

                    static JClass* clazz;

                    JClass* JObjectPointer::getClazz(){
                        if (clazz==NULL){
                            clazz=new JObjectPointerClass();
                        }
                        return clazz;
                    }

                    JObjectPointer::JObjectPointer():JObject(getClazz()){
                        this->id=new JString("");
                        this->endPoint=new JEndPoint();
                    }

                    JObjectPointer::JObjectPointer(JEndPoint* endPoint, JString* id):JObject(getClazz()){
                        this->endPoint=endPoint;
                        this->id=id;
                    }

                    bool JObjectPointer::equals(JObject* other){
                        if (other->getClass()!=getClazz()){
                            return false;
                        }
                        JObjectPointer* s=dynamic_cast<JObjectPointer*>(other);
                        return (*s->endPoint)==(*endPoint) && (*s->id)==(*id);
                    }

                    JEndPoint* JObjectPointer::getEndPoint(){
                        return endPoint;
                    }

                    void JObjectPointer::setEndPoint(JEndPoint* endPoint){
                        delete this->endPoint;
                        this->endPoint=endPoint;
                    }

                    JString* JObjectPointer::getId(){
                        return id;
                    }

                    void JObjectPointer::setId(JString* id){
                        this->id=id;
                    }

                    jint JObjectPointer::hashCode(){
                        jint h=1;
                        h=h*31+id->hashCode();
                        h=h*31+endPoint->hashCode();
                        return h;
                    }

                    string JObjectPointer::toString(){
                        return "ObjectPointer[" + endPoint->toString() + "[Id:" + id->toString() + "]]";
                    }

                    JObjectPointer::~JObjectPointer(){
                        delete endPoint;
                        delete id;
                    }
                }
            }
        }
    }
}

