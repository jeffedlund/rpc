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
using namespace std;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JEnum;
        class JClassLoader;

        //TODO implement forName,
        class JClass : public JObject{
        private:
            void initFields();
            void initMethods();
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
            bool bIsArray;
            bool bIsProxy;
            bool bIsEnum;
            bool bIsInterface;
            bool bIsPrimitive;
            bool bIsPackage;
            jlong serialVersionUID;
            JClass(JClassLoader* classLoader);
            JClass();
            JClass(bool root);

            void addEnumConstant(JEnum* enumConstant);
            void addField(JField* field);
            void addMethod(JMethod* method);
            void addInterface(JClass* interface);

         public:

            static JClass* getClazz();
            string getSignature();
            string getCanonicalName();
            string getName();
            string getSimpleName();
            JClassLoader* getClassLoader();
            JClass* getComponentType();
            vector<JEnum*>* getEnumConstants();
            JEnum* valueOf(string value);
            JField* getField(string name);
            vector<JField*>* getFields();
            JField* getDeclaredField(string name);
            vector<JField*>* getDeclaredFields();
            vector<JClass*>* getInterfaces();
            bool hasMethod(string name, vector<JClass*>* parameterTypes);
            JMethod* getMethod(string name, vector<JClass*>* parameterTypes);
            vector<JMethod*>* getMethods();
            bool hasDeclaredMethod(string name, vector<JClass*>* parameterTypes);
            JMethod* getDeclaredMethod(string name, vector<JClass*>* parameterTypes);
            vector<JMethod*>* getDeclaredMethods();
            virtual JClass* getSuperclass()=0;
            bool isArray();
            bool isProxy();
            bool isEnum();
            bool isAssignableFrom(JClass* clazz);
            bool isInstance(JObject* object);
            bool isInterface();
            bool isPrimitive();
            bool isPackage();
            virtual JObject* newInstance()=0;
            jlong getSerialVersionUID();
            string toString();
            ~JClass();
        };
    }
}

#endif // JCLASS_H
