#ifndef JCLASS_H
#define JCLASS_H

#include "JObject.h"
#include "JMethod.h"
#include "JField.h"
#include "JClassLoader.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "Object.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JEnum;
        class JClassLoader;

        //TODO implement JClass::forName,, getPackage, getenclosingMethod,getEnclosingConstructor,
        //getDeclaringClass,isAnonymousClass,isLocalClass,isMemberClass,getClasses, getDeclaredClasses,
        //getResourceAsStream, getResource,getPrimitiveClass, cast,annotations,
        class JCPP_LIBRARY_EXPORT JClass : public JObject{
        private:
            void init(JClassLoader* cl);
            void initFields();
            void initMethods();
            void initDeclaredMethods();
            void initInheritedPublicClasses();
            void initEnumConstants();
            void initInterfaces();
        protected:
            string canonicalName;
            string name;
            string simpleName;
            JClassLoader* classLoader;
            JClass* componentType;
            vector<JEnum*>* enumConstants;
            map<string,JField*>* fields;
            vector<JField*>* fieldsList;
            map<string,JField*>* declaredFields;
            vector<JField*>* declaredFieldsList;
            map<string,JMethod*>* methods;
            vector<JMethod*>* methodsList;
            map<string,JMethod*>* declaredMethods;
            vector<JMethod*>* declaredMethodsList;
            vector<JClass*>* interfaces;
            vector<JClass*>* publicClasses;
            vector<JClass*>* inheritedPublicClasses;
            vector<JClass*>* declaredClasses;
            bool bIsArray;
            bool bIsProxy;
            bool bIsEnum;
            bool bIsInterface;
            bool bIsPrimitive;
            bool bIsPackage;
            jlong serialVersionUID;
            jint modifier;
            JClass(JClassLoader* classLoader);
            JClass();
            JClass(bool root);

            void addEnumConstant(JEnum* enumConstant);
            void addField(JField* field);
            void addMethod(JMethod* method);
            void addInterface(JClass* interface);
            void addDeclaredClass(JClass* c);
            virtual void fillDeclaredMethods();
            virtual void fillDeclaredClasses();
            virtual void fillEnumConstants();
            virtual void fillInterfaces();

         public:

            static JClass* getClazz();
            virtual string getSignature();
            virtual string getCanonicalName();
            virtual string getName();
            virtual string getSimpleName();
            virtual JClassLoader* getClassLoader();
            virtual JClass* getComponentType();
            virtual vector<JEnum*>* getEnumConstants();
            virtual JEnum* valueOf(string value);
            virtual JField* getField(string name);
            virtual vector<JField*>* getFields();
            virtual jbool hasDeclaredField(string name);
            virtual JField* getDeclaredField(string name);
            virtual vector<JField*>* getDeclaredFields();
            virtual vector<JClass*>* getInterfaces();
            virtual bool hasMethod(string name, vector<JClass*>* parameterTypes);
            virtual JMethod* getMethod(string name, vector<JClass*>* parameterTypes);
            virtual vector<JMethod*>* getMethods();
            virtual bool hasDeclaredMethod(string name, vector<JClass*>* parameterTypes);
            virtual JMethod* getDeclaredMethod(string name, vector<JClass*>* parameterTypes);
            virtual vector<JMethod*>* getDeclaredMethods();
            virtual vector<JClass*>* getClasses();
            virtual vector<JClass*>* getDeclaredClasses();
            virtual JClass* getSuperclass()=0;
            virtual bool isArray();
            virtual bool isProxy();
            virtual bool isEnum();
            virtual bool isAssignableFrom(JClass* clazz);
            virtual bool isInstance(JObject* o);
            virtual bool isInterface();
            virtual bool isPrimitive();
            virtual bool isPackage();
            virtual jint getModifiers();
            virtual JObject* newInstance();
            virtual JClass* getDeclaringClass();
            virtual jlong getSerialVersionUID();
            virtual string toString();
            virtual ~JClass();
        };
    }
}

#endif // JCLASS_H
