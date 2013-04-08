#ifndef JEXTERNALIZABLE_H
#define JEXTERNALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JObjectOutput.h"
#include "JObjectInput.h"
#include "JSerializable.h"
#include "JCPP.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JExternalizable : public JSerializable{
        protected:
        public:

            static JClass* getClazz();

            virtual void writeExternal(JObjectOutput* out)=0;

            virtual void readExternal(JObjectInput* in)=0;

            virtual ~JExternalizable();
        };
    }
}

#endif // JEXTERNALIZABLE_H
