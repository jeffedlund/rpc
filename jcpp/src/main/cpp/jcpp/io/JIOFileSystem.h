#ifndef JIO_FILESYSTEM_H
#define JIO_FILESYSTEM_H

#include "JString.h"
#include "JObject.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;
        class JFileSystem : public JObject  {
        protected:
            JFileSystem(JClass* _class);

            public:
                static JClass* getClazz();
                static jint BA_EXISTS;
                static jint BA_REGULAR;
                static jint BA_DIRECTORY;
                static jint BA_HIDDEN;

                static jint ACCESS_READ;
                static jint ACCESS_WRITE;
                static jint ACCESS_EXECUTE;

                static jint SPACE_TOTAL;
                static jint SPACE_FREE;
                static jint SPACE_USABLE;

                virtual jchar getSeparator()=0;
                virtual jchar getPathSeparator()=0;
                virtual string normalize(string path)=0;
                virtual jint prefixLength(string path)=0;
                virtual string resolve(string parent, string child)=0;
                virtual string getDefaultParent()=0;
                virtual string fromURIPath(string path)=0;
                virtual jbool isAbsolute(JFile* f)=0;
                virtual string resolve(JFile* f)=0;
                virtual string canonicalize(string path)=0;
                virtual jint getBooleanAttributes(JFile* f)=0;
                virtual jbool checkAccess(JFile* f, jint access)=0;
                virtual jbool setPermission(JFile* f,jint access,jbool enable,jbool owneronly)=0;
                virtual jlong getLastModifiedTime(JFile* f)=0;
                virtual jlong getLength(JFile* f)=0;
                virtual jbool createFileExclusively(string pathname)=0;
                virtual jbool deleteFile(JFile* f)=0;
                virtual vector<string>* list(JFile* f)=0;
                virtual jbool createDirectory(JFile* f)=0;
                virtual jbool rename(JFile* f1, JFile* f2)=0;
                virtual jbool setLastModifiedTime(JFile* f, jlong time)=0;
                virtual jbool setReadOnly(JFile* f)=0;
                virtual vector<JFile*>* listRoots()=0;
                virtual jlong getSpace(JFile* f, jint t)=0;
                virtual jint compare(JFile* f1, JFile* f2)=0;
                virtual jint hashCode(JFile* f)=0;
                virtual ~JFileSystem();
        };
    }
}

#endif // JIO_FILESYSTEM_H
