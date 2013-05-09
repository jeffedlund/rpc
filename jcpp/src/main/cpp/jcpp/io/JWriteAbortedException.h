#ifndef JWRITEABORTEDEXCEPTION_H
#define JWRITEABORTEDEXCEPTION_H

#include "JString.h"
#include "JThrowable.h"
#include "JException.h"
#include "JObjectStreamException.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JWriteAbortedException : public JObjectStreamException  {
            protected:
                JException* detail;

            public:
                JWriteAbortedException();
                JWriteAbortedException(JString message,JException* ex);
                static JClass* getClazz();
                virtual JThrowable * getCause();
                JException* getDetail();
                void setDetail(JException* e);
                virtual ~JWriteAbortedException();
        };
    }
}

#endif // JWRITEABORTEDEXCEPTION_H
