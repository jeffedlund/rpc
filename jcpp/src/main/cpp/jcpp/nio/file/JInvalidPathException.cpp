#include "JInvalidPathException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JInvalidPathExceptionClass : public JClass{
                protected:
                    static JObject* staticGetInput(JObject* object){
                        JInvalidPathException* e=(JInvalidPathException*)object;
                        return e->input;
                    }

                    static void staticSetInput(JObject* object,JObject* value){
                        JInvalidPathException* e=(JInvalidPathException*)object;
                        if (e->input!=NULL){
                            delete e->input;
                        }
                        e->input=(JString*)value;
                    }

                    static JObject* staticGetIndex(JObject* object){
                        JInvalidPathException* e=(JInvalidPathException*)object;
                        return e->index;
                    }

                    static void staticSetIndex(JObject* object,JObject* value){
                        JInvalidPathException* e=(JInvalidPathException*)object;
                        if (e->index!=NULL){
                            delete e->index;
                        }
                        e->index=(JPrimitiveInt*)value;
                    }

                public:
                    JInvalidPathExceptionClass(){
                        this->canonicalName="java.nio.file.InvalidPathException";
                        this->name="java.nio.file.InvalidPathException";
                        this->simpleName="InvalidPathException";
                        this->serialVersionUID=4355821422286746137ULL;
                        addField(new JField("input",JString::getClazz(),this,staticGetInput,staticSetInput));
                        addField(new JField("index",JPrimitiveInt::getClazz(),this,staticGetIndex,staticSetIndex));
                    }

                    JClass* getSuperclass(){
                        return JIllegalArgumentException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JInvalidPathException();
                    }
            };

            static JClass* clazz;

            JClass* JInvalidPathException::getClazz(){
                if (clazz==NULL){
                    clazz=new JInvalidPathExceptionClass();
                }
                return clazz;
            }

            JInvalidPathException::JInvalidPathException():JIllegalArgumentException(getClazz()){
                input=NULL;
                index=NULL;
            }

            JInvalidPathException::JInvalidPathException(JString input,JString reason,jint index):JIllegalArgumentException(getClazz()){
                this->input=new JString(input);
                this->index=new JPrimitiveInt(index);
                this->message=new JString(reason);
            }

            JString JInvalidPathException::getInput(){
                return input;
            }

            JString JInvalidPathException::getReason(){
                return message;
            }

            jint JInvalidPathException::getIndex(){
                return index->get();
            }

            JInvalidPathException::~JInvalidPathException(){
                delete input;
                delete index;
            }
        }
    }
}
