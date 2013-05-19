#include "JSimpleFormatter.h"
#include "JClass.h"
#include "JStringWriter.h"

namespace jcpp{
    namespace util{
        namespace logging{
        class JSimpleFormatterClass : public JClass{
            public:
                JSimpleFormatterClass(){
                    this->canonicalName="java.util.logging.SimpleFormatter";
                    this->name="java.util.logging.SimpleFormatter";
                    this->simpleName="SimpleFormatter";
                }

                JClass* getSuperclass(){
                    return JFormatter::getClazz();
                }

                JObject* newInstance(){
                    return new JSimpleFormatter();
                }
            };

            static JClass* clazz;

            JClass* JSimpleFormatter::getClazz(){
                if (clazz==NULL){
                    clazz=new JSimpleFormatterClass();
                }
                return clazz;
            }

            JSimpleFormatter::JSimpleFormatter():JFormatter(getClazz()){
            }

            JString JSimpleFormatter::format(JLogRecord* record){
                JString source("");
                if (record->getSourceClassName() != NULL) {
                    source << record->getSourceClassName();
                    if (record->getSourceMethodName() != NULL) {
                       source << " " << record->getSourceMethodName();
                    }
                } else {
                    source << record->getLoggerName();
                }
                JString message = formatMessage(record);

                JString throwable = "";
                if (record->getThrown() != NULL) {
                    //JStringWriter* sw = new JStringWriter();
                    //TODO JPrintWriter* pw = new JPrintWriter(sw);
                    //pw->println();
                    //record->getThrown()->printStackTrace(pw);
                    //pw.close();
                    //throwable = sw.toString();
                    throwable=record->getThrown()->toString();
                }
                return source << " : "<< message<<". Error: "<<throwable;
                //TODO JString::format(format,dat,source,record.getLoggerName(),record.getLevel().getLocalizedName(),message,throwable);
            }

            JSimpleFormatter::~JSimpleFormatter(){
            }
        }
    }
}
