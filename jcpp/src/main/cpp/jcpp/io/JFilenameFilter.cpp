#include "JFilenameFilter.h"
#include "JClass.h"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JFilenameFilterClass : public JClass{
            public:
                JFilenameFilterClass(){
                    this->canonicalName="java.io.FilenameFilter";
                    this->name="java.io.FilenameFilter";
                    this->simpleName="FilenameFilter";
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFilenameFilter::getClazz(){
            if (clazz==NULL){
                clazz=new JFilenameFilterClass();
            }
            return clazz;
        }

        JFilenameFilter::~JFilenameFilter(){
        }
    }
}
