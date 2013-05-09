#include "JField.h"
#include "JModifier.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JException.h"
#include "JObject.h"
#include "JString.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JFieldClass : public JClass{
            public:
                JFieldClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.Field";
                    name="java.lang.reflect.Field";
                    simpleName="Field";
                    addInterface(JMember::getClazz());
                }

                JClass* getSuperclass(){
                    return JAccessibleObject::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JField::getClazz(){
                if (clazz==NULL){
                    clazz= new JFieldClass();
                }
                return clazz;
            }

            JField::JField(JString name,JClass* type, JClass* declaringClass):JAccessibleObject(getClazz()){
                this->name=name;
                this->type=type;
                this->declaringClass=declaringClass;
                this->g=NULL;
                this->s=NULL;
            }

            JField::JField(JString name,JClass* type,JClass* declaringClass, getter g,setter s):JAccessibleObject(getClazz()){
                this->name=name;
                this->type=type;
                this->declaringClass=declaringClass;
                this->g=g;
                this->s=s;
            }

            JString JField::getName(){
                return name;
            }

            JClass* JField::getType(){
                return type;
            }

            JObject* JField::get(JObject* object){
                if (g!=NULL){
                    return g(object);
                }else{
                    throw new JException("field "+toString()+" not implemented");
                }
            }

            void JField::set(JObject* object, JObject* value){
                if (s!=NULL){
                    s(object,value);
                }else{
                    throw new JException("field "+toString()+" not implemented");
                }
            }

            JClass* JField::getDeclaringClass(){
                return declaringClass;
            }

            jint JField::getModifiers(){
                return iModifiers;
            }

            jbool JField::isSynthetic(){
                return JModifier::isSynthetic(getModifiers());
            }

            bool JField::equals(JObject* o){
                if (o->getClass()!=getClazz()){
                    return false;
                }
                JField* f=dynamic_cast<JField*>(o);
                return this->getName()==f->getName() && this->getType()==f->getType() &&
                       this->getDeclaringClass()==f->getDeclaringClass();
            }

            jint JField::hashCode(){
                return getDeclaringClass()->getName().hashCode()^getName().hashCode();
            }

            JString JField::toString(){
                return getType()->getName()+" "+getDeclaringClass()->getName()+"."+getName();
            }

             JField::~JField(){
             }
        }
    }
}
