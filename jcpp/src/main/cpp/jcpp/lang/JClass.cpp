#ifndef JCLASS_CPP
#define JCLASS_CPP

#include "JClass.h"
#include "JClassLoader.h"
#include "JMethod.h"
#include "JEnum.h"
#include "Collections.h"
#include "JNoSuchFieldException.h"
#include "JNoSuchMethodException.h"
#include "JIllegalArgumentException.h"
#include "JPrimitiveBoolean.h"
#include "JPrimitiveByte.h"
#include "JPrimitiveChar.h"
#include "JPrimitiveDouble.h"
#include "JPrimitiveFloat.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveLong.h"
#include "JPrimitiveShort.h"
#include "JVoid.h"
#include <sstream>
#include "JInternalError.h"
#include <algorithm>
#include "JNullPointerException.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JClassClass : public JClass{
            public:
            JClassClass():JClass(true){
                this->canonicalName="java.lang.Class";
                this->name="java.lang.Class";
                this->simpleName="Class";
                this->serialVersionUID=3206093459760846163ULL;
            }

            JClassLoader* getClassLoader(){
                return JClassLoader::getBootClassLoader();
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return this;//returning itself, bof ...
            }

        };

        static JClass* clazz;

        JClass* JClass::getClazz(){
            if (clazz==NULL){
                clazz=new JClassClass();
            }
            return clazz;
        }

        string JClass::getSignature(){
            JClass* _class=this;
            stringstream ss;
            while (_class->isArray()){
                ss<<"[";
                _class=_class->getComponentType();
            }
            if (_class->isPrimitive()){
                if (_class== JPrimitiveInt::getClazz()) {
                    ss<<'I';
                }else if (_class == JPrimitiveByte::getClazz()) {
                    ss<<'B';
                } else if (_class == JPrimitiveLong::getClazz()) {
                    ss<<'J';
                } else if (_class == JPrimitiveFloat::getClazz()) {
                    ss<<'F';
                } else if (_class == JPrimitiveDouble::getClazz()) {
                    ss<<'D';
                } else if (_class == JPrimitiveShort::getClazz()) {
                    ss<<'S';
                } else if (_class == JPrimitiveChar::getClazz()) {
                    ss<<'C';
                } else if (_class == JPrimitiveBoolean::getClazz()) {
                    ss<<'Z';
                } else if (_class == JVoid::getClazz()) {
                    ss<<'V';
                } else {
                    throw new JInternalError();
                }
            }else{
                string name=_class->getName();
                string newName(name);
                replace(newName.begin(),newName.end(),'/','.');
                ss<<'L'<<newName<<";";
            }
            return ss.str();
        }

        JClass::JClass(JClassLoader* classLoader):JObject(JClass::getClazz()){
            this->classLoader=classLoader;
            this->bIsArray=false;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->bIsInterface=false;
            this->bIsPrimitive=false;
            this->bIsPackage=false;
            this->componentType=NULL;
            this->enumConstants=new vector<JEnum*>;
            this->fields=new map<string,JField*>;
            this->fieldsList=new vector<JField*>;
            this->declaredFields=new map<string,JField*>;
            this->declaredFieldsList=new vector<JField*>;
            this->methods=new map<string,JMethod*>;
            this->methodsList=new vector<JMethod*>;
            this->declaredMethods=new map<string,JMethod*>;
            this->declaredMethodsList=new vector<JMethod*>;
            this->interfaces=new vector<JClass*>;
        }

        JClass::JClass():JObject(JClass::getClazz()){
            this->classLoader=JClassLoader::getBootClassLoader();
            this->bIsArray=false;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->bIsInterface=false;
            this->bIsPrimitive=false;
            this->bIsPackage=false;
            this->componentType=NULL;
            this->enumConstants=new vector<JEnum*>;
            this->fields=new map<string,JField*>;
            this->fieldsList=new vector<JField*>;
            this->declaredFields=new map<string,JField*>;
            this->declaredFieldsList=new vector<JField*>;
            this->methods=new map<string,JMethod*>;
            this->methodsList=new vector<JMethod*>;
            this->declaredMethods=new map<string,JMethod*>;
            this->declaredMethodsList=new vector<JMethod*>;
            this->interfaces=new vector<JClass*>;
        }

        JClass::JClass(bool root):JObject(root){
            this->bIsArray=false;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->bIsInterface=false;
            this->bIsPrimitive=false;
            this->bIsPackage=false;
            this->componentType=NULL;
            this->enumConstants=new vector<JEnum*>;
            this->fields=new map<string,JField*>;
            this->fieldsList=new vector<JField*>;
            this->declaredFields=new map<string,JField*>;
            this->declaredFieldsList=new vector<JField*>;
            this->methods=new map<string,JMethod*>;
            this->methodsList=new vector<JMethod*>;
            this->declaredMethods=new map<string,JMethod*>;
            this->declaredMethodsList=new vector<JMethod*>;
            this->interfaces=new vector<JClass*>;
        }

        string JClass::getCanonicalName(){
            return canonicalName;
        }

        string JClass::getName(){
            return name;
        }

        string JClass::getSimpleName(){
            return simpleName;
        }

        JClassLoader* JClass::getClassLoader(){
            return classLoader;
        }

        JClass* JClass::getComponentType(){
            return componentType;
        }

        vector<JEnum*>* JClass::getEnumConstants(){
            return enumConstants;
        }

        JEnum* JClass::valueOf(string value){
            for (unsigned int i=0;i<enumConstants->size();i++){
                JEnum* e=enumConstants->at(i);
                if (e->getName()->getString()==value){
                    return e;
                }
            }
            throw new JIllegalArgumentException("No enum constant "+value+" in enum "+getName());
        }

        JField* JClass::getField(string name){
            initFields();
            JField* field=getFromMap(fields,name);
            if (field==NULL){
                throw JNoSuchFieldException("field "+name+" not delared in "+getName());
            }
            return field;
        }

        JField* JClass::getDeclaredField(string name){
            JField* field=getFromMap(declaredFields,name);
            if (field==NULL){
                throw JNoSuchFieldException("field "+name+" not delared in "+getName());
            }
            return field;
        }

        void JClass::initFields(){
            if (fieldsList->size()==0){
                JClass* current=this;
                while (current!=NULL){
                    for (unsigned int i=0;i<current->declaredFieldsList->size();i++){
                        JField* f=current->declaredFieldsList->at(i);//TODO add it or check before? ...
                        fieldsList->push_back(f);
                        fields->insert(pair<string,JField*>(f->getName(),f));
                    }
                    current=current->getSuperclass();
                }
            }
        }

        vector<JField*>* JClass::getFields(){
            initFields();
            return fieldsList;
        }

        vector<JField*>* JClass::getDeclaredFields(){
            return declaredFieldsList;
        }

        vector<JClass*>* JClass::getInterfaces(){
            return interfaces;
        }

        bool JClass::hasMethod(string name, vector<JClass*>*){
            initMethods();
            JMethod* method=getFromMap(methods,name);
            if (method==NULL){
                return false;
            }
            return true;
        }

        bool JClass::hasDeclaredMethod(string name, vector<JClass*>*){
            JMethod* method=getFromMap(declaredMethods,name);
            if (method==NULL){
                return false;
            }
            return true;
        }

        JMethod* JClass::getMethod(string name, vector<JClass*>*){
            initMethods();
            JMethod* method=getFromMap(methods,name);
            if (method==NULL){
                throw JNoSuchMethodException("method "+name+" not declared in "+getName());//we should check using signature ...
            }
            return method;
        }

        JMethod* JClass::getDeclaredMethod(string name, vector<JClass*>*){
            JMethod* method=getFromMap(declaredMethods,name);
            if (method==NULL){
                throw JNoSuchMethodException("method "+name+" not declared in "+getName());//we should check using signature ...
            }
            return method;
        }

        void JClass::initMethods(){
            if (methodsList->size()==0){
                JClass* current=this;
                while (current!=NULL){
                    for (unsigned int i=0;i<current->declaredMethodsList->size();i++){
                        JMethod* m=current->declaredMethodsList->at(i);//TODO add it or check before ...
                        methodsList->push_back(m);
                        methods->insert(pair<string,JMethod*>(m->getName(),m));
                    }
                    current=current->getSuperclass();
                }
            }
        }

        vector<JMethod*>* JClass::getMethods(){
            initMethods();
            return methodsList;
        }

        vector<JMethod*>* JClass::getDeclaredMethods(){
            return declaredMethodsList;
        }

        void JClass::addEnumConstant(JEnum* enumConstant){
            enumConstants->push_back(enumConstant);
        }

        void JClass::addField(JField* field){
            declaredFieldsList->push_back(field);
            declaredFields->insert(pair<string,JField*>(field->getName(),field));
        }

        void JClass::addMethod(JMethod* method){
            declaredMethodsList->push_back(method);
            declaredMethods->insert(pair<string,JMethod*>(method->getName(),method));
        }

        void JClass::addInterface(JClass* interface){
            if (!interface->isInterface()){
                throw new JIllegalArgumentException("class "+interface->getName()+" is not typed as an interface");
            }
            if (!interface->getSuperclass()->isInterface()){
                throw new JIllegalArgumentException("class "+interface->getName()+" doesnt not declare "+JInterface::getClazz()->getName()+" as its parent class");
            }
            interfaces->push_back(interface);
        }

        bool JClass::isArray(){
            return bIsArray;
        }

        bool JClass::isProxy(){
            return bIsProxy;
        }

        bool JClass::isEnum(){
            return bIsEnum;
        }

        bool JClass::isAssignableFrom(JClass* clazz){
            JClass* current=clazz;
            while (current!=NULL){
                if (current==this){
                    return true;
                }
                for (unsigned int i=0;i<current->getInterfaces()->size();i++){
                     JClass* interf=current->getInterfaces()->at(i);
                     if (this==interf){
                        return true;
                     }
                }
                current=current->getSuperclass();//check also interfaces
            }
            return false;
        }

        bool JClass::isInstance(JObject* object){
            if (object==NULL){
                throw new JNullPointerException();
            }
            JClass* classObject=object->getClass();
            return isAssignableFrom(classObject);
        }

        bool JClass::isInterface(){
            return bIsInterface;
        }

        bool JClass::isPrimitive(){
            return bIsPrimitive;
        }

        bool JClass::isPackage(){
            return bIsPackage;
        }

        jlong JClass::getSerialVersionUID(){
            return serialVersionUID;
        }

        string JClass::toString(){
            return (isInterface()?"interface ":(isPrimitive()?"":"class "))+getName();
        }

        JClass::~JClass(){
            deleteVectorOfPointers(this->enumConstants);
            deleteVectorOfPointers(this->interfaces);
            deleteMapOfValuePointer(fields);
            deleteVectorOfPointers(fieldsList);
            deleteMapOfValuePointer(declaredFields);
            deleteVectorOfPointers(declaredFieldsList);
            deleteMapOfValuePointer(methods);
            deleteVectorOfPointers(methodsList);
            deleteMapOfValuePointer(declaredMethods);
            deleteVectorOfPointers(declaredMethodsList);
        }
    }
}

#endif // JCLASS_CPP