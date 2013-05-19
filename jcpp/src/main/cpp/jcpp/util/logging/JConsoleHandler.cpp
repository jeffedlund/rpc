#include "JConsoleHandler.h"
#include "JClass.h"
#include "JSimpleFormatter.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JConsoleHandlerClass : public JClass{
                public:
                    JConsoleHandlerClass(){
                        this->canonicalName="java.util.logging.ConsoleHandler";
                        this->name="java.util.logging.ConsoleHandler";
                        this->simpleName="ConsoleHandler";
                        this->serialVersionUID=0ULL;
                    }

                    JClass* getSuperclass(){
                        return JStreamHandler::getClazz();
                    }

                    JObject* newInstance(){
                        return new JConsoleHandler();
                    }
            };

            static JClass* clazz;

            JClass* JConsoleHandler::getClazz(){
                if (clazz==NULL){
                    clazz=new JConsoleHandlerClass();
                }
                return clazz;
            }

            JConsoleHandler::JConsoleHandler(){
                sealed=false;
                configure();
                //TODO setOutputStream(JSystem::err);
                sealed=true;
            }

            void JConsoleHandler::configure() {
                //TODO JLogManager* manager = JLogManager::getLogManager();
                //TODO JString cname = getClass()->getName();

                setLevel(JLevel::INFO);//TODO manager.getLevelProperty(cname +".level", Level.INFO));
                setFilter(NULL);//TODO manager.getFilterProperty(cname +".filter", null));
                setFormatter(new JSimpleFormatter());//TODO manager.getFormatterProperty(cname +".formatter", new SimpleFormatter()));
                try {
                    setEncoding("");//TODO manager.getStringProperty(cname +".encoding", null));
                } catch (JException* ex) {
                    delete ex;
                    try {
                        setEncoding("");
                    } catch (JException* ex2) {
                        delete ex2;
                    }
                }
            }

            void JConsoleHandler::publish(JLogRecord* record) {
                JStreamHandler::publish(record);
                flush();
            }

            void JConsoleHandler::close(){
                flush();;
            }

            JConsoleHandler::~JConsoleHandler(){
            }
        }
    }
}
