#include "JUTFDataFormatException.h"

namespace jcpp{
    namespace io{
        class JUTFDataFormatExceptionClass : public JClass{
        public:
            JUTFDataFormatExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.UTFDataFormatException";
                name="java.io.UTFDataFormatException";
                simpleName="UTFDataFormatException";
                serialVersionUID=420743449228280612ULL;
            }

            JClass* getSuperclass(){
                return JIOException::getClazz();
            }

            JObject* newInstance(){
                return new JUTFDataFormatException();
            }
        };

        static JClass* clazz;

        JClass* JUTFDataFormatException::getClazz(){
            if (clazz==NULL){
                clazz=new JUTFDataFormatExceptionClass();
            }
            return clazz;
        }

        JUTFDataFormatException::JUTFDataFormatException():JIOException(getClazz()){
        }

        JUTFDataFormatException::JUTFDataFormatException(string message) : JIOException(getClazz()){
            this->message=new JString(message);
        }

        JUTFDataFormatException::~JUTFDataFormatException(){
        }
    }
}
