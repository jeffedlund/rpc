#ifndef JUTFDATAFORMATEXCEPTION_H
#define JUTFDATAFORMATEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
using namespace std;

class JUTFDataFormatException : public JIOException{
public:
    JUTFDataFormatException();
    JUTFDataFormatException(string message);

     static JClass* getClazz();
};

#endif // JUTFDATAFORMATEXCEPTION_H
