#include "JErrorManager.h"
#include "JClass.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JErrorManagerClass : public JClass{
                public:
                    JErrorManagerClass(){
                        this->canonicalName="java.util.logging.ErrorManager";
                        this->name="java.util.logging.ErrorManager";
                        this->simpleName="ErrorManager";
                        this->serialVersionUID=0ULL;

                        //interfaces

                        //fields
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }

                    JObject* newInstance(){
                        return new JErrorManager();
                    }
            };

            static JClass* clazz;

            JClass* JErrorManager::getClazz(){
                if (clazz==NULL){
                    clazz=new JErrorManagerClass();
                }
                return clazz;
            }

            JErrorManager::JErrorManager():JObject(getClazz()){
                reported=false;
            }

            jint JErrorManager::GENERIC_FAILURE = 0;

            jint JErrorManager::WRITE_FAILURE = 1;

            jint JErrorManager::FLUSH_FAILURE = 2;

            jint JErrorManager::CLOSE_FAILURE = 3;

            jint JErrorManager::OPEN_FAILURE = 4;

            jint JErrorManager::FORMAT_FAILURE = 5;

            void JErrorManager::error(JString m, JException* e, jint code){
                lock();
                if (reported) {
                    return;
                }
                reported = true;
                JString text = "java.util.logging.ErrorManager: " + code;
                text<<": " << m;
                cerr<<text<<"\r\n";
                //TODO System::err::println(text);
                if (e != NULL) {
                    e->printStackTrace();
                }
                unlock();
            }

            JErrorManager::~JErrorManager(){
            }
        }
    }
}
