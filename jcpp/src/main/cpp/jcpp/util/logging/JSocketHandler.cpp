#include "JSocketHandler.h"
#include "JClass.h"
#include "JIllegalArgumentException.h"
#include "JBufferedOutputStream.h"
#include "JXMLFormatter.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JSocketHandlerClass : public JClass{
                public:
                    JSocketHandlerClass(){
                        this->canonicalName="java.util.logging.SocketHandler";
                        this->name="java.util.logging.SocketHandler";
                        this->simpleName="SocketHandler";
                    }

                    JClass* getSuperclass(){
                        return JStreamHandler::getClazz();
                    }

                    JObject* newInstance(){
                        return new JSocketHandler();
                    }
            };

            static JClass* clazz;

            JClass* JSocketHandler::getClazz(){
                if (clazz==NULL){
                    clazz=new JSocketHandlerClass();
                }
                return clazz;
            }

            JSocketHandler::JSocketHandler():JStreamHandler(getClazz()){
                sock=NULL;
                host=NULL;
                port=0;
                portProperty=NULL;
                sealed = false;
                configure();
                try {
                    connect();
                } catch (JIOException* ix) {
                    ix->printStackTrace();
                    throw ix;
                }
                sealed = true;
            }

            JSocketHandler::JSocketHandler(JString host, jint port){
                portProperty=NULL;
                sealed = false;
                configure();
                sealed = true;
                this->port = port;
                this->host = new JString(host);
                connect();
            }

            void JSocketHandler::configure() {
                //TODO JLogManager* manager = JLogManager::getLogManager();
                JString cname = getClass()->getName();

                setLevel(JLevel::ALL);//TODO manager.getLevelProperty(cname +".level", Level.ALL));
                setFilter(NULL);//TODO manager.getFilterProperty(cname +".filter", null));
                setFormatter(new JXMLFormatter());//TODO manager.getFormatterProperty(cname +".formatter", new XMLFormatter()));
                try {
                    setEncoding("");//TODOmanager.getStringProperty(cname +".encoding", null));
                } catch (JException* ex) {
                    delete ex;
                    try {
                        setEncoding("");
                    } catch (JException* ex2) {
                        delete ex2;
                    }
                }
                port = 0;//TODO manager.getIntProperty(cname + ".port", 0);
                host = new JString("localhost");//TODO manager.getStringProperty(cname + ".host", null);
            }

            void JSocketHandler::connect(){
                if (port == 0) {
                    throw new JIllegalArgumentException("Bad port: 0");
                }
                if (host == NULL) {
                    throw new JIllegalArgumentException("Null host name: ");
                }

                sock = new JSocket(*host, port);
                JOutputStream* out = sock->getOutputStream();
                JBufferedOutputStream* bout = new JBufferedOutputStream(out);
                setOutputStream(bout);
            }

            void JSocketHandler::close(){
                lock();
                JStreamHandler::close();
                if (sock != NULL) {
                    try {
                        sock->close();
                    } catch (JIOException* ix) {
                        delete ix;
                    }
                }
                delete sock;
                sock = NULL;
                unlock();
            }

            void JSocketHandler::publish(JLogRecord* record) {
                lock();
                if (!isLoggable(record)) {
                    unlock();
                    return;
                }
                JStreamHandler::publish(record);
                flush();
                unlock();
            }

            JSocketHandler::~JSocketHandler(){
                if (host!=NULL){
                    delete host;
                }
                if (sock!=NULL){
                    delete sock;
                }
            }
        }
    }
}

