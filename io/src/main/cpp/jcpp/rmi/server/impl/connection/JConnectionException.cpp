#include "JConnectionException.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JConnectionExceptionClass : public JClass{
                    public:
                        JConnectionExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ConnectionException";
                            this->name="jcpp.rmi.server.impl.connection.ConnectionException";
                            this->simpleName="ConnectionException";
                            serialVersionUID=1470950606719849553ULL;
                        }

                        JClass* getSuperclass(){
                            return JException::getClazz();
                        }

                        JObject* newInstance(){
                            return new JConnectionException();
                        }
                    };

                    static JClass* clazz;

                    JClass* JConnectionException::getClazz(){
                        if (clazz==NULL){
                            clazz=new JConnectionExceptionClass();
                        }
                        return clazz;
                    }

                    JConnectionException::JConnectionException():JException(getClazz()){
                    }

                    JConnectionException::JConnectionException(JClass* _class):JException(_class){
                    }

                    JConnectionException::JConnectionException(string message):JException(getClazz()){
                        this->message=new JString(message);
                    }

                    JConnectionException::JConnectionException(string message,JThrowable* cause):JException(getClazz()){
                        this->message=new JString(message);
                        this->cause=cause;
                    }

                    JConnectionException::~JConnectionException(){
                    }
                }
            }
        }
    }
}
