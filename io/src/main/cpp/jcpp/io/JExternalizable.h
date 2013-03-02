#ifndef JEXTERNALIZABLE_H
#define JEXTERNALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JObjectOutputStream.h"
#include "JObjectInputStream.h"

namespace jcpp{
    namespace io{
        //TODO have a test case scenario
        class JExternalizable:JInterface{
        protected:
        public:

            static JClass* getClazz();

            virtual void writeExternal(JObjectOutputStream* out)=0;

            virtual void readExternal(JObjectInputStream* in)=0;

            virtual ~JExternalizable();
        };
    }
}

#endif // JEXTERNALIZABLE_H
