#ifndef JSERIALIZABLEPERMISSION_H
#define JSERIALIZABLEPERMISSION_H

#include "JBasicPermission.h"

using namespace jcpp::security;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JSerializablePermission : public JBasicPermission  {
            protected:
                JString* actions;
                JSerializablePermission();
                friend class JSerializablePermissionClass;
            public:
                static JClass* getClazz();
                JSerializablePermission(JString name);
                JSerializablePermission(JString name,JString actions);
                virtual ~JSerializablePermission();
        };
    }
}

#endif // JSERIALIZABLEPERMISSION_H
