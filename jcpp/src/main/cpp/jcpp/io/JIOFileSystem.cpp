#include "JIOFileSystem.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JFileSystemClass : public JClass{
            public:
                JFileSystemClass(){
                    this->canonicalName="java.io.FileSystem";
                    this->name="java.io.FileSystem";
                    this->simpleName="FileSystem";
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

        jint JFileSystem::BA_EXISTS = 0x01;
        jint JFileSystem::BA_REGULAR = 0x02;
        jint JFileSystem::BA_DIRECTORY = 0x04;
        jint JFileSystem::BA_HIDDEN = 0x08;

        jint JFileSystem::ACCESS_READ = 0x04;
        jint JFileSystem::ACCESS_WRITE = 0x02;
        jint JFileSystem::ACCESS_EXECUTE = 0x01;

        jint JFileSystem::SPACE_TOTAL = 0;
        jint JFileSystem::SPACE_FREE = 1;
        jint JFileSystem::SPACE_USABLE = 2;

        JFileSystem::~JFileSystem(){
        }
    }
}
