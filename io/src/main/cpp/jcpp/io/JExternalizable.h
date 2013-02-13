#ifndef JEXTERNALIZABLE_H
#define JEXTERNALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JObjectOutputStream.h"
#include "JObjectInputStream.h"

namespace jcpp{
    namespace io{
        //TODO have a test case scenario
        class JExternalizable:JObject{//TODO extends JInterface instead...
        protected:
            JExternalizable();
        public:

            static JClass* getClazz();

            virtual void writeExternal(JObjectOutputStream* out)=0;

            virtual void readExternal(JObjectInputStream* in)=0;
        };
    }
}

#endif // JEXTERNALIZABLE_H
