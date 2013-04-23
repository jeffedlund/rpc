#ifndef JFILEVISITOPTION_H
#define JFILEVISITOPTION_H

#include "JString.h"
#include "JEnum.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileVisitOption : public JEnum  {
                protected:
                    class JFileVisitOptionClass : public JEnumClass{
                    public:
                        JFileVisitOptionClass();
                        virtual void fillEnumConstants();
                    };
                    JFileVisitOption(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JFileVisitOption* FOLLOW_LINKS;
                    virtual ~JFileVisitOption();
            };
        }
    }
}

#endif // JFILEVISITOPTION_H
