#include "JCharConversionException.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JCharConversionExceptionClass : public JClass{
            public:
                JCharConversionExceptionClass(){
                    this->canonicalName="java.io.CharConversionException";
                    this->name="java.io.CharConversionException";
                    this->simpleName="CharConversionException";
                    this->serialVersionUID=-8680016352018427031ULL;
                }

                JClass* getSuperclass(){
                    return JIOException::getClazz();
                }

                JObject* newInstance(){
                    return new JCharConversionException();
                }
        };

        static JClass* clazz;

        JClass* JCharConversionException::getClazz(){
            if (clazz==NULL){
                clazz=new JCharConversionExceptionClass();
            }
            return clazz;
        }

        JCharConversionException::JCharConversionException():JIOException(getClazz()){
        }

        JCharConversionException::~JCharConversionException(){
        }
    }
}
