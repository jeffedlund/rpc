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

//TODO implement JClass::forName,, getPackage, getenclosingMethod,getEnclosingConstructor,
//getDeclaringClass,isAnonymousClass,isLocalClass,isMemberClass,getClasses, getDeclaredClasses,
//getResourceAsStream, getResource,getPrimitiveClass, cast,annotations,
namespace jcpp{
    namespace lang{
        class JEnum;
        class JClassLoader;
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
            jbool bIsArray;
            jbool bIsProxy;
            jbool bIsEnum;
            jbool bIsInterface;
            jbool bIsPrimitive;
            jbool bIsPackage;
            jlong serialVersionUID;
            jint modifier;
            JClass(JClassLoader* classLoader);
            JClass();
            JClass(jbool root);

            void addEnumConstant(JEnum* enumConstant);
            void addField(JField* field);
            void addMethod(JMethod* method);
            void addInterface(JClass* inter);
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
            virtual jbool hasMethod(JString name, vector<JClass*>* parameterTypes);
            virtual JMethod* getMethod(JString name, vector<JClass*>* parameterTypes);
            virtual vector<JMethod*>* getMethods();
            virtual jbool hasDeclaredMethod(JString name, vector<JClass*>* parameterTypes);
            virtual JMethod* getDeclaredMethod(JString name, vector<JClass*>* parameterTypes);
            virtual vector<JMethod*>* getDeclaredMethods();
            virtual vector<JClass*>* getClasses();
            virtual vector<JClass*>* getDeclaredClasses();
            virtual JClass* getSuperclass()=0;
            virtual jbool isArray();
            virtual jbool isProxy();
            virtual jbool isEnum();
            virtual jbool isAssignableFrom(JClass* clazz);
            virtual jbool isInstance(JObject* o);
            virtual jbool isInterface();
            virtual jbool isPrimitive();
            virtual jbool isPackage();
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
