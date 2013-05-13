#ifndef JWINNTFILESYSTEM_H
#define JWINNTFILESYSTEM_H

#include "JString.h"
#include "JIOFileSystem.h"
#include "JFile.h"
#include "JStringBuffer.h"

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
                JString slashify(JString p);
                JString normalize(JString p,jint len,jint off);
                jint normalizePrefix(JString p,jint len,JStringBuffer* sb);
                JString getUserPath();
                JString getDrive(JString path);

            public:
                static JClass* getClazz();
                JWinNTFileSystem();
                virtual jchar getSeparator();
                virtual jchar getPathSeparator();
                virtual JString normalize(JString path);
                virtual jint prefixLength(JString path);
                virtual JString resolve(JString parent, JString child);
                virtual JString getDefaultParent();
                virtual JString fromURIPath(JString path);
                virtual jbool isAbsolute(JFile* f);
                virtual JString resolve(JFile* f);
                virtual JString canonicalize(JString path);
                virtual jint getBooleanAttributes(JFile* f);
                virtual jbool checkAccess(JFile* f, jint access);
                virtual jbool setPermission(JFile* f,jint access,jbool enable,jbool owneronly);
                virtual jlong getLastModifiedTime(JFile* f);
                virtual jlong getLength(JFile* f);
                virtual jbool createFileExclusively(JString pathname);
                virtual jbool deleteFile(JFile* f);
                virtual vector<JString>* list(JFile* f);
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
