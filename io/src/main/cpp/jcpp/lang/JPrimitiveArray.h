#ifndef JPRIMITIVEARRAY_H
#define JPRIMITIVEARRAY_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveArray : public JObject{
        private:
            vector<JObject*>* objects;
            int len;

        public:
            JPrimitiveArray(JClass* arrayClass,int len=10);

            JPrimitiveArray(JClass* arrayClass,vector<JObject*>* objects);

            bool operator==(JObject &other);

            static JClass* getClazz(JClass* componentType);

            //TODO test cases for this method
            static JClass* loadClassBySignature(JClassLoader* classLoader,string name);

            int size();

            void setSize(int len);

            JObject* get(int i);

            void set(int i,JObject* value);

            vector<JObject*>* getObjects();

            virtual ~JPrimitiveArray();
        };
    }
}

#endif // JPRIMITIVEARRAY_H
