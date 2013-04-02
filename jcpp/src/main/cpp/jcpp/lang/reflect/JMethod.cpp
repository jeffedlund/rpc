#include "JMethod.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JModifier.h"
#include <sstream>

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JMethodClass : public JClass{
                public:
                    JMethodClass():JClass(JClassLoader::getBootClassLoader()){
                        canonicalName="java.lang.reflect.Method";
                        name="java.lang.reflect.Method";
                        simpleName="Method";
                        addInterface(JMember::getClazz());
                    }

                    JClass* getSuperclass(){
                        return JAccessibleObject::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JMethod::getClazz(){
                if (clazz==NULL){
                    clazz= new JMethodClass();
                }
                return clazz;
            }

            JMethod::JMethod(string name,JClass* declaringClass,JClass* returnType,vector<JClass*>* parameterType,invocation inv):JAccessibleObject(getClazz()){
                this->name=name;
                this->declaringClass=declaringClass;
                this->returnType=returnType;
                this->parameterType=parameterType;
                this->inv=inv;
            }

            string JMethod::getName(){
                return name;
            }

            JClass* JMethod::getDeclaringClass(){
                return declaringClass;
            }

            jint JMethod::getModifiers(){
                return modifiers;
            }

            jbool JMethod::isSynthetic() {
                return JModifier::isSynthetic(getModifiers());
            }

            JClass* JMethod::getReturnType(){
                return returnType;
            }

            vector<JClass*>* JMethod::getParameterType(){
                return parameterType;
            }

            JObject* JMethod::invoke(JObject* object, vector<JObject*>*args){
                return inv(object,args);
            }

            bool JMethod::equals(JObject* obj) {
                if (obj != NULL && getClazz()!=obj->getClass()) {
                    JMethod* other = dynamic_cast<JMethod*>(obj);
                    if (getDeclaringClass()->equals(other->getDeclaringClass()) && (getName() == other->getName())) {
                        if (!returnType->equals(other->getReturnType())){
                            return false;
                        }
                        //TODO return equalParamTypes(parameterTypes, other.parameterTypes);
                    }
                }
                return false;
            }

            jint JMethod::hashCode() {
                return JString::hashCode(getDeclaringClass()->getName())^ JString::hashCode(getName());
            }

            string JMethod::toString(){
                stringstream ss;
                ss<<returnType->getName()<<" ";
                ss<<declaringClass<<"."<<name;
                if (parameterType!=NULL){
                    ss<<"(";
                    for (unsigned int i=0;i<parameterType->size();i++){
                        JClass* param=parameterType->at(i);
                        ss<<param->getName()+",";
                    }
                }
                return ss.str();
            }

            JMethod::~JMethod(){
                delete parameterType;
            }
        }
    }
}
