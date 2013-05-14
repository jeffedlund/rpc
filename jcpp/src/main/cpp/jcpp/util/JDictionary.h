#ifndef JDICTIONARY_H
#define JDICTIONARY_H

#include "JObject.h"
#include "JIterable.h"
#include "JPrimitiveArray.h"
#include "JCPP.h"
#include "JEnumeration.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JDictionary : public JObject{
        protected:
            JDictionary(JClass* _class);

        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual jbool isEmpty()=0;
            virtual JEnumeration* keys()=0;
            virtual JEnumeration* elements()=0;
            virtual JObject* get(JObject* key)=0;
            virtual JObject* put(JObject* key,JObject* value)=0;
            virtual JObject* remove(JObject* key)=0;
            virtual ~JDictionary();
        };
    }
}

#endif // JDICTIONARY_H
