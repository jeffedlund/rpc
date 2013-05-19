#ifndef JLOGRECORD_H
#define JLOGRECORD_H

#include "JThrowable.h"
#include "JLevel.h"
#include "JString.h"
#include "JObject.h"
#include "JSerializable.h"
#include "JPrimitiveLong.h"
#include "JObjectOutputStream.h"
#include "JObjectInputStream.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogRecord : public JObject  , public JSerializable  {
                protected:
                    JLevel* level;
                    JPrimitiveLong* sequenceNumber;
                    JString* sourceClassName;
                    JString* sourceMethodName;
                    JString* message;
                    JPrimitiveInt* threadID;
                    JPrimitiveLong* millis;
                    JThrowable* thrown;
                    JString* loggerName;
                    JString* resourceBundleName;
                    JPrimitiveArray* parameters;
                    virtual void writeObject(JObjectOutputStream* out);
                    virtual void readObject(JObjectInputStream* in);
                    friend class JLogRecordClass;

                public:
                    static JClass* getClazz();
                    JLogRecord();
                    JLogRecord(JLevel* level,JString message);
                    virtual JString* getLoggerName();
                    virtual void setLoggerName(JString name);
                    virtual JLevel* getLevel();
                    virtual void setLevel(JLevel* level);
                    virtual jlong getSequenceNumber();
                    virtual void setSequenceNumber(jlong nb);
                    virtual JString* getSourceClassName();
                    virtual void setSourceClassName(JString name);
                    virtual JString* getSourceMethodName();
                    virtual void setSourceMethodName(JString name);
                    virtual JString* getMessage();
                    virtual void setMessage(JString m);
                    virtual JPrimitiveArray* getParameters();
                    virtual void setParameters(JPrimitiveArray* p);
                    virtual jint getThreadID();
                    virtual void setThreadID(jint id);
                    virtual jlong getMillis();
                    virtual void setMillis(jlong m);
                    virtual JThrowable* getThrown();
                    virtual void setThrown(JThrowable* th);
                    virtual ~JLogRecord();
            };
        }
    }
}

#endif // JLOGRECORD_H
