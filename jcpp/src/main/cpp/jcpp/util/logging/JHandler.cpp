#include "JHandler.h"
#include "JClass.h"
#include "JLogManager.h"
#include "JFormatter.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JHandlerClass : public JClass{
                public:
                    JHandlerClass(){
                        this->canonicalName="java.util.logging.Handler";
                        this->name="java.util.logging.Handler";
                        this->simpleName="Handler";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JHandler::getClazz(){
                if (clazz==NULL){
                    clazz=new JHandlerClass();
                }
                return clazz;
            }

            JHandler::JHandler(JClass* _class):JObject(_class){
                logManager=JLogManager::getLogManager();
                filter=NULL;
                formatter=NULL;
                logLevel=JLevel::ALL;
                errorManager=new JErrorManager();
                encoding=NULL;
                sealed=true;
            }

            void JHandler::setFormatter(JFormatter* f){
                formatter=f;
            }

            JFormatter* JHandler::getFormatter(){
                return formatter;
            }

            void JHandler::setEncoding(JString enc){
                if (encoding!=NULL){
                    delete encoding;
                }
                this->encoding=new JString(enc);
            }

            JString* JHandler::getEncoding(){
                return encoding;
            }

            void JHandler::setFilter(JFilter* f){
                this->filter=f;
            }

            JFilter* JHandler::getFilter(){
                return filter;
            }

            void JHandler::setErrorManager(JErrorManager* em){
                this->errorManager=em;
            }

            JErrorManager* JHandler::getErrorManager(){
                return errorManager;
            }

            void JHandler::reportError(JString msg, JException* ex, jint code){
                try {
                    errorManager->error(msg, ex, code);
                } catch (JException* ex2) {
                    ex2->printStackTrace();
                }
            }

            void JHandler::setLevel(JLevel* l){
                lock();
                this->logLevel=l;
                unlock();
            }

            JLevel* JHandler::getLevel(){
                lock();
                JLevel* l=logLevel;
                unlock();
                return l;
            }

            jbool JHandler::isLoggable(JLogRecord* record){
                jint levelValue = getLevel()->intValue();
                if (record->getLevel()->intValue() < levelValue || levelValue == JLevel::OFF->intValue()) {
                    return false;
                }
                JFilter* filter = getFilter();
                if (filter == NULL) {
                    return true;
                }
                return filter->isLoggable(record);
            }

            JHandler::~JHandler(){
                if (errorManager!=NULL){
                    delete errorManager;
                }
                if (encoding!=NULL){
                    delete encoding;
                }
            }
        }
    }
}
