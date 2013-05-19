#ifndef JLEVEL_H
#define JLEVEL_H

#include "JObject.h"
#include "JString.h"
#include "JSerializable.h"
#include "JLevel.h"
#include "JPrimitiveInt.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLevel : public JObject  , public JSerializable  {
                protected:
                    JString* name;
                    JPrimitiveInt* value;
                    JString* resourceBundleName;
                    friend class JLevelClass;
                    JLevel();
                    JLevel(JString name, jint value);

                public:
                    static JClass* getClazz();
                    static JLevel* parse(JString name);
                    static JLevel* OFF;
                    static JLevel* SEVERE;
                    static JLevel* WARNING;
                    static JLevel* INFO;
                    static JLevel* CONFIG;
                    static JLevel* FINE;
                    static JLevel* FINER;
                    static JLevel* FINEST;
                    static JLevel* ALL;
                    virtual JString getName();
                    virtual JString toString();
                    virtual jint intValue();
                    virtual jbool equals(JObject* o);
                    virtual jint hashCode();
                    virtual ~JLevel();
            };
        }
    }
}

#endif // JLEVEL_H
