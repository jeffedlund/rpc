#ifndef JLOGGER_H
#define JLOGGER_H

#include "JObject.h"
#include "JHandler.h"
#include "JThrowable.h"
#include "JLogger.h"
#include "JLogRecord.h"
#include "JFilter.h"
#include "JString.h"
#include "JLevel.h"
#include "JArrayList.h"

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogManager;
            class JLogger : public JObject  {
                protected:
                    JLogManager* manager;
                    JString* name;
                    JArrayList* handlers;
                    JString* resourceBundleName;
                    jbool useParentHandlers;
                    JFilter* filter;
                    jbool anonymous;
                    JString* catalogName;
                    JLogger* parent;
                    JArrayList* kids;
                    JLevel* levelObject;
                    jint levelValue;
                    JLogger(JClass* _class,JString name);
                    JLogger(JString name);
                    static JObject* treeLock;
                    void setLogManager(JLogManager* logManager);
                    void doLog(JLogRecord* lr);
                    void doSetParent(JLogger* newParent);
                    void updateEffectiveLevel();
                    friend class JLoggerClass;
                    friend class JLogManager;

                public:
                    static JClass* getClazz();
                    static JString GLOBAL_LOGGER_NAME;
                    static JLogger* getGlobal();
                    static JLogger* global;
                    static JLogger* getLogger(JString name);
                    static JLogger* getAnonymousLogger();
                    virtual void setFilter(JFilter* f);
                    virtual JFilter* getFilter();
                    virtual void log(JLogRecord* record);
                    virtual void log(JLevel* level,JString m);
                    virtual void log(JLevel* level, JString m, JObject* param);
                    virtual void log(JLevel* level, JString m, JPrimitiveArray* param);
                    virtual void log(JLevel* level, JString m, JThrowable* thrown);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg,JObject* param);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg,JPrimitiveArray* param);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg,JThrowable* thrown);
                    virtual void logp(JLevel* level, JString sourceClass, JString sourceMethod, JThrowable* thrown);
                    virtual void entering(JString sourceClass, JString sourceMethod);
                    virtual void entering(JString sourceClass, JString sourceMethod, JPrimitiveArray* param);
                    virtual void entering(JString sourceClass, JString sourceMethod, JObject* param);
                    virtual void exiting(JString sourceClass, JString sourceMethod);
                    virtual void exiting(JString sourceClass, JString sourceMethod, JObject* param);
                    virtual void throwing(JString sourceClass, JString sourceMethod, JThrowable* thrown);
                    virtual void severe(JString msg);
                    virtual void warning(JString msg);
                    virtual void info(JString msg);
                    virtual void config(JString msg);
                    virtual void fine(JString msg);
                    virtual void finer(JString msg);
                    virtual void finest(JString msg);
                    virtual void setLevel(JLevel* l);
                    virtual JLevel* getLevel();
                    virtual jbool isLoggable(JLevel* l);
                    virtual JString getName();
                    virtual void addHandler(JHandler* h);
                    virtual void removeHandler(JHandler* h);
                    virtual JPrimitiveArray* getHandlers();
                    virtual void setUseParentHandlers(jbool b);
                    virtual jbool getUseParentHandlers();
                    virtual JLogger * getParent();
                    virtual void setParent(JLogger* p);
                    virtual ~JLogger();
            };
        }
    }
}

#endif // JLOGGER_H
