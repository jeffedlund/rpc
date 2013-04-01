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
            void setSize(jint len);

        public:
            JPrimitiveArray(JClass* arrayClass,jint len=10);
            JPrimitiveArray(JClass* arrayClass,vector<JObject*>* objects);
            static JClass* getClazz(JClass* componentType);
            jint size();
            JObject* get(jint i);
            vector<JObject*>* getObjects();
            void set(jint i,JObject* value);
            virtual bool equals(JObject* other);
            virtual ~JPrimitiveArray();
        };
    }
}

#endif // JPRIMITIVEARRAY_H
