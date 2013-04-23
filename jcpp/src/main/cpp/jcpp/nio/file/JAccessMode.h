#ifndef JACCESSMODE_H
#define JACCESSMODE_H

#include "JEnum.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JAccessMode : public JEnum  {
                protected:
                    class JAccessModeClass : public JEnumClass{
                      public:
                        JAccessModeClass();
                        virtual JClass* getSuperclass();
                        virtual void fillEnumConstants();
                    };
                    JAccessMode(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JAccessMode* READ;
                    static JAccessMode* WRITE;
                    static JAccessMode* EXECUTE;
                    virtual ~JAccessMode();
            };
        }
    }
}

#endif // JACCESSMODE_H
