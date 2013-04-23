#ifndef JOPENOPTION_H
#define JOPENOPTION_H

#include "JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JCPP_LIBRARY_EXPORT JOpenOption : public JInterface  {
                public:
                    static JClass* getClazz();
                    virtual ~JOpenOption();

            };
        }
    }
}

#endif // JOPENOPTION_H
