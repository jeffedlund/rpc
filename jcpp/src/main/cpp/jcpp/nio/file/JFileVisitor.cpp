#include "JFileVisitor.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JFileVisitorClass : public JClass{
            public:
                JFileVisitorClass(){
                    this->canonicalName="java.nio.file.FileVisitor";
                    this->name="java.nio.file.FileVisitor";
                    this->simpleName="FileVisitor";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JFileVisitor::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileVisitorClass();
                }
                return clazz;
            }

            JFileVisitor::~JFileVisitor(){
            }
        }
    }
}
