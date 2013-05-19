#ifndef JERRORMANAGER_H
#define JERRORMANAGER_H

#include "JObject.h"
#include "JException.h"
#include "JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JErrorManager : public JObject  {
                protected:
                    jbool reported;

                public:
                    JErrorManager();
                    static JClass* getClazz();
                    static jint GENERIC_FAILURE;
                    static jint WRITE_FAILURE;
                    static jint FLUSH_FAILURE;
                    static jint CLOSE_FAILURE;
                    static jint OPEN_FAILURE;
                    static jint FORMAT_FAILURE;
                    virtual void error(JString m, JException* e, jint code);
                    virtual ~JErrorManager();
            };
        }
    }
}

#endif // JERRORMANAGER_H
