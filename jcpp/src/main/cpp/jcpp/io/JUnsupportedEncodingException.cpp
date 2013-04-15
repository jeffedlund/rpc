#include "JUnsupportedEncodingException.h"
#include "JClass.h"

//namespace declaration
namespace jcpp{
    namespace io{

        class JUnsupportedEncodingExceptionClass : public JClass{
            public:
                JUnsupportedEncodingExceptionClass(){
                    this->canonicalName="java.io.UnsupportedEncodingException";
                    this->name="java.io.UnsupportedEncodingException";
                    this->simpleName="UnsupportedEncodingException";
                    this->serialVersionUID=-4274276298326136670ULL;
                }

                JClass* getSuperclass(){
                    return JIOException::getClazz();
                }

                JObject* newInstance(){
                    return new JUnsupportedEncodingException();
                }
        };

        static JClass* clazz;

        JClass* JUnsupportedEncodingException::getClazz(){
            if (clazz==NULL){
                clazz=new JUnsupportedEncodingExceptionClass();
            }
            return clazz;
        }

        JUnsupportedEncodingException::JUnsupportedEncodingException():JIOException(getClazz()){
        }

        JUnsupportedEncodingException::~JUnsupportedEncodingException(){
        }
    }
}
