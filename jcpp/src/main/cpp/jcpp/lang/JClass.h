#ifndef JCLASS_H
#define JCLASS_H

#include "JMethod.h"
#include "JField.h"
#include "JObject.h"
#include "JString.h"
#include <vector>
#include <map>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

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
            JString canonicalName;
            JString name;
            JString simpleName;
            JClassLoader* classLoader;
            JClass* componentType;
            vector<JEnum*>* enumConstants;
            map<JString,JField*>* fields;
            vector<JField*>* fieldsList;
            map<JString,JField*>* declaredFields;
            vector<JField*>* declaredFieldsList;
            map<JString,JMethod*>* methods;
            vector<JMethod*>* methodsList;
            map<JString,JMethod*>* declaredMethods;
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
            friend class JClassLoader;

         public:

            static JClass* getClazz();
            virtual JString getSignature();
            virtual JString getCanonicalName();
            virtual JString getName();
            virtual JString getSimpleName();
            virtual JClassLoader* getClassLoader();
            virtual JClass* getComponentType();
            virtual vector<JEnum*>* getEnumConstants();
            virtual JEnum* valueOf(JString value);
            virtual JField* getField(JString name);
            virtual vector<JField*>* getFields();
            virtual jbool hasDeclaredField(JString name);
            virtual JField* getDeclaredField(JString name);
            virtual vector<JField*>* getDeclaredFields();
            virtual vector<JClass*>* getInterfaces();
            virtual bool hasMethod(JString name, vector<JClass*>* parameterTypes);
            virtual JMethod* getMethod(JString name, vector<JClass*>* parameterTypes);
            virtual vector<JMethod*>* getMethods();
            virtual bool hasDeclaredMethod(JString name, vector<JClass*>* parameterTypes);
            virtual JMethod* getDeclaredMethod(JString name, vector<JClass*>* parameterTypes);
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
            virtual JString toString();
            virtual ~JClass();
        };
    }
}

#endif // JCLASS_H
