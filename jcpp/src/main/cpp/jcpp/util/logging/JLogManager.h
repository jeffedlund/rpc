#ifndef JLOGMANAGER_H
#define JLOGMANAGER_H

#include "JLogManager.h"
#include "JInputStream.h"
#include "JEnumeration.h"
#include "JObject.h"
#include "JString.h"
#include "JHashtable.h"
#include "JHashMap.h"
#include "JLogger.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogManager : public JObject  {
                protected:
                    class JLogNode : public JObject{
                        protected:
                            JHashMap* children;
                            JLogger* loggerRef;
                            JLogNode* parent;
                            friend class JLogManager;

                        public:
                            static JClass* getClazz();
                            JLogNode(JLogNode* parent);
                            void walkAndSetParent(JLogger* parent);

                    };

                    class JRootLogger : public JLogger{
                    protected:
                        JLogManager* logManager;

                    public:
                        JRootLogger(JLogManager* logManager);
                        static JClass* getClazz();
                        virtual void log(JLogRecord* record);
                        virtual void addHandler(JHandler* h);
                        virtual void removeHandler(JHandler* h);
                        virtual JPrimitiveArray* getHandlers();
                    };

                    static JLogManager* manager;
                    JHashtable* namedLoggers;
                    JLogNode* root;
                    JLogger* rootLogger;
                    JLogManager();
                    JLogger* demandLogger(JString name);
                    void processParentHandlers(JLogger* logger, JString name);
                    static void doSetLevel(JLogger* logger, JLevel* level);
                    static void doSetParent(JLogger* logger, JLogger* parent);
                    JLogNode* findNode(JString name);
                    void resetLogger(JString name);
                    vector<JString>* parseClassNames(JString propertyName);
                    void initializeGlobalHandlers();
                    void setLevelsOnExistingLoggers();
                    friend class JLogManagerClass;
                    friend class JLogger;

                public:
                    static JClass* getClazz();
                    static JLogManager* getLogManager();
                    virtual jbool addLogger(JLogger* logger);
                    virtual JLogger* getLogger(JString name);
                    virtual JEnumeration* getLoggerNames();
                    virtual void readConfiguration();
                    virtual void reset();
                    virtual void readConfiguration(JInputStream* in);
                    virtual ~JLogManager();
            };
        }
    }
}

#endif // JLOGMANAGER_H
