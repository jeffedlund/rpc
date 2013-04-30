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
            return ';';
        }

        string JWinNTFileSystem::normalize(string path){
            return path;
        }

        jint JWinNTFileSystem::prefixLength(string path){
            return 0;//TODO
        }

        string JWinNTFileSystem::resolve(string parent, string child){
            stringstream ss;
            ss<<parent<<getSeparator()<<child;
            return ss.str();
        }

        string JWinNTFileSystem::getDefaultParent(){
            return ""+getSeparator();
        }

        string JWinNTFileSystem::fromURIPath(string path){
            return path;//TODO
        }

        jbool JWinNTFileSystem::isAbsolute(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath()));
            return info.isAbsolute();
        }

        string JWinNTFileSystem::resolve(JFile* f){
            return f->getPath();//TODO
        }

        string JWinNTFileSystem::canonicalize(string path){
            return path;//TODO
        }
        jint JWinNTFileSystem::getBooleanAttributes(JFile* f){
            return 0;//TODO
        }
        jbool JWinNTFileSystem::checkAccess(JFile* f, jint access){
            return false;//TODO
        }
        jbool JWinNTFileSystem::setPermission(JFile* f,jint access,jbool enable,jbool owneronly){
            return false;//TODO
        }

        jlong JWinNTFileSystem::getLastModifiedTime(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath()));
            return info.lastModified().toMSecsSinceEpoch();
        }

        jlong JWinNTFileSystem::getLength(JFile* f){
            QFileInfo info(QString::fromStdString(f->getPath()));
            return info.size();
        }

        jbool JWinNTFileSystem::createFileExclusively(string pathname){
            return false;//TODO
        }

        jbool JWinNTFileSystem::deleteFile(JFile* f){
            QFile file(QString::fromStdString(f->getPath()));
            return file.remove();
        }

        vector<string>* JWinNTFileSystem::list(JFile* f){
            return NULL;//TODO
        }

        jbool JWinNTFileSystem::createDirectory(JFile* f){
            QDir dir1(QString::fromStdString(f->getPath()));
            QDir dir2(QString::fromStdString(f->getPath()));
            dir1.cdUp();
            return dir2.mkdir(dir1.dirName());
        }

        jbool JWinNTFileSystem::rename(JFile* f1, JFile* f2){
            QFile file1(QString::fromStdString(f1->getPath()));
            QFile file2(QString::fromStdString(f2->getPath()));
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
            QFileInfo info(QString::fromStdString(f->getPath()));
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
