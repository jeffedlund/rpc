#include "JFileSystemException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemExceptionClass : public JClass{
                protected:
                    static JObject* staticGetFile(JObject* object){
                        JFileSystemException* e=(JFileSystemException*)object;
                        return e->file;
                    }

                    static void staticSetFile(JObject* object,JObject* value){
                        JFileSystemException* e=(JFileSystemException*)object;
                        if (e->file!=NULL){
                            delete e->file;
                        }
                        e->file=(JString*)value;
                    }

                    static JObject* staticGetOther(JObject* object){
                        JFileSystemException* e=(JFileSystemException*)object;
                        return e->other;
                    }

                    static void staticSetOther(JObject* object,JObject* value){
                        JFileSystemException* e=(JFileSystemException*)object;
                        if (e->other!=NULL){
                            delete e->other;
                        }
                        e->other=(JString*)value;
                    }

                public:
                    JFileSystemExceptionClass(){
                        this->canonicalName="java.nio.file.FileSystemException";
                        this->name="java.nio.file.FileSystemException";
                        this->simpleName="FileSystemException";
                        this->serialVersionUID=-3055425747967319812ULL;
                        addField(new JField("file",JString::getClazz(),this,staticGetFile,staticSetFile));
                        addField(new JField("other",JString::getClazz(),this,staticGetOther,staticSetOther));
                    }

                    JClass* getSuperclass(){
                        return JIOException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JFileSystemException();
                    }
            };

            static JClass* clazz;

            JClass* JFileSystemException::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileSystemExceptionClass();
                }
                return clazz;
            }

            JFileSystemException::JFileSystemException(JString file):JIOException(getClazz()){
                this->file=new JString(file);
                this->other=NULL;
            }

            JFileSystemException::JFileSystemException(JString file,JString other,JString reason):JIOException(getClazz()){
                this->file=new JString(file);
                this->other=new JString(other);
                this->message=new JString(reason);
            }

            JFileSystemException::JFileSystemException():JIOException(getClazz()){
                this->file=NULL;
                this->other=NULL;
            }

            JFileSystemException::JFileSystemException(JClass* _class,JString file):JIOException(_class){
                this->file=new JString(file);
                this->other=NULL;
            }

            JFileSystemException::JFileSystemException(JClass* _class,JString file,JString other,JString reason):JIOException(_class){
                this->file=new JString(file);
                this->other=new JString(other);
                this->message=new JString(reason);
            }

            JFileSystemException::JFileSystemException(JClass* _class):JIOException(_class){
                this->file=NULL;
                this->other=NULL;
            }

            JString JFileSystemException::getFile(){
                return file;
            }

            JString JFileSystemException::getOtherFile(){
                return other;
            }

            JString JFileSystemException::getReason(){
                return message;
            }

            JFileSystemException::~JFileSystemException(){
                if (file!=NULL){
                    delete file;
                }
                if (other!=NULL){
                    delete other;
                }
            }
        }
    }
}
