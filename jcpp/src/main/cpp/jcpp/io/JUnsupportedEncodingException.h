#ifndef JUNSUPPORTEDENCODINGEXCEPTION_H
#define JUNSUPPORTEDENCODINGEXCEPTION_H

#include "JIOException.h"

namespace jcpp{
    namespace io{
        class JUnsupportedEncodingException : public JIOException  {
            public:
                static JClass* getClazz();
                JUnsupportedEncodingException();
                virtual ~JUnsupportedEncodingException();
        };
    }
}

#endif // JUNSUPPORTEDENCODINGEXCEPTION_H
