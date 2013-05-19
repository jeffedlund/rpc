#include "JMemoryHandler.h"
#include "JClass.h"
#include "JRuntimeException.h"
#include "JNullPointerException.h"
#include "JIllegalArgumentException.h"
#include "JSimpleFormatter.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JMemoryHandlerClass : public JClass{
                public:
                    JMemoryHandlerClass(){
                        this->canonicalName="java.util.logging.MemoryHandler";
                        this->name="java.util.logging.MemoryHandler";
                        this->simpleName="MemoryHandler";
                    }

                    JClass* getSuperclass(){
                        return JHandler::getClazz();
                    }

                    JObject* newInstance(){
                        return new JMemoryHandler();
                    }
            };

            static JClass* clazz;

            JClass* JMemoryHandler::getClazz(){
                if (clazz==NULL){
                    clazz=new JMemoryHandlerClass();
                }
                return clazz;
            }

            JMemoryHandler::JMemoryHandler():JHandler(getClazz()){
                pushLevel=NULL;
                size=0;
                target=NULL;
                buffer=NULL;
                start=0;
                count=0;
                sealed = false;
                configure();
                sealed = true;
                //TODO JLogManager* manager = JLogManager::getLogManager();
                JString handlerName = getClass()->getName();
                JString targetName = "";//TODO manager.getProperty(handlerName+".target");
                if (targetName == "") {
                    throw new JRuntimeException("The handler " + handlerName + " does not specify a target");
                }
                JClass* clz;
                try {
                    clz = getClass()->getClassLoader()->loadClass(targetName);
                    target = (JHandler*) clz->newInstance();
                } catch (JThrowable* e) {
                    throw new JRuntimeException("MemoryHandler can't load handler target \"" + targetName + "\"" , e);
                }
                init();
            }

            JMemoryHandler::JMemoryHandler(JHandler* target, jint size, JLevel* pushLevel):JHandler(getClazz()){
                pushLevel=NULL;
                size=0;
                target=NULL;
                buffer=NULL;
                start=0;
                count=0;
                if (target == NULL || pushLevel == NULL) {
                    throw new JNullPointerException();
                }
                if (size <= 0) {
                    throw new JIllegalArgumentException();
                }
                sealed = false;
                configure();
                sealed = true;
                this->target = target;
                this->pushLevel = pushLevel;
                this->size = size;
                init();
            }

            void JMemoryHandler::init() {
                buffer = new vector<JLogRecord*>();
                start = 0;
                count = 0;
            }

            void JMemoryHandler::configure() {
                //TODO JLogManager* manager = JLogManager::getLogManager();
                JString cname = getClass()->getName();

                pushLevel = JLevel::SEVERE;//TODO manager.getLevelProperty(cname +".push", Level.SEVERE);
                size = 1000;//TODO manager.getIntProperty(cname + ".size", DEFAULT_SIZE);
                setLevel(JLevel::ALL);//TODO manager.getLevelProperty(cname +".level", Level.ALL));
                setFilter(NULL);//TODO manager.getFilterProperty(cname +".filter", null));
                setFormatter(new JSimpleFormatter());//TODO manager.getFormatterProperty(cname +".formatter", new SimpleFormatter()));
            }

            void JMemoryHandler::publish(JLogRecord* record) {
                lock();
                if (!isLoggable(record)) {
                    unlock();
                    return;
                }
                buffer->push_back(record);
                if (record->getLevel()->intValue() >= pushLevel->intValue()) {
                    push();
                }
                unlock();
            }

            void JMemoryHandler::push() {
                for (unsigned int i = 0; i < buffer->size(); i++) {
                    JLogRecord* record = (JLogRecord*)buffer->at(i);
                    target->publish(record);
                }
                buffer->clear();
                start = 0;
                count = 0;
            }

            void JMemoryHandler::flush() {
                target->flush();
            }

            void JMemoryHandler::close(){
                target->close();
                setLevel(JLevel::OFF);
            }

            void JMemoryHandler::setPushLevel(JLevel* newLevel){
                if (newLevel == NULL) {
                    throw new JNullPointerException();
                }
                pushLevel = newLevel;
            }

            JLevel* JMemoryHandler::getPushLevel() {
                return pushLevel;
            }

            jbool JMemoryHandler::isLoggable(JLogRecord* record) {
                return JHandler::isLoggable(record);
            }

            JMemoryHandler::~JMemoryHandler(){
                delete buffer;
            }
        }
    }
}
