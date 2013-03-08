#ifndef JFIELD_H
#define JFIELD_H

#include "JObject.h"
#include "JAccessibleObject.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JField: public JAccessibleObject{
            public:
                typedef JObject* (*getter)(JObject* objet);
                typedef void (*setter)(JObject* object,JObject* value);

            private:
                string name;
                JClass* type;
                getter g;
                setter s;

            public:
                JField(string name,JClass* type);
                JField(string name,JClass* type,getter g,setter s);

                static JClass* getClazz();

                string getName();

                JClass* getType();

                virtual JObject* get(JObject* object);

                virtual void set(JObject* object, JObject* value);

                string toString();

                virtual ~JField();
            };
        }
    }
}
#endif // JFIELD_H