#include "JStreamHandler.h"
#include "JClass.h"
#include "JNullPointerException.h"
#include "JOutputStreamWriter.h"
#include "JUnsupportedEncodingException.h"
#include "JError.h"
#include "JSimpleFormatter.h"

namespace jcpp{
    namespace util{
        namespace logging{
        class JStreamHandlerClass : public JClass{
            public:
                JStreamHandlerClass(){
                    this->canonicalName="java.util.logging.StreamHandler";
                    this->name="java.util.logging.StreamHandler";
                    this->simpleName="StreamHandler";
                }

                JClass* getSuperclass(){
                    return JHandler::getClazz();
                }

                JObject* newInstance(){
                    return new JStreamHandler();
                }
            };

            static JClass* clazz;

            JClass* JStreamHandler::getClazz(){
                if (clazz==NULL){
                    clazz=new JStreamHandlerClass();
                }
                return clazz;
            }

            JStreamHandler::JStreamHandler(JClass* _class):JHandler(_class){
                manager=JLogManager::getLogManager();
                output=NULL;
                doneHeader=false;
                writer=NULL;
                sealed=false;
                configure();
                sealed=true;
            }

            JStreamHandler::JStreamHandler():JHandler(getClazz()){
                manager=JLogManager::getLogManager();
                output=NULL;
                doneHeader=false;
                writer=NULL;
                sealed=false;
                configure();
                sealed=true;
            }

            JStreamHandler::JStreamHandler(JOutputStream* out, JFormatter* formatter):JHandler(getClazz()){
                manager=JLogManager::getLogManager();
                output=NULL;
                doneHeader=false;
                writer=NULL;
                sealed = false;
                configure();
                setFormatter(formatter);
                setOutputStream(out);
                sealed = true;
            }

            void JStreamHandler::configure() {
                JLogManager* manager = JLogManager::getLogManager();
                JString cname = getClazz()->getName();

                setLevel(JLevel::INFO);//TODO manager->getLevelProperty(cname +".level", JLevel::INFO));
                setFilter(NULL);//TODOmanager->getFilterProperty(cname +".filter", NULL));
                setFormatter(new JSimpleFormatter());//TODOmanager.getFormatterProperty(cname +".formatter", new SimpleFormatter()));
                try {
                    setEncoding("");//TODOmanager->getStringProperty(cname +".encoding", NULL));
                } catch (JException* ex) {
                    delete ex;
                    try {
                        setEncoding("");
                    } catch (JException* ex2) {
                        delete ex2;
                    }
                }
            }

            void JStreamHandler::setOutputStream(JOutputStream* out){
                if (out == NULL) {
                    throw new JNullPointerException();
                }
                lock();
                flushAndClose();
                output = out;
                doneHeader = false;
                JString encoding = getEncoding();
                if (encoding == NULL) {
                    writer = new JOutputStreamWriter(output);
                } else {
                    try {
                        writer = new JOutputStreamWriter(output, encoding);
                    } catch (JUnsupportedEncodingException* ex) {
                        unlock();
                        throw new JError("Unexpected exception " + ex->toString(),ex);
                    }
                }
                unlock();
            }

            void JStreamHandler::setEncoding(JString encoding){
                JHandler::setEncoding(encoding);
                if (output == NULL) {
                    return;
                }
                flush();
                if (encoding == "") {
                    writer = new JOutputStreamWriter(output);
                } else {
                    writer = new JOutputStreamWriter(output, encoding);
                }
            }

            void JStreamHandler::publish(JLogRecord* record) {
                lock();
                if (!isLoggable(record)) {
                    unlock();
                    return;
                }
                JString msg;
                try {
                    msg = getFormatter()->format(record);
                } catch (JException* ex) {
                    reportError("", ex, JErrorManager::FORMAT_FAILURE);
                    unlock();
                    return;
                }

                try {
                    if (!doneHeader) {
                        writer->write(getFormatter()->getHead(this));
                        doneHeader = true;
                    }
                    writer->write(msg);
                } catch (JException* ex) {
                    reportError("", ex, JErrorManager::WRITE_FAILURE);
                }
                unlock();
            }

            jbool JStreamHandler::isLoggable(JLogRecord* record) {
                if (writer == NULL || record == NULL) {
                    return false;
                }
                return JHandler::isLoggable(record);
            }

            void JStreamHandler::flush() {
                lock();
                if (writer != NULL) {
                    try {
                        writer->flush();
                    } catch (JException* ex) {
                        reportError("", ex, JErrorManager::FLUSH_FAILURE);
                    }
                }
                unlock();
            }

            void JStreamHandler::flushAndClose(){
                lock();
                if (writer != NULL) {
                    try {
                        if (!doneHeader) {
                            writer->write(getFormatter()->getHead(this));
                            doneHeader = true;
                        }
                        writer->write(getFormatter()->getTail(this));
                        writer->flush();
                        writer->close();
                    } catch (JException* ex) {
                        reportError("", ex, JErrorManager::CLOSE_FAILURE);
                    }
                    writer = NULL;
                    output = NULL;
                }
                unlock();
            }

            void JStreamHandler::close(){
                flushAndClose();
            }

            JStreamHandler::~JStreamHandler(){
                delete writer;
            }
        }
    }
}
