#ifndef JSTANDARDOPENOPTION_H
#define JSTANDARDOPENOPTION_H

#include "JEnum.h"
#include "JString.h"
#include "JOpenOption.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JStandardOpenOption : public JEnum  , public JOpenOption  {
                protected:
                    class JStandardOpenOptionClass : public JEnumClass{
                    public:
                        JStandardOpenOptionClass();
                        virtual void fillEnumConstants();
                    };
                    JStandardOpenOption(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JStandardOpenOption* READ;
                    static JStandardOpenOption* WRITE;
                    static JStandardOpenOption* APPEND;
                    static JStandardOpenOption* TRUNCATE_EXISTING;
                    static JStandardOpenOption* CREATE;
                    static JStandardOpenOption* CREATE_NEW;
                    static JStandardOpenOption* DELETE_ON_CLOSE;
                    static JStandardOpenOption* SPARSE;
                    static JStandardOpenOption* SYNC;
                    static JStandardOpenOption* DSYNC;
                    virtual ~JStandardOpenOption();
            };
        }
    }
}

#endif // JSTANDARDOPENOPTION_H
