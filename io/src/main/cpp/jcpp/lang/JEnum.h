#ifndef JENUM_H
#define JENUM_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveInt.h"
#include "JString.h"
#include "JInstantiationException.h"
#include "JCPP.h"
using namespace std;

//TODO write enum test case
namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JEnum: public JObject{

        protected:

            class JEnumClass : public JClass{
              public:
                JEnumClass(){
                    this->canonicalName="java.lang.Enum";
                    this->name="java.lang.Enum";
                    this->simpleName="Enum";
                    this->bIsEnum=true;
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                virtual JObject* newInstance(){
                    throw new JInstantiationException("cannot instantiate enum of class "+getName());
                }
            };

            JPrimitiveInt* ordinal;
            JString* name;
            JEnum(JEnumClass* _class,JString* name,JPrimitiveInt* ordinal);

        public:
            static JClass* getClazz();
            bool operator==(JObject &other);

            JString* getName();

            JPrimitiveInt* getOrdinal();

            string toString();

            virtual ~JEnum();
        };
    }
}

#endif // JENUM_H
