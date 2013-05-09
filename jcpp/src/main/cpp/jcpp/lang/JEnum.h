#ifndef JENUM_H
#define JENUM_H

#include "JObject.h"
#include "JClass.h"
#include "JPrimitiveInt.h"
#include "JString.h"
#include "JInstantiationException.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

//TODO implement valueOf
namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JEnum: public JObject, public JComparable, public JSerializable{
        protected:
            class JEnumClass : public JClass{
              public:
                JEnumClass(){
                    this->canonicalName="java.lang.Enum";
                    this->name="java.lang.Enum";
                    this->simpleName="Enum";
                    this->bIsEnum=true;
                    addInterface(JComparable::getClazz());
                    addInterface(JSerializable::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
            };

            JPrimitiveInt* ordinal;
            JString* name;
            JEnum(JEnumClass* _class,JString* name,JPrimitiveInt* ordinal);

        public:
            static JClass* getClazz();
            JString* getName();
            JPrimitiveInt* getOrdinal();
            virtual jint compareTo(JObject* o);
            virtual bool equals(JObject* other);
            virtual jint hashCode();
            virtual JString toString();
            virtual ~JEnum();
        };
    }
}

#endif // JENUM_H
