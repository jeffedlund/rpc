#ifndef JCHARCONVERSIONEXCEPTION_H
#define JCHARCONVERSIONEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JCharConversionException : public JIOException  {
            public:
                static JClass* getClazz();
                JCharConversionException();
                virtual ~JCharConversionException();
        };
    }
}

#endif // JCHARCONVERSIONEXCEPTION_H

