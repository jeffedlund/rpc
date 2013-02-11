#ifndef JOBJECTSTREAMFIELD_H
#define JOBJECTSTREAMFIELD_H

#include "JObject.h"
#include "JClass.h"
#include "JField.h"
#include <iostream>
#include <string.h>
#include "JString.h"
using namespace std;
using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        //TODO add getClazz
        class JObjectStreamField{
        private:
            string name;
            string signature;
            JClass* type;
            bool unshared;
            JField* field;
            qint32 offset;
            JString* typeString;

            void setTypeString();

        public:
            JObjectStreamField();
            JObjectStreamField(string name,JClass* type);
            JObjectStreamField(string name,JClass* type,bool unshared);
            JObjectStreamField(string name,string signature,bool unshared);
            JObjectStreamField(JField* field,bool unshared,bool showType);


            static bool comparator (JObjectStreamField* f1,JObjectStreamField* f2) {
                bool isPrim = f1->getType()->isPrimitive();
                if (isPrim != f2->getType()->isPrimitive()) {
                    return isPrim ? true : false;
                }
                return (f1->getName()<f2->getName());
            }

            string getName();
            JClass* getType();
            char getTypeCode();
            JString* getTypeString();
            qint32 getOffset();
            void setOffset(qint32 offset);
            bool isPrimitive();
            bool isUnshared();
            JField* getField();
            string getSignature();
            ~JObjectStreamField();
        };
    }
}

#endif // JOBJECTSTREAMFIELD_H
