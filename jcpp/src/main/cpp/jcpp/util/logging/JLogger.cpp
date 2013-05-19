#include "JLogger.h"
#include "JClass.h"
#include "JLogManager.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JLoggerClass : public JClass{
                public:
                    JLoggerClass(){
                        this->canonicalName="java.util.logging.Logger";
                        this->name="java.util.logging.Logger";
                        this->simpleName="Logger";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JLogger::getClazz(){
                if (clazz==NULL){
                    clazz=new JLoggerClass();
                }
                return clazz;
            }

            JObject* JLogger::treeLock = new JObject();

            JLogger::JLogger(JClass* _class,JString name):JObject(_class){
                this->manager=JLogManager::getLogManager();
                this->name=new JString(name);
                handlers=new JArrayList();
                resourceBundleName=NULL;
                useParentHandlers=true;
                levelValue = JLevel::INFO->intValue();
                filter=NULL;
                catalogName=NULL;
                parent=NULL;
                kids=NULL;
                levelObject=NULL;
                anonymous=false;
            }

            JLogger::JLogger(JString name):JObject(getClazz()){
                this->manager=JLogManager::getLogManager();
                this->name=new JString(name);
                handlers=new JArrayList();
                resourceBundleName=NULL;
                useParentHandlers=true;
                levelValue = JLevel::INFO->intValue();
                filter=NULL;
                catalogName=NULL;
                parent=NULL;
                kids=NULL;
                levelObject=NULL;
                anonymous=false;
            }

            JString JLogger::GLOBAL_LOGGER_NAME = "global";

            JLogger* JLogger::global = NULL;

            JLogger* JLogger::getGlobal(){
                if (global==NULL){
                    global = new JLogger(GLOBAL_LOGGER_NAME);
                }
                return global;
            }

            void JLogger::setLogManager(JLogManager* logManager){
                this->manager=logManager;
            }

            JLogger* JLogger::getLogger(JString name){
                JLogManager* manager = JLogManager::getLogManager();
                return manager->demandLogger(name);
            }

            JLogger* JLogger::getAnonymousLogger(){
                JLogManager* manager = JLogManager::getLogManager();
                JLogger* result = new JLogger("");
                result->anonymous = true;
                JLogger* root = manager->getLogger("");
                result->doSetParent(root);
                return result;
            }

            void JLogger::setFilter(JFilter* f){
                this->filter=f;
            }

            JFilter* JLogger::getFilter(){
                return filter;
            }

            void JLogger::log(JLogRecord* record){
                if (record->getLevel()->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JFilter* theFilter = filter;
                if (theFilter != NULL && !theFilter->isLoggable(record)) {
                    return;
                }

                JLogger* logger = this;
                while (logger != NULL) {
                    JPrimitiveArray* a=logger->getHandlers();
                    if (a!=NULL){
                        for (int i=0;i<a->size();i++) {
                            JHandler* h=(JHandler*)a->get(i);
                            h->publish(record);
                        }
                    }

                    if (!logger->getUseParentHandlers()) {
                        break;
                    }

                    logger = logger->getParent();
                }
            }

            void JLogger::log(JLevel* level, JString msg) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                doLog(lr);
            }

            void JLogger::log(JLevel* level, JString msg, JObject* param1) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                JPrimitiveArray* a=new JPrimitiveArray(JObject::getClazz(),1);
                a->set(0,param1);
                lr->setParameters(a);
                doLog(lr);
            }

            void JLogger::log(JLevel* level, JString msg, JPrimitiveArray* params) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setParameters(params);
                doLog(lr);
            }

            void JLogger::log(JLevel* level, JString msg, JThrowable* thrown) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setThrown(thrown);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, "");
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg, JObject* param1) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                JPrimitiveArray* a=new JPrimitiveArray(JObject::getClazz(),1);
                a->set(0,param1);
                lr->setParameters(a);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg, JPrimitiveArray* a) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                lr->setParameters(a);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod, JString msg, JThrowable* thrown) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, msg);
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                lr->setThrown(thrown);
                doLog(lr);
            }

            void JLogger::logp(JLevel* level, JString sourceClass, JString sourceMethod, JThrowable* thrown) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(level, "");
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                lr->setThrown(thrown);
                doLog(lr);
            }

            void JLogger::doLog(JLogRecord* lr) {
                lr->setLoggerName(name);
                log(lr);
            }

            void JLogger::entering(JString sourceClass, JString sourceMethod) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                logp(JLevel::FINER, sourceClass, sourceMethod, "ENTRY");
            }

            void JLogger::entering(JString sourceClass, JString sourceMethod, JObject* param1) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                JPrimitiveArray* a=new JPrimitiveArray(JObject::getClazz(),1);
                a->set(0,param1);
                logp(JLevel::FINER, sourceClass, sourceMethod, "ENTRY {0}", a);
            }

            void JLogger::entering(JString sourceClass, JString sourceMethod, JPrimitiveArray* params) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                JString msg = "ENTRY";
                if (params == NULL) {
                   logp(JLevel::FINER, sourceClass, sourceMethod, msg);
                   return;
                }
                for (int i = 0; i < params->size(); i++) {
                    msg<< " {" << i << "}";
                }
                logp(JLevel::FINER, sourceClass, sourceMethod, msg, params);
            }

            void JLogger::exiting(JString sourceClass, JString sourceMethod) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                logp(JLevel::FINER, sourceClass, sourceMethod, "RETURN");
            }

            void JLogger::exiting(JString sourceClass, JString sourceMethod, JObject* result) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                JPrimitiveArray* a=new JPrimitiveArray(JObject::getClazz(),1);
                a->set(0,result);
                logp(JLevel::FINER, sourceClass, sourceMethod, "RETURN {0}", a);
            }

            void JLogger::throwing(JString sourceClass, JString sourceMethod, JThrowable* thrown) {
                if (JLevel::FINER->intValue() < levelValue || levelValue == JLevel::OFF->intValue() ) {
                    return;
                }
                JLogRecord* lr = new JLogRecord(JLevel::FINER, "THROW");
                lr->setSourceClassName(sourceClass);
                lr->setSourceMethodName(sourceMethod);
                lr->setThrown(thrown);
                doLog(lr);
            }

            void JLogger::severe(JString msg) {
                if (JLevel::SEVERE->intValue() < levelValue) {
                    return;
                }
                log(JLevel::SEVERE, msg);
            }

            void JLogger::warning(JString msg) {
                if (JLevel::WARNING->intValue() < levelValue) {
                    return;
                }
                log(JLevel::WARNING, msg);
            }

            void JLogger::info(JString msg) {
                if (JLevel::INFO->intValue() < levelValue) {
                    return;
                }
                log(JLevel::INFO, msg);
            }

            void JLogger::config(JString msg) {
                if (JLevel::CONFIG->intValue() < levelValue) {
                    return;
                }
                log(JLevel::CONFIG, msg);
            }

            void JLogger::fine(JString msg) {
                if (JLevel::FINE->intValue() < levelValue) {
                    return;
                }
                log(JLevel::FINE, msg);
            }

            void JLogger::finer(JString msg) {
                if (JLevel::FINER->intValue() < levelValue) {
                    return;
                }
                log(JLevel::FINER, msg);
            }

            void JLogger::finest(JString msg) {
                if (JLevel::FINEST->intValue() < levelValue) {
                    return;
                }
                log(JLevel::FINEST, msg);
            }

            void JLogger::setLevel(JLevel* newLevel) {
                treeLock->lock();
                levelObject = newLevel;
                updateEffectiveLevel();
                treeLock->unlock();
            }

            JLevel* JLogger::getLevel() {
                return levelObject;
            }

            jbool JLogger::isLoggable(JLevel* level) {
                if (level->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return false;
                }
                return true;
            }

            JString JLogger::getName() {
                return *name;
            }

            void JLogger::addHandler(JHandler* h){
                handlers->add(h);
            }

            void JLogger::removeHandler(JHandler* h){
                if (h == NULL) {
                    return;
                }
                handlers->remove(h);//TODO test
            }

            JPrimitiveArray* JLogger::getHandlers() {
                return handlers->toArray();
            }

            void JLogger::setUseParentHandlers(jbool useParentHandlers) {
                this->useParentHandlers = useParentHandlers;
            }

            jbool JLogger::getUseParentHandlers() {
                return useParentHandlers;
            }

            JLogger* JLogger::getParent() {
                return parent;
            }

            void JLogger::setParent(JLogger* parent) {
                doSetParent(parent);
            }

            void JLogger::doSetParent(JLogger* newParent) {
                treeLock->lock();

                JLogger* ref = NULL;
                if (parent != NULL) {
                    JIterator* iter=NULL;
                    for (iter = parent->kids->iterator(); iter->hasNext(); ) {
                        ref = (JLogger*)iter->next();
                        if (ref == this) {
                            iter->remove();
                            break;
                        } else {
                            ref = NULL;
                        }
                    }
                    delete iter;
                }

                parent = newParent;
                if (parent->kids == NULL) {
                    parent->kids = new JArrayList();
                }
                parent->kids->add(parent);
                updateEffectiveLevel();
                treeLock->unlock();
            }

            void JLogger::updateEffectiveLevel() {
                jint newLevelValue;
                if (levelObject != NULL) {
                    newLevelValue = levelObject->intValue();
                } else {
                    if (parent != NULL) {
                        newLevelValue = parent->levelValue;
                    } else {
                        newLevelValue = JLevel::INFO->intValue();
                    }
                }

                if (levelValue == newLevelValue) {
                    return;
                }

                levelValue = newLevelValue;

                if (kids != NULL) {
                    for (int i = 0; i < kids->size(); i++) {
                        JLogger* ref = (JLogger*)kids->get(i);
                        if (ref != NULL) {
                            ref->updateEffectiveLevel();
                        }
                    }
                }
            }

            JLogger::~JLogger(){
                if (name!=NULL){
                    delete name;
                }
                if (handlers!=NULL){
                    delete handlers;
                }
            }
        }
    }
}

