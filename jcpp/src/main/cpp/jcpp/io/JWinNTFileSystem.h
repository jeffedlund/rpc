#ifndef JWINNTFILESYSTEM_H
#define JWINNTFILESYSTEM_H

#include "JString.h"
#include "JIOFileSystem.h"
#include "JFile.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JWinNTFileSystem : public JFileSystem  {
            protected:
                jchar slash;
                jchar altSlash;
                jchar semicolon;
                jbool isSlash(jchar c);
                jbool isLetter(jchar c);
                string slashify(string p);
                string normalize(string p,jint len,jint off);
                jint normalizePrefix(string p,jint len,JStringBuffer* sb);
                string getUserPath();
                string getDrive(string path);

            public:
                static JClass* getClazz();
                JWinNTFileSystem();
                virtual jchar getSeparator();
                virtual jchar getPathSeparator();
                virtual string normalize(string path);
                virtual jint prefixLength(string path);
                virtual string resolve(string parent, string child);
                virtual string getDefaultParent();
                virtual string fromURIPath(string path);
                virtual jbool isAbsolute(JFile* f);
                virtual string resolve(JFile* f);
                virtual string canonicalize(string path);
                virtual jint getBooleanAttributes(JFile* f);
                virtual jbool checkAccess(JFile* f, jint access);
                virtual jbool setPermission(JFile* f,jint access,jbool enable,jbool owneronly);
                virtual jlong getLastModifiedTime(JFile* f);
                virtual jlong getLength(JFile* f);
                virtual jbool createFileExclusively(string pathname);
                virtual jbool deleteFile(JFile* f);
                virtual vector<string>* list(JFile* f);
                virtual jbool createDirectory(JFile* f);
                virtual jbool rename(JFile* f1, JFile* f2);
                virtual jbool setLastModifiedTime(JFile* f, jlong time);
                virtual jbool setReadOnly(JFile* f);
                virtual vector<JFile*>* listRoots();
                virtual jlong getSpace(JFile* f, jint t);
                virtual jint compare(JFile* f1, JFile* f2);
                virtual jint hashCode(JFile* f);
                virtual ~JWinNTFileSystem();

        };
    }
}

#endif // JWINNTFILESYSTEM_H

//
