#ifndef JFILEVISITRESULT_H
#define JFILEVISITRESULT_H

#include "JString.h"
#include "JEnum.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileVisitResult : public JEnum  {
                protected:
                    class JFileVisitResultClass : public JEnumClass{
                    public:
                        JFileVisitResultClass();
                        virtual void fillEnumConstants();
                    };
                    JFileVisitResult(JString* name, JPrimitiveInt* ordinal);

                public:
                    static JClass* getClazz();
                    static JFileVisitResult * CONTINUE;
                    static JFileVisitResult * TERMINATE;
                    static JFileVisitResult * SKIP_SUBTREE;
                    static JFileVisitResult * SKIP_SIBLINGS;
                    virtual ~JFileVisitResult();
            };
        }
    }
}

#endif // JFILEVISITRESULT_H
