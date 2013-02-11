#ifndef JUTFDATAFORMATEXCEPTION_H
#define JUTFDATAFORMATEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JUTFDataFormatException : public JIOException{
        public:
            JUTFDataFormatException();
            JUTFDataFormatException(string message);

             static JClass* getClazz();
        };
    }
}

#endif // JUTFDATAFORMATEXCEPTION_H
