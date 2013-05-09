#include "JWinNTFileSystem.h"
#include "JClass.h"
#include <QFile>
#include "QFileInfo"
#include "QDir"
#include "sstream"
#include <QDateTime>

namespace jcpp{
    namespace io{
        class JWinNTFileSystemClass : public JClass{
            public:
                JWinNTFileSystemClass(){
                    this->canonicalName="java.io.WinNTFileSystem";
                    this->name="java.io.WinNTFileSystem";
                    this->simpleName="WinNTFileSystem";
                }

                JClass* getSuperclass(){
                    return JFileSystem::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JWinNTFileSystem::getClazz(){
            if (clazz==NULL){
                clazz=new JWinNTFileSystemClass();
            }
            return clazz;
        }

        JWinNTFileSystem::JWinNTFileSystem():JFileSystem(getClazz()){
        }

        jchar JWinNTFileSystem::getSeparator(){
            return (jchar)QDir::separator().toLatin1();
        }

        jchar JWinNTFileSystem::getPathSeparator(){
            /*TODO a way to do it is the following :
             #ifdef _WIN32
             const std::String os_pathsep(";");
             #else
             const std::String os_pathsep(":");
             #endif

             find a better one
                */

            return ';';
        }

        JString JWinNTFileSystem::normalize(JString path){
            return path;
        }

        jint JWinNTFileSystem::prefixLength(JString path){
            return 0;//TODO
        }

        JString JWinNTFileSystem::resolve(JString parent, JString child){
            JString ss;
            ss<<parent<<getSeparator()<<child;
            return ss;
        }

        JString JWinNTFileSystem::getDefaultParent(){
            return ""+getSeparator();
        }

        JString JWinNTFileSystem::fromURIPath(JString path){
            return path;//TODO
        }

        jbool JWinNTFileSystem::isAbsolute(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            return info.isAbsolute();
        }

        JString JWinNTFileSystem::resolve(JFile* f){
            return f->getPath();//TODO
        }

        JString JWinNTFileSystem::canonicalize(JString path){
            return path;//TODO
        }

        jint JWinNTFileSystem::getBooleanAttributes(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            jint b=0;
            if (info.exists()){
                b|=BA_EXISTS;
            }
            if (info.isDir()){
                b|=BA_DIRECTORY;
            }
            if (info.isHidden()){
                b|=BA_HIDDEN;
            }
            if (info.isFile()){
                b|=BA_REGULAR;
            }
            return b;
        }

        jbool JWinNTFileSystem::checkAccess(JFile* f, jint access){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            if (access==ACCESS_READ){
                return info.isReadable();
            }
            if (access==ACCESS_WRITE){
                return info.isWritable();
            }
            if (access==ACCESS_EXECUTE){
                return info.isExecutable();
            }
            return false;
        }

        jbool JWinNTFileSystem::setPermission(JFile* f,jint access,jbool enable,jbool owneronly){
            QFile::Permissions p;
            if (access==ACCESS_READ){
                if (owneronly){
                    if (enable){
                        p|=QFile::ReadOwner;
                    }
                }else{
                    if (enable){
                        p|=QFile::ReadOwner;
                        p|=QFile::ReadUser;
                        p|=QFile::ReadGroup;
                        p|=QFile::ReadOther;
                    }
                }
            }
            if (access==ACCESS_WRITE){
                if (owneronly){
                    if (enable){
                        p|=QFile::WriteOwner;
                    }
                }else{
                    if (enable){
                        p|=QFile::WriteOwner;
                        p|=QFile::WriteUser;
                        p|=QFile::WriteGroup;
                        p|=QFile::WriteOther;
                    }
                }
            }
            if (access==ACCESS_EXECUTE){
                if (owneronly){
                    if (enable){
                        p|=QFile::ExeOwner;
                    }
                }else{
                    if (enable){
                        p|=QFile::ExeOwner;
                        p|=QFile::ExeUser;
                        p|=QFile::ExeGroup;
                        p|=QFile::ExeOther;
                    }
                }
            }
            QFile qfile(QString::fromStdString(f->getPath().getString()));
            return qfile.setPermissions(p);
        }

        jlong JWinNTFileSystem::getLastModifiedTime(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            return info.lastModified().toMSecsSinceEpoch();
        }

        jlong JWinNTFileSystem::getLength(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            return info.size();
        }

        jbool JWinNTFileSystem::createFileExclusively(JString pathname){
            return false;//TODO
        }

        jbool JWinNTFileSystem::deleteFile(JFile* f){
            QFile file(QString::fromStdString(f->getPath().getString()));
            return file.remove();
        }

        vector<JString>* JWinNTFileSystem::list(JFile* f){
            return NULL;//TODO
        }

        jbool JWinNTFileSystem::createDirectory(JFile* f){
            QDir dir1(QString::fromStdString(f->getPath().getString()));
            QDir dir2(QString::fromStdString(f->getPath().getString()));
            dir1.cdUp();
            return dir2.mkdir(dir1.dirName());
        }

        jbool JWinNTFileSystem::rename(JFile* f1, JFile* f2){
            QFile file1(QString::fromStdString(f1->getPath().getString()));
            QFile file2(QString::fromStdString(f2->getPath().getString()));
            return QFile::rename(file1.fileName(),file2.fileName());
        }

        jbool JWinNTFileSystem::setLastModifiedTime(JFile* f, jlong time){
            //TODO
            return false;
        }

        jbool JWinNTFileSystem::setReadOnly(JFile* f){
            //TODO
            return false;
        }

        vector<JFile*>* JWinNTFileSystem::listRoots(){
            //TODO QDir::drives()
            return NULL;
        }

        jlong JWinNTFileSystem::getSpace(JFile* f, jint t){
            QFileInfo info(QString::fromStdString(f->getPath().getString()));
            return 0;//TODO return total, free,usable
        }

        jint JWinNTFileSystem::compare(JFile* f1, JFile* f2){
            return JString::compare(f1->getPath(),f2->getPath());
        }

        jint JWinNTFileSystem::hashCode(JFile* f){
            return JString::hashCode(f->getPath())^1234321;
        }

        JWinNTFileSystem::~JWinNTFileSystem(){
        }
    }
}
