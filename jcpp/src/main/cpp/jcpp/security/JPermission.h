#ifndef JPERMISSION_H
#define JPERMISSION_H

#include "JPermissionCollection.h"
#include "JSerializable.h"
#include "JObject.h"
#include "JGuard.h"
#include "JString.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JCPP_LIBRARY_EXPORT JPermission : public JObject  , public JGuard  , public JSerializable  {
            protected:
                JString* name;
                JPermission(JClass* _class,string name);
                JPermission(JClass* _class);
                friend class JPermissionClass;

            public:
                static JClass* getClazz();
                virtual void  checkGuard(JObject* object);
                virtual jbool implies(JPermission* permission)=0;
                virtual jbool equals(JObject* objet)=0;
                virtual jint hashCode()=0;
                virtual string getName();
                virtual string getActions()=0;
                virtual JPermissionCollection* newPermissionCollection();
                virtual string toString();
                virtual ~JPermission();
        };
    }
}

#endif // JPERMISSION_H
