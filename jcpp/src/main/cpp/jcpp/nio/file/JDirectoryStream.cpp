#include "JDirectoryStream.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JDirectoryStreamClass : public JClass{
                public:
                    JDirectoryStreamClass(){
                        this->canonicalName="java.nio.file.DirectoryStream";
                        this->name="java.nio.file.DirectoryStream";
                        this->simpleName="DirectoryStream";
                        addInterface(JCloseable::getClazz());
                        addInterface(JIterable::getClazz());
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }

                    virtual void fillDeclaredClasses(){
                        addDeclaredClass(JDirectoryStream::JFilter::getClazz());
                    }
            };

            static JClass* clazz;

            JClass* JDirectoryStream::getClazz(){
                if (clazz==NULL){
                    clazz=new JDirectoryStreamClass();
                }
                return clazz;
            }

            class JDirectoryStreamFilterClass : public JClass{
                public:
                    JDirectoryStreamFilterClass(){
                        this->canonicalName="java.nio.file.DirectoryStream$Filter";
                        this->name="java.nio.file.DirectoryStream$Filter";
                        this->simpleName="DirectoryStream$Filter";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }

                    virtual JClass* getDeclaringClass(){
                        return JDirectoryStream::getClazz();
                    }
            };

            static JClass* filterClazz;

            JClass* JDirectoryStream::JFilter::getClazz(){
                if (filterClazz==NULL){
                    filterClazz=new JDirectoryStreamFilterClass();
                }
                return filterClazz;
            }

            JDirectoryStream::~JDirectoryStream(){
            }
        }
    }
}
