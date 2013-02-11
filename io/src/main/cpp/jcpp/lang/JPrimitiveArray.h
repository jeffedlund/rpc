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

            bool operator==(JPrimitiveArray &other);

            static JClass* getClazz(JClass* componentType);

            static JClass* getClass(JClassLoader* classLoader,string name);

            int size();

            void setSize(int len);

            JObject* get(int i);

            void set(int i,JObject* value);

            ~JPrimitiveArray();
        };
    }
}

#endif // JPRIMITIVEARRAY_H
