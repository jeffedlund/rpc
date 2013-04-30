#include "JDefaultFileSystem.h"
#include "JClass.h"
#include "JWinNTFileSystem.h"

namespace jcpp{
    namespace io{
        class JDefaultFileSystemClass : public JClass{
            public:
                JDefaultFileSystemClass(){
                    this->canonicalName="java.io.DefaultFileSystem";
                    this->name="java.io.DefaultFileSystem";
                    this->simpleName="DefaultFileSystem";
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JDefaultFileSystem::getClazz(){
            if (clazz==NULL){
                clazz=new JDefaultFileSystemClass();
            }
            return clazz;
        }

        JFileSystem* JDefaultFileSystem::getFileSystem(){
            return new JWinNTFileSystem();
        }

        JDefaultFileSystem::~JDefaultFileSystem(){
        }
    }
}
