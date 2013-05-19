#include "JFormatter.h"
#include "JClass.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JFormatterClass : public JClass{
                public:
                    JFormatterClass(){
                        this->canonicalName="java.util.logging.Formatter";
                        this->name="java.util.logging.Formatter";
                        this->simpleName="Formatter";
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JFormatter::getClazz(){
                if (clazz==NULL){
                    clazz=new JFormatterClass();
                }
                return clazz;
            }

            JFormatter::JFormatter(JClass* _class):JObject(_class){
            }

            JString JFormatter::getHead(JHandler* h){
                return "";
            }

            JString JFormatter::getTail(JHandler* h){
                return "";
            }

            JString JFormatter::formatMessage(JLogRecord* record){
                JString* format = record->getMessage();
                //TODO return java.text.MessageFormat.format(format, parameters);
                return *format;
            }

            JFormatter::~JFormatter(){
            }
        }
    }
}
