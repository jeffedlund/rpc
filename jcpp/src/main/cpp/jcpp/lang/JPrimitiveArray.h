#ifndef JPRIMITIVEARRAY_H
#define JPRIMITIVEARRAY_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveArray : public JObject{
        private:
            vector<JObject*>* objects;
            jint len;
            void checkType(JObject* o);

        public:
            JPrimitiveArray(JClass* arrayClass,jint len=10);

            JPrimitiveArray(JClass* arrayClass,vector<JObject*>* objects);

            virtual bool equals(JObject* other);

            static JClass* getClazz(JClass* componentType);

            //TODO test cases for this method
            static JClass* loadClassBySignature(JClassLoader* classLoader,string name);

            jint size();

            void setSize(jint len);

            JObject* get(jint i);

            void set(jint i,JObject* value);

            vector<JObject*>* getObjects();

            virtual ~JPrimitiveArray();
        };
    }
}

#endif // JPRIMITIVEARRAY_H
