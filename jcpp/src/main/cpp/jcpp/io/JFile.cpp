#include "JFile.h"
#include "JClass.h"
#include "JIOFileSystem.h"
#include "JPath.h"
#include "JDefaultFileSystem.h"

namespace jcpp{
    namespace io{
        class JFileClass : public JClass{
            protected:
                //TODO fill serializable fields like path

            public:
                JFileClass(){
                    this->canonicalName="java.io.File";
                    this->name="java.io.File";
                    this->simpleName="File";
                    this->serialVersionUID=301077366599181567ULL;
                    addInterface(JSerializable::getClazz());
                    addInterface(JComparable::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                JObject* newInstance(){
                    return new JFile();
                }
        };

        static JClass* clazz;

        JClass* JFile::getClazz(){
            if (clazz==NULL){
                clazz=new JFileClass();
            }
            return clazz;
        }

        jcpp::io::JFileSystem* JFile::fs = JDefaultFileSystem::getFileSystem();

        jchar JFile::separatorChar = fs->getSeparator();

        JString JFile::separator = JString(separatorChar);

        jchar JFile::pathSeparatorChar = fs->getPathSeparator();

        JString JFile::pathSeparator = JString(pathSeparatorChar);

        JFile::JFile():JObject(getClazz()){
            path=NULL;
            prefixLength=0;
            filePath=NULL;
        }

        JFile::JFile(JString pathname,jint prefix):JObject(getClazz()){
            this->path=new JString(pathname);
            this->prefixLength=prefix;
            filePath=NULL;
        }

        JFile::JFile(JString child,JFile* parent):JObject(getClazz()){
            this->path=new JString(fs->resolve(*parent->path,child));
            this->prefixLength=parent->prefixLength;
            filePath=NULL;
        }

        JFile::JFile(JString pathname){
            this->path=new JString(fs->normalize(pathname));
            this->prefixLength=fs->prefixLength(*this->path);
            filePath=NULL;
        }

        JFile::JFile(JString parent,JString child){
            if (parent=="") {
                this->path = new JString(fs->resolve(fs->getDefaultParent(),fs->normalize(child)));
            } else {
                this->path = new JString(fs->resolve(fs->normalize(parent),fs->normalize(child)));
            }
            this->prefixLength = fs->prefixLength(this->path);
        }

        JFile::JFile(JFile* parent,JString child){
            if ((*parent->path)=="") {
                this->path = new JString(fs->resolve(fs->getDefaultParent(),fs->normalize(child)));
            } else {
                this->path = new JString(fs->resolve(parent->path,fs->normalize(child)));
            }
            this->prefixLength = fs->prefixLength(this->path);
        }

        jint JFile::getPrefixLength(){
            return prefixLength;
        }

        JString JFile::getName(){
            jint index = path->getString().find_last_of(separatorChar);//TODO remove usage of getString
            if (index < prefixLength){
                return path->getString().substr(prefixLength,path->getString().size());
            }
            return path->getString().substr(index + 1,path->getString().size());
        }

        JString* JFile::getParent(){
            jint index = path->getString().find_last_of(separatorChar);
            if (index < prefixLength) {
                if ((prefixLength > 0) && (path->length() > prefixLength)){
                    return new JString(path->substring(0, prefixLength));
                }
                return NULL;
            }
            return new JString(path->substring(0, index));
        }

        JFile* JFile::getParentFile(){
            JString p=getParent();
            if (p==""){
                return NULL;
            }
            return new JFile(p,prefixLength);
        }

        JString JFile::getPath(){
            return JString(path);
        }

        jbool JFile::isAbsolute(){
            return fs->isAbsolute(this);
        }

        JString JFile::getAbsolutePath(){
            return fs->resolve(this);
        }

        JFile* JFile::getAbsoluteFile(){
            JString absPath=getAbsolutePath();
            return new JFile(absPath,fs->prefixLength(absPath));
        }

        JString JFile::getCanonicalPath(){
            return fs->canonicalize(fs->resolve(this));
        }

        JFile* JFile::getCanonicalFile(){
            JString canonPath=getCanonicalPath();
            return new JFile(canonPath,fs->prefixLength(canonPath));
        }

        JString JFile::slashify(JString path, jbool isDirectory) {
            JString p = path;
            if (JFile::separatorChar != '/'){
                p=p.replace(JFile::separatorChar, (jchar)'/');
            }
            if (p.getString().find("/")>0){//TODO JString.indexOf
                p = "/" + p;
            }
            if (p.charAt(p.length()-1)=='/' && isDirectory){
                p = p + "/";
            }
            return p;
        }

        jbool JFile::canRead(){
            return fs->checkAccess(this,jcpp::io::JFileSystem::ACCESS_READ);
        }

        jbool JFile::canWrite(){
            return fs->checkAccess(this,jcpp::io::JFileSystem::ACCESS_WRITE);
        }

        jbool JFile::exists(){
            return (fs->getBooleanAttributes(this) & jcpp::io::JFileSystem::BA_EXISTS)!=0;
        }

        jbool JFile::isDirectory(){
            return (fs->getBooleanAttributes(this) & jcpp::io::JFileSystem::BA_DIRECTORY)!=0;
        }

        jbool JFile::isFile(){
            return (fs->getBooleanAttributes(this) & jcpp::io::JFileSystem::BA_REGULAR)!=0;
        }

        jbool JFile::isHidden(){
            return (fs->getBooleanAttributes(this) & jcpp::io::JFileSystem::BA_HIDDEN)!=0;
        }

        jlong JFile::lastModified(){
            return fs->getLastModifiedTime(this);
        }

        jlong JFile::length(){
            return fs->getLength(this);
        }

        jbool JFile::createNewFile(){
            return fs->createFileExclusively(path->getString());
        }

        jbool JFile::deleteFile(){
            return fs->deleteFile(this);
        }

        void  JFile::deleteOnExit(){
            //TODO DeleteOnExitHook::add(path)
        }

        vector<JString>* JFile::list(){
            return fs->list(this);
        }

        vector<JString>* JFile::list(JFilenameFilter* filter){
            vector<JString>* names=list();
            if (names->size()==0){
                return names;
            }
            vector<JString>* newnames=new vector<JString>();
            for (unsigned i=0;i<names->size();i++){
                if (filter->accept(this,names->at(i))){
                    newnames->push_back(names->at(i));
                }
            }
            delete names;
            return newnames;
        }

        vector<JFile*>* JFile::listFiles(){
            vector<JFile*>* files=new vector<JFile*>();
            vector<JString>* names=list();
            for (unsigned i=0;i<names->size();i++){
                files->push_back(new JFile(names->at(i),this));
            }
            delete names;
            return files;
        }

        vector<JFile*>* JFile::listFiles(JFilenameFilter* filter){
            vector<JFile*>* files=new vector<JFile*>();
            vector<JString>* names=list();
            for (unsigned i=0;i<names->size();i++){
                if (filter==NULL || filter->accept(this,names->at(i))){
                    files->push_back(new JFile(names->at(i),this));
                }
            }
            delete names;
            return files;
        }

        vector<JFile*>* JFile::listFiles(JFileFilter* filter){
            vector<JFile*>* files=new vector<JFile*>();
            vector<JString>* names=list();
            for (unsigned i=0;i<names->size();i++){
                JFile* f=new JFile(names->at(i),this);
                if (filter==NULL || filter->accept(f)){
                    files->push_back(f);
                }else{
                    delete f;
                }
            }
            delete names;
            return files;
        }

        jbool JFile::mkdir(){
            return fs->createDirectory(this);
        }

        jbool JFile::mkdirs(){
            if (exists()){
                return false;
            }
            if (mkdir()){
                return true;
            }
            JFile* canonFile=NULL;
            try{
                canonFile=getCanonicalFile();
            }catch(JIOException* e){
                return false;
            }
            JFile* parent=canonFile->getParentFile();
            return (parent!= NULL && (parent->mkdirs() || parent->exists()) && canonFile->mkdir());
        }

        jbool JFile::renameTo(JFile* dest){
            return fs->rename(this,dest);
        }

        jbool JFile::setLastModified(jlong time){
            return fs->setLastModifiedTime(this,time);
        }

        jbool JFile::setReadOnly(){
            return fs->setReadOnly(this);
        }

        jbool JFile::setWritable(jbool writable, jbool ownerOnly){
            return fs->setPermission(this,jcpp::io::JFileSystem::ACCESS_WRITE,writable,ownerOnly);
        }

        jbool JFile::setWritable(jbool writable){
            return setWritable(writable,true);
        }

        jbool JFile::setReadable(jbool readable,jbool ownerOnly){
            return fs->setPermission(this,jcpp::io::JFileSystem::ACCESS_READ,readable,ownerOnly);
        }

        jbool JFile::setReadable(jbool readable){
            return setReadable(readable,true);
        }

        jbool JFile::setExecutable(jbool executable,jbool ownerOnly){
            return fs->setPermission(this,jcpp::io::JFileSystem::ACCESS_EXECUTE,executable,ownerOnly);
        }

        jbool JFile::setExecutable(jbool executable){
            return setExecutable(executable,true);
        }

        jbool JFile::canExecute(){
            return fs->checkAccess(this,jcpp::io::JFileSystem::ACCESS_EXECUTE);
        }

        vector<JFile*>* JFile::listRoots(){
            return fs->listRoots();
        }

        jlong JFile::getTotalSpace(){
            return fs->getSpace(this,jcpp::io::JFileSystem::SPACE_TOTAL);
        }

        jlong JFile::getFreeSpace(){
            return fs->getSpace(this,jcpp::io::JFileSystem::SPACE_FREE);
        }

        jlong JFile::getUsableSpace(){
            return fs->getSpace(this,jcpp::io::JFileSystem::SPACE_USABLE);
        }

        JFile* JFile::createTempFile(JString, JString, JFile* ){
            return NULL;//TODO
        }

        JFile* JFile::createTempFile(JString , JString ){
            return NULL;//TODO
        }

        jint JFile::compareTo(JFile* pathname){
            return fs->compare(this,pathname);
        }

        jint JFile::compareTo(JObject* o){
            return compareTo((JFile*)o);
        }

        jbool JFile::equals(JObject* object){
            if (object->getClass()!=getClass()){
                return false;
            }
            return compareTo((JFile*)object)==0;
        }

        jint JFile::hashCode(){
            return fs->hashCode(this);
        }

        JString JFile::toString(){
            return JString(getPath());//TODO
        }

        void JFile::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeChar(separatorChar);
        }

        void JFile::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            JString* pathField = (JString*)fields->get("path", (JObject*)NULL);
            if (pathField!=NULL){
                ;
            }
            jchar sep = in->readChar();//TODO
            if (sep>0){
                ;
            }
        }

        jcpp::nio::file::JPath* JFile::toPath(){
            jcpp::nio::file::JPath* result=filePath;
            if (result==NULL){
                lock();
                result=filePath;
                if (result==NULL){
                    result=NULL;//TODO JFileSystems::getDefault()->getPath(path);
                    filePath=result;
                }
            }
            return result;
        }

        JFile::~JFile(){
            delete this->path;
            delete this->filePath;
        }
    }
}
