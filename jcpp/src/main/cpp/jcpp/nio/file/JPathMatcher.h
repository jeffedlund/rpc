#ifndef JPATHMATCHER_H
#define JPATHMATCHER_H

#include "JInterface.h"
#include "JPath.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JPathMatcher : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual jbool matches(JPath* path)=0;
                    virtual ~JPathMatcher();
            };
        }
    }
}

#endif // JPATHMATCHER_H
