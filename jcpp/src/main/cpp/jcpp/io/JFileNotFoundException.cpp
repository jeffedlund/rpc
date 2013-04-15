#include "JFileNotFoundException.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JFileNotFoundExceptionClass : public JClass{
            public:
                JFileNotFoundExceptionClass(){
                    this->canonicalName="java.io.FileNotFoundException";
                    this->name="java.io.FileNotFoundException";
                    this->simpleName="FileNotFoundException";
                    this->serialVersionUID=-897856973823710492ULL;
                }

                JClass* getSuperclass(){
                    return JIOException::getClazz();
                }

                JObject* newInstance(){
                    return new JFileNotFoundException();
                }
        };

        static JClass* clazz;

        JClass* JFileNotFoundException::getClazz(){
            if (clazz==NULL){
                clazz=new JFileNotFoundExceptionClass();
            }
            return clazz;
        }

        JFileNotFoundException::JFileNotFoundException():JIOException(getClazz()){
        }

        JFileNotFoundException::~JFileNotFoundException(){
        }
    }
}
