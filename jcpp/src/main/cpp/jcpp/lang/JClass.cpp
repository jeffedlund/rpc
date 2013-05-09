#ifndef JCLASS_CPP
#define JCLASS_CPP

#include "JClass.h"
#include "JObject.h"
#include "JClassLoader.h"
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
#include "JModifier.h"
#include "JString.h"
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

            void fillInterfaces(){
                addInterface(JSerializable::getClazz());
            }
        };

        static JClass* clazz;

        JClass* JClass::getClazz(){
            if (clazz==NULL){
                clazz=new JClassClass();
            }
            return clazz;
        }

        JString JClass::getSignature(){
            JClass* _class=this;
            JString ss;
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
                JString name=_class->getName();
                JString newName=name.replace('/','.');
                ss<<'L'<<newName<<";";
            }
            return ss;
        }

        JClass::JClass(JClassLoader* classLoader):JObject(JClass::getClazz()){
            init(classLoader);
        }

        JClass::JClass():JObject(JClass::getClazz()){
            init(JClassLoader::getBootClassLoader());
        }

        JClass::JClass(bool root):JObject(root){
            init(NULL);
        }

        void JClass::init(JClassLoader* cl){
            this->classLoader=cl;
            this->serialVersionUID=0;
            this->bIsArray=false;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->bIsInterface=false;
            this->bIsPrimitive=false;
            this->bIsPackage=false;
            this->componentType=NULL;
            this->enumConstants=new vector<JEnum*>;
            this->fields=new map<JString,JField*>;
            this->fieldsList=new vector<JField*>;
            this->declaredFields=new map<JString,JField*>;
            this->declaredFieldsList=new vector<JField*>;
            this->methods=new map<JString,JMethod*>;
            this->methodsList=new vector<JMethod*>;
            this->declaredMethods=new map<JString,JMethod*>;
            this->declaredMethodsList=new vector<JMethod*>;
            this->interfaces=new vector<JClass*>;
            this->publicClasses=new vector<JClass*>();
            this->inheritedPublicClasses=new vector<JClass*>();
            this->declaredClasses=new vector<JClass*>();
            this->modifier=0;
        }

        JString JClass::getCanonicalName(){
            return canonicalName;
        }

        JString JClass::getName(){
            return name;
        }

        JString JClass::getSimpleName(){
            return simpleName;
        }

        JClassLoader* JClass::getClassLoader(){
            return classLoader;
        }

        JClass* JClass::getComponentType(){
            return componentType;
        }

        vector<JEnum*>* JClass::getEnumConstants(){
            initEnumConstants();
            return enumConstants;
        }

        void JClass::initEnumConstants(){
            if (enumConstants->size()==0){
                fillEnumConstants();
            }
        }

        void JClass::fillEnumConstants(){
        }

        JEnum* JClass::valueOf(JString value){
            initEnumConstants();
            for (unsigned int i=0;i<enumConstants->size();i++){
                JEnum* e=enumConstants->at(i);
                if ((*e->getName())==value){
                    return e;
                }
            }
            throw new JIllegalArgumentException("No enum constant "+value+" in enum "+getName());
        }

        JField* JClass::getField(JString name){
            initFields();
            JField* field=getFromMap(fields,name);
            if (field==NULL){
                throw JNoSuchFieldException("field "+name+" not delared in "+getName());
            }
            return field;
        }

        jbool JClass::hasDeclaredField(JString name){
            JField* field=getFromMap(declaredFields,name);
            return (field!=NULL);
        }

        JField* JClass::getDeclaredField(JString name){
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
                        fields->insert(pair<JString,JField*>(f->getName(),f));
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
            initInterfaces();
            return interfaces;
        }

        void JClass::initInterfaces(){
            if (interfaces->size()==0){
                fillInterfaces();
            }
        }

        void JClass::fillInterfaces(){
        }

        bool JClass::hasMethod(JString name, vector<JClass*>*){
            initMethods();
            JMethod* method=getFromMap(methods,name);
            if (method==NULL){
                return false;
            }
            return true;
        }

        bool JClass::hasDeclaredMethod(JString name, vector<JClass*>*){
            initDeclaredMethods();
            JMethod* method=getFromMap(declaredMethods,name);
            if (method==NULL){
                return false;
            }
            return true;
        }

        JMethod* JClass::getMethod(JString name, vector<JClass*>*){
            initMethods();
            JMethod* method=getFromMap(methods,name);
            if (method==NULL){
                throw JNoSuchMethodException("method "+name+" not declared in "+getName());//we should check using signature ...
            }
            return method;
        }

        JMethod* JClass::getDeclaredMethod(JString name, vector<JClass*>*){
            initDeclaredMethods();
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
                    current->initDeclaredMethods();
                    for (unsigned int i=0;i<current->declaredMethodsList->size();i++){
                        JMethod* m=current->declaredMethodsList->at(i);//TODO add it or check before ...
                        methodsList->push_back(m);
                        methods->insert(pair<JString,JMethod*>(m->getName(),m));
                    }
                    vector<JClass*>* interf=current->getInterfaces();
                    for (unsigned int i=0;i<interf->size();i++){
                        JClass* c=interf->at(i);
                        c->initDeclaredMethods();
                        for (unsigned int j=0;j<c->declaredMethodsList->size();j++){
                            JMethod* m=c->declaredMethodsList->at(j);
                            methodsList->push_back(m);
                            methods->insert(pair<JString,JMethod*>(m->getName(),m));
                        }
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
            initDeclaredMethods();
            return declaredMethodsList;
        }

        void JClass::initDeclaredMethods(){
            if (declaredMethods->size()==0){
                fillDeclaredMethods();
            }
        }

        void JClass::fillDeclaredMethods(){
        }

        vector<JClass*>* JClass::getClasses(){
            initInheritedPublicClasses();
            return inheritedPublicClasses;
        }

        void JClass::addDeclaredClass(JClass* c){
            if (c->getDeclaringClass()!=this){
                throw new JIllegalArgumentException("Declaring class of "+c->getName()+" is not "+getName()+". It is "+c->getDeclaringClass()->getName());
            }
            declaredClasses->push_back(c);
        }

        void JClass::fillDeclaredClasses(){
        }

        vector<JClass*>* JClass::getDeclaredClasses(){
            if (declaredClasses->size()==0){
                fillDeclaredClasses();
            }
            return declaredClasses;
        }

        void JClass::initInheritedPublicClasses(){
            if (inheritedPublicClasses->size()==0){
                JClass* current=this;
                while (current!=NULL){
                    vector<JClass*>* members=current->getDeclaredClasses();
                    for (unsigned int i=0;members->size();i++){
                        JClass* c=members->at(i);
                        if (JModifier::isPublic(c->getModifiers())){
                            inheritedPublicClasses->push_back(c);
                        }
                    }
                    current=current->getSuperclass();
                }
            }
        }

        void JClass::addEnumConstant(JEnum* enumConstant){
            enumConstants->push_back(enumConstant);
        }

        void JClass::addField(JField* field){
            declaredFieldsList->push_back(field);
            declaredFields->insert(pair<JString,JField*>(field->getName(),field));
        }

        void JClass::addMethod(JMethod* method){
            declaredMethodsList->push_back(method);
            declaredMethods->insert(pair<JString,JMethod*>(method->getName(),method));
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
                     }else{
                         if (isAssignableFrom(interf)){
                             return true;
                         }
                     }
                }
                current=current->getSuperclass();//check also interfaces
            }
            return false;
        }

        bool JClass::isInstance(JObject* o){
            if (o==NULL){
                throw new JNullPointerException();
            }
            JClass* c=o->getClass();
            return isAssignableFrom(c);
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

        jint JClass::getModifiers(){
            return modifier;
        }

        JObject* JClass::newInstance(){
            throw new JInstantiationException("cannot instantiate object of class "+getName());
        }

        JClass* JClass::getDeclaringClass(){
            return NULL;
        }

        jlong JClass::getSerialVersionUID(){
            return serialVersionUID;
        }

        JString JClass::toString(){
            return JString((isInterface()?"interface ":(isPrimitive()?"":"class "))+getName());
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
