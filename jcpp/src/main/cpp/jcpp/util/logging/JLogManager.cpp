#include "JLogManager.h"
#include "JClass.h"
#include "JLogger.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogManagerClass : public JClass{
                public:
                    JLogManagerClass(){
                        this->canonicalName="java.util.logging.LogManager";
                        this->name="java.util.logging.LogManager";
                        this->simpleName="LogManager";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JLogManager::getClazz(){
                if (clazz==NULL){
                    clazz=new JLogManagerClass();
                }
                return clazz;
            }

            JLogManager::JLogManager():JObject(getClazz()){
                namedLoggers=new JHashtable();
                root=new JLogNode(NULL);
                rootLogger=NULL;
            }

            JLogManager* JLogManager::manager = NULL;
            JLogManager* JLogManager::getLogManager(){
                if (manager==NULL){
                    manager=new JLogManager();
                    manager->rootLogger = new JRootLogger(manager);
                    manager->addLogger(manager->rootLogger);
                    JLogger::getGlobal()->setLogManager(manager);
                    manager->addLogger(JLogger::getGlobal());
                }
                return manager;
            }

            JLogger* JLogManager::demandLogger(JString name){
                JLogger* result = getLogger(name);
                if (result == NULL) {
                    JLogger* newLogger = new JLogger(name);
                    do {
                        if (addLogger(newLogger)) {
                            return newLogger;
                        }
                        result = getLogger(name);
                    } while (result == NULL);
                }
                return result;
            }

            void JLogManager::processParentHandlers(JLogger* logger, JString name){
                jint ix = 1;
                for (;;) {
                    jint ix2 = name.indexOf(".", ix);
                    if (ix2 < 0) {
                        break;
                    }
                    JString pname = name.substring(0,ix2);
                    //if (getProperty(pname+".level")    != NULL ||getProperty(pname+".handlers") != NULL) {
                    //    demandLogger(pname);
                   // }//TODO put Properties
                    ix = ix2+1;
                }
            }

            jbool JLogManager::addLogger(JLogger* logger){
                JString name = logger->getName();

                JLogger* ref = (JLogger*)namedLoggers->get(&name);
                if (ref != NULL) {
                    return false;
                }

                JLevel* level = NULL;//TODO getLevelProperty(name+".level", null);
                if (level != NULL) {
                    doSetLevel(logger, level);
                }

                processParentHandlers(logger, name);

                JLogNode* node = findNode(name);
                node->loggerRef = ref;
                JLogger* parent = NULL;
                JLogNode* nodep = node->parent;
                while (nodep != NULL) {
                    JLogger* nodeRef = nodep->loggerRef;
                    if (nodeRef != NULL) {
                        parent = nodeRef;
                        break;
                    }
                    nodep = nodep->parent;
                }

                if (parent != NULL) {
                    doSetParent(logger, parent);
                }
                node->walkAndSetParent(logger);

                namedLoggers->put(new JString(name), logger);
                return true;
            }

            void JLogManager::doSetLevel(JLogger* logger, JLevel* level) {
                logger->setLevel(level);
            }

            void JLogManager::doSetParent(JLogger* logger, JLogger* parent) {
                logger->setParent(parent);
            }

            JLogManager::JLogNode* JLogManager::findNode(JString name) {
                if (name.equals("")) {
                    return root;
                }
                JLogNode* node = root;
                while (name.length() > 0) {
                    jint ix = name.indexOf(".");
                    JString head;
                    if (ix > 0) {
                        head = name.substring(0,ix);
                        name = name.substring(ix+1);
                    } else {
                        head = name;
                        name = "";
                    }
                    if (node->children == NULL) {
                        node->children = new JHashMap();
                    }
                    JLogNode* child = (JLogNode*)node->children->get(&head);
                    if (child == NULL) {
                        child = new JLogNode(node);
                        node->children->put(new JString(head), child);
                    }
                    node = child;
                }
                return node;
            }

            JLogger* JLogManager::getLogger(JString name) {
                JLogger* ref = (JLogger*)namedLoggers->get(&name);
                return ref;
            }

            JEnumeration* JLogManager::getLoggerNames() {
                return namedLoggers->keys();
            }

            void JLogManager::readConfiguration(){
                //TODO
            }

            void JLogManager::reset(){
                JEnumeration* enum_ = getLoggerNames();
                while (enum_->hasMoreElements()) {
                    JString* name = (JString*)enum_->nextElement();
                    resetLogger(name);
                }
                delete enum_;
            }

            void JLogManager::resetLogger(JString name) {
                JLogger* logger = getLogger(name);
                if (logger == NULL) {
                    return;
                }
                JPrimitiveArray* targets = logger->getHandlers();
                for (int i = 0; i < targets->size(); i++) {
                    JHandler* h = (JHandler*)targets->get(i);
                    logger->removeHandler(h);
                    try {
                        h->close();
                    } catch (JException* ex) {
                        delete ex;
                    }
                }
                if (name.equals("")) {
                    logger->setLevel(JLevel::INFO);
                } else {
                    logger->setLevel(NULL);
                }
            }

            void JLogManager::readConfiguration(JInputStream* in){
            }

            vector<JString>* JLogManager::parseClassNames(JString propertyName){
                return NULL;
            }

            class JLogNodeClass : public JClass{
                public:
                    JLogNodeClass(){
                        this->canonicalName="java.util.logging.LogManager$LogNode";
                        this->name="java.util.logging.LogManager$LogNode";
                        this->simpleName="LogManager$LogNode";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }//TODO fill declaring class
            };

            static JClass* logNodeClazz;
            JClass* JLogManager::JLogNode::getClazz(){
                if (logNodeClazz==NULL){
                    logNodeClazz=new JLogNodeClass();
                }
                return logNodeClazz;
            }

            JLogManager::JLogNode::JLogNode(JLogNode* parent):JObject(JLogManager::JLogNode::getClazz()){
                this->parent=parent;
                this->children=NULL;
                this->loggerRef=NULL;
            }

            void JLogManager::JLogNode::walkAndSetParent(JLogger* parent){
                if (children == NULL) {
                    return;
                }
                JIterator* values = children->values()->iterator();
                while (values->hasNext()) {
                    JLogNode* node = (JLogNode*)values->next();
                    JLogger* ref = node->loggerRef;
                    if (ref == NULL) {
                        node->walkAndSetParent(parent);
                    } else {
                        doSetParent(ref, parent);
                    }
                }
                delete values;
            }

            class JRootLoggerClass : public JClass{
                public:
                    JRootLoggerClass(){
                        this->canonicalName="java.util.logging.LogManager$RootLogger";
                        this->name="java.util.logging.LogManager$RootLogger";
                        this->simpleName="LogManager$RootLogger";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }//TODO fill declaring class
            };

            static JClass* rootLoggerClazz;
            JClass* JLogManager::JRootLogger::getClazz(){
                if (rootLoggerClazz==NULL){
                    rootLoggerClazz=new JRootLoggerClass();
                }
                return rootLoggerClazz;
            }

            JLogManager::JRootLogger::JRootLogger(JLogManager* logManager):JLogger(JLogManager::JRootLogger::getClazz(),""){
                this->logManager=logManager;
                setLevel(JLevel::INFO);
            }

            void JLogManager::JRootLogger::log(JLogRecord* record){
                logManager->initializeGlobalHandlers();
                JLogger::log(record);
            }

            void JLogManager::JRootLogger::addHandler(JHandler* h){
                logManager->initializeGlobalHandlers();
                JLogger::addHandler(h);
            }

            void JLogManager::JRootLogger::removeHandler(JHandler* h){
                logManager->initializeGlobalHandlers();
                JLogger::removeHandler(h);
            }

            JPrimitiveArray* JLogManager::JRootLogger::getHandlers(){
                logManager->initializeGlobalHandlers();
                return JLogger::getHandlers();
            }

            void JLogManager::setLevelsOnExistingLoggers(){
            }

            void JLogManager::initializeGlobalHandlers(){
            }

            JLogManager::~JLogManager(){
                delete this->namedLoggers;
                delete this->root;
                delete this->rootLogger;
            }
        }
    }
}

