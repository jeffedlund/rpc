#ifndef JCHARCONVERSIONEXCEPTION_H
#define JCHARCONVERSIONEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JCharConversionException : public JIOException  {
            public:
                static JClass* getClazz();
                JCharConversionException();
                virtual ~JCharConversionException();
        };
    }
}

#endif // JCHARCONVERSIONEXCEPTION_H

