#ifndef JOPTIONALDATAEXCEPTION_H
#define JOPTIONALDATAEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
#include "JPrimitiveInt.h"
#include "JPrimitiveBoolean.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JOptionalDataException : public JObjectStreamException{
        protected:
            JPrimitiveInt* length;
            JPrimitiveBoolean* eof;
            JOptionalDataException(JClass* _clazz);
            JPrimitiveInt* getPLength();
            void setPLength(JPrimitiveInt* l);
            JPrimitiveBoolean* getPEOF();
            void setPEOF(JPrimitiveBoolean* eof);
            friend class JOptionalDataExceptionClass;

        public:
            JOptionalDataException();
            JOptionalDataException(string message);
            static JClass* getClazz();
            jint getLength();
            void setLength(jint l);
            jbool getEOF();
            void setEOF(jbool eof);
            virtual ~JOptionalDataException();
        };
    }
}

#endif // JOPTIONALDATAEXCEPTION_H
