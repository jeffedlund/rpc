#ifndef JOBJECTSTREAMFIELD_H
#define JOBJECTSTREAMFIELD_H

#include "JObject.h"
#include "JClass.h"
#include "JField.h"
#include <iostream>
#include "JString.h"
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;
using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JObjectStreamField : public JObject, public JComparable{
        private:
            JString* name;
            JString* signature;
            JClass* type;
            jbool unshared;
            JField* field;
            jint offset;
            JString* typeString;
            void setTypeString();

        public:
            JObjectStreamField();
            JObjectStreamField(JString name,JClass* type);
            JObjectStreamField(JString name,JClass* type,jbool unshared);
            JObjectStreamField(JString name,JString signature,jbool unshared);
            JObjectStreamField(JField* field,jbool unshared,jbool showType);
            static JClass* getClazz();


            //TODO what to do for PTR ==/<
            static jbool comparator (JObjectStreamField* f1,JObjectStreamField* f2) {
                jbool isPrim = f1->getType()->isPrimitive();
                if (isPrim != f2->getType()->isPrimitive()) {
                    return isPrim ? true : false;
                }
                return (f1->getName()<f2->getName());
            }

            JString* getName();
            JClass* getType();
            jchar getTypeCode();
            JString* getTypeString();
            jint getOffset();
            void setOffset(jint offset);
            jbool isPrimitive();
            jbool isUnshared();
            JField* getField();
            JString* getSignature();
            virtual jint compareTo(JObject* o);
            virtual ~JObjectStreamField();
        };
    }
}

#endif // JOBJECTSTREAMFIELD_H
