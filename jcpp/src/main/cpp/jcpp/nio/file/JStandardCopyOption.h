#ifndef JSTANDARDCOPYOPTION_H
#define JSTANDARDCOPYOPTION_H

#include "JEnum.h"
#include "JString.h"
#include "JCopyOption.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JStandardCopyOption : public JEnum  , public JCopyOption  {
                protected:
                    class JStandardCopyOptionClass : public JEnumClass{
                    public:
                        JStandardCopyOptionClass();
                        virtual void fillEnumConstants();
                    };
                    JStandardCopyOption(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JStandardCopyOption* REPLACE_EXISTING;
                    static JStandardCopyOption* COPY_ATTRIBUTES;
                    static JStandardCopyOption* ATOMIC_MOVE;
                    virtual ~JStandardCopyOption();
            };
        }
    }
}

#endif // JSTANDARDCOPYOPTION_H
