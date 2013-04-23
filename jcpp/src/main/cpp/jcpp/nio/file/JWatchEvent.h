#ifndef JWATCHEVENT_H
#define JWATCHEVENT_H

#include "JInterface.h"
#include "JObject.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JCPP_LIBRARY_EXPORT JWatchEvent : public JInterface  {
                public:
                    class JCPP_LIBRARY_EXPORT JKind : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual string getName()=0;
                        virtual JClass* type()=0;
                    };

                    class JCPP_LIBRARY_EXPORT JModifier : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual string getName()=0;
                    };

                    static JClass* getClazz();
                    virtual JKind * kind()=0;
                    virtual jint count()=0;
                    virtual JObject* context()=0;
                    virtual ~JWatchEvent();
            };
        }
    }
}

#endif // JWATCHEVENT_H
