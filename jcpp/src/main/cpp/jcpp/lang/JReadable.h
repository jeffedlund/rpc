#ifndef JREADABLE_H
#define JREADABLE_H

#include "JInterface.h"

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JReadable : public JInterface  {
            public:
                static JClass* getClazz();
                //TODO virtual jint read(JCharBuffer* charBuffer);
                virtual ~JReadable();
        };
    }
}

#endif // JREADABLE_H
