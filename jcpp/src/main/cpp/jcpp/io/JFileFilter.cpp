#include "JFileFilter.h"
#include "JClass.h"
#include "JFile.h"

namespace jcpp{
    namespace io{
        class JFileFilterClass : public JClass{
            protected:


            public:
                JFileFilterClass(){
                    this->canonicalName="java.io.FileFilter";
                    this->name="java.io.FileFilter";
                    this->simpleName="FileFilter";
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JFileFilter::getClazz(){
            if (clazz==NULL){
                clazz=new JFileFilterClass();
            }
            return clazz;
        }

        JFileFilter::~JFileFilter(){
        }
    }
}
