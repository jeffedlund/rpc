#ifndef JLINKOPTION_H
#define JLINKOPTION_H

#include "JOpenOption.h"
#include "JEnum.h"
#include "JCopyOption.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JLinkOption : public JEnum  , public JOpenOption  , public JCopyOption  {
                protected:
                    class JLinkOptionClass : public JEnumClass{
                    public:
                        JLinkOptionClass();
                        virtual void fillEnumConstants();
                    };
                    JLinkOption(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JLinkOption* NOFOLLOW_LINKS;
                    virtual ~JLinkOption();
            };
        }
    }
}

#endif // JLINKOPTION_H
