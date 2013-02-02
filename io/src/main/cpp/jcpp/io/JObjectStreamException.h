#ifndef JOBJECTSTREAMEXCEPTION_H
#define JOBJECTSTREAMEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
using namespace std;

class JObjectStreamException : public JIOException{
protected:
    JObjectStreamException(JClass* _clazz);
public:
    JObjectStreamException();
    JObjectStreamException(string message);

     static JClass* getClazz();
};

#endif // JOBJECTSTREAMEXCEPTION_H