#include "JField.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JFieldClass : public JClass{
            public:
                JFieldClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.Field";
                    name="java.lang.reflect.Field";
                    simpleName="Field";
                }

                JClass* getSuperclass(){
                    return JAccessibleObject::getClazz();
                }

                JObject* newInstance(){
                    throw new JInstantiationException("cannot instantiate object of class "+getName());
                }
            };

            static JClass* clazz;

            JClass* JField::getClazz(){
                if (clazz==NULL){
                    clazz= new JFieldClass();
                }
                return clazz;
            }

            JField::JField(string name,JClass* type):JAccessibleObject(getClazz()){
                this->name=name;
                this->type=type;
                this->g=NULL;
                this->s=NULL;
            }

            JField::JField(string name,JClass* type,getter g,setter s):JAccessibleObject(getClazz()){
                this->name=name;
                this->type=type;
                this->g=g;
                this->s=s;
            }

            string JField::getName(){
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

            string JField::toString(){
                return getType()->getName()+"."+getName();
            }

             JField::~JField(){
             }
        }
    }
}
