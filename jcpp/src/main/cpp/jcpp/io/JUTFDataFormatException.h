#ifndef JUTFDATAFORMATEXCEPTION_H
#define JUTFDATAFORMATEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JUTFDataFormatException : public JIOException{
        public:
            JUTFDataFormatException();
            JUTFDataFormatException(JString message);
            static JClass* getClazz();
            virtual ~JUTFDataFormatException();
        };
    }
}

#endif // JUTFDATAFORMATEXCEPTION_H
