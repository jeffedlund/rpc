#ifndef JSTRINGWRITER_H
#define JSTRINGWRITER_H

#include "JAppendable.h"
#include "JString.h"
#include "JWriter.h"
#include "JCharSequence.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JStringWriter : public JWriter  {
            public:
                static JClass* getClazz();
                JStringWriter();
                virtual ~JStringWriter();
        };
    }
}

#endif // JSTRINGWRITER_H
