#include "JLevel.h"
#include "JClass.h"
#include "JInteger.h"
#include "JIllegalArgumentException.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLevelClass : public JClass{
                protected:
                    static JObject* staticGetName(JObject* object){
                        JLevel* s=(JLevel*)object;
                        return s->name;
                    }

                    static void staticSetName(JObject* object,JObject* value){
                        JLevel* s=(JLevel*)object;
                        if (s->name!=NULL){
                            delete s->name;
                        }
                        s->name=(JString*)value;
                    }

                    static JObject* staticGetValue(JObject* object){
                        JLevel* s=(JLevel*)object;
                        return s->value;
                    }

                    static void staticSetValue(JObject* object,JObject* value){
                        JLevel* s=(JLevel*)object;
                        if (s->value!=NULL){
                            delete s->value;
                        }
                        s->value=(JPrimitiveInt*)value;
                    }

                    static JObject* staticGetResouveBundleName(JObject* object){
                        JLevel* s=(JLevel*)object;
                        return s->resourceBundleName;
                    }

                    static void staticSetResourceBundleName(JObject* object,JObject* value){
                        JLevel* s=(JLevel*)object;
                        if (s->resourceBundleName!=NULL){
                            delete s->resourceBundleName;
                        }
                        s->resourceBundleName=(JString*)value;
                    }

                public:
                    JLevelClass(){
                        this->canonicalName="java.util.logging.Level";
                        this->name="java.util.logging.Level";
                        this->simpleName="Level";
                        this->serialVersionUID=-8176160795706313070ULL;
                        addInterface(JSerializable::getClazz());

                        addField(new JField("name",JString::getClazz(),this,staticGetName,staticSetName));
                        addField(new JField("value",JPrimitiveInt::getClazz(),this,staticGetValue,staticSetValue));
                        addField(new JField("resourceBundleName",JString::getClazz(),this,staticGetResouveBundleName,staticSetResourceBundleName));
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }

                    JObject* newInstance(){
                        return new JLevel();
                    }
            };

            static JClass* clazz;

            JClass* JLevel::getClazz(){
                if (clazz==NULL){
                    clazz=new JLevelClass();
                }
                return clazz;
            }

            JLevel::JLevel():JObject(getClazz()){
                this->name=NULL;
                this->value=NULL;
                this->resourceBundleName=NULL;
            }

            JLevel::JLevel(JString name, jint value):JObject(getClazz()){
                this->name=new JString(name);
                this->value=new JPrimitiveInt(value);
                this->resourceBundleName=NULL;
            }


            JLevel* JLevel::parse(JString name){
                if (name.equals("OFF")){
                    return OFF;
                }
                if (name.equals("SEVERE")){
                    return SEVERE;
                }
                if (name.equals("WARNING")){
                    return WARNING;
                }
                if (name.equals("INFO")){
                    return INFO;
                }
                if (name.equals("CONFIG")){
                    return CONFIG;
                }
                if (name.equals("FINE")){
                    return FINE;
                }
                if (name.equals("FINER")){
                    return FINER;
                }
                if (name.equals("FINEST")){
                    return FINEST;
                }
                if (name.equals("ALL")){
                    return ALL;
                }
                throw new JIllegalArgumentException("Bad level \"" + name + "\"");
            }

            JLevel* JLevel::OFF = new JLevel("OFF",JInteger::MAX_VALUE);

            JLevel* JLevel::SEVERE = new JLevel("SEVERE",1000);

            JLevel* JLevel::WARNING = new JLevel("WARNING",900);

            JLevel* JLevel::INFO = new JLevel("INFO",800);

            JLevel* JLevel::CONFIG = new JLevel("CONFIG",700);

            JLevel* JLevel::FINE = new JLevel("FINE",500);

            JLevel* JLevel::FINER = new JLevel("FINER",400);

            JLevel* JLevel::FINEST = new JLevel("FINEST",300);

            JLevel* JLevel::ALL = new JLevel("ALL",JInteger::MIN_VALUE);

            JString JLevel::getName(){
                return *name;
            }

            JString JLevel::toString(){
                return *name;
            }

            jint JLevel::intValue(){
                return value->get();
            }

            jbool JLevel::equals(JObject* o){
                if (o->getClass()!=getClazz()){
                    return false;
                }
                JLevel* l=(JLevel*)o;
                return l->name->equals(name) && l->value->equals(value);
            }

            jint JLevel::hashCode(){
                return value->get();
            }

            JLevel::~JLevel(){
                if (name!=NULL){
                    delete name;
                }
                if (value!=NULL){
                    delete value;
                }
                if (resourceBundleName!=NULL){
                    delete resourceBundleName;
                }
            }
        }
    }
}

//            
