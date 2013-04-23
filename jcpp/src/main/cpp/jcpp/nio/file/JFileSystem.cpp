#include "JFileSystem.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JFileSystemClass : public JClass{
            public:
                JFileSystemClass(){
                    this->canonicalName="java.nio.file.FileSystem";
                    this->name="java.nio.file.FileSystem";
                    this->simpleName="FileSystem";
                    addInterface(JCloseable::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JFileSystem::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileSystemClass();
                }
                return clazz;
            }

            JFileSystem::~JFileSystem(){
            }
        }
    }
}
