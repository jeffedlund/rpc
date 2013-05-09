#ifndef JPERMISSIONCOLLECTION_H
#define JPERMISSIONCOLLECTION_H

#include "JSerializable.h"
#include "JObject.h"
#include "JEnumeration.h"
#include "JString.h"
#include "JPrimitiveBoolean.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JPermission;
        class JCPP_LIBRARY_EXPORT JPermissionCollection : public JObject  , public JSerializable  {
            protected:
                JPrimitiveBoolean* readOnly;
                JPermissionCollection(JClass* _class);
                friend class JPermissionCollectionClass;

            public:
                static JClass* getClazz();
                virtual void add(JPermission* permission)=0;
                virtual jbool implies(JPermission* permission)=0;
                virtual JEnumeration* elements()=0;
                virtual void setReadOnly();
                virtual jbool isReadOnly();
                virtual JString toString();
                virtual ~JPermissionCollection();
        };
    }
}

#endif // JPERMISSIONCOLLECTION_H
