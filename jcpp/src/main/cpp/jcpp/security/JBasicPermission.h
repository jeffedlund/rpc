#ifndef JBASICPERMISSION_H
#define JBASICPERMISSION_H

#include "JPermission.h"
#include "JObject.h"
#include "JSerializable.h"
#include "JPermissionCollection.h"
#include "JString.h"
#include "JObjectInputStream.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JCPP_LIBRARY_EXPORT JBasicPermission : public JPermission {
            protected:
                jbool wildcard;
                string path;
                jbool exitVM;
                JBasicPermission(JClass* _class,string name);
                JBasicPermission(JClass* _class);
                void init(string name);
                string getCanonicalName();
                void readObject(JObjectInputStream* in);
                friend class JBasicPermissionClass;

            public:
                static JClass* getClazz();
                JBasicPermission(string name);
                JBasicPermission();
                virtual jbool implies(JPermission* permission);
                virtual jbool equals(JObject* object);
                virtual jint hashCode();
                virtual string getActions();
                virtual JPermissionCollection* newPermissionCollection();
                virtual ~JBasicPermission();
        };
    }
}

#endif // JBASICPERMISSION_H
