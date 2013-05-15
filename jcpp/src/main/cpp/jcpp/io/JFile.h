#ifndef JFILE_H
#define JFILE_H

#include "JSerializable.h"
#include "JString.h"
#include "JFileFilter.h"
#include "JObject.h"
#include "JFilenameFilter.h"
#include "JComparable.h"
#include "JObjectOutputStream.h"
#include "JObjectInputStream.h"
#include "JIOFileSystem.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JPath;
        }
    }
    namespace io{
        class JCPP_LIBRARY_EXPORT JFile : public JObject, public JSerializable, public JComparable  {
            protected:
                static jcpp::io::JFileSystem* fs;
                JString* path;
                jint prefixLength;
                jcpp::nio::file::JPath* filePath;
                JFile();
                JFile(JString pathname,jint prefix);
                JFile(JString child,JFile* parent);
                jint getPrefixLength();
                static JString slashify(JString path, jbool isDirectory);
                virtual void writeObject(JObjectOutputStream* out);
                virtual void readObject(JObjectInputStream* in);
                friend class JFileClass;

            public:
                static JClass* getClazz();
                static jchar separatorChar;
                static JString separator;
                static jchar pathSeparatorChar;
                static JString pathSeparator;
                static vector<JFile*>* listRoots();
                static JFile* createTempFile(JString prefix, JString suffix, JFile* directory);
                static JFile* createTempFile(JString prefix, JString suffix);

                JFile(JString pathname);
                JFile(JString parent,JString child);
                JFile(JFile* parent,JString child);
                //TODO JFile(JURI* uri);
                virtual JString getName();
                virtual JString* getParent();
                virtual JFile* getParentFile();
                virtual JString getPath();
                virtual jbool isAbsolute();
                virtual JString getAbsolutePath();
                virtual JFile* getAbsoluteFile();
                virtual JString getCanonicalPath();
                virtual JFile* getCanonicalFile();
                //TODO virtual JURL* toURL();
                //TODO virtual JURI* toURI();
                virtual jbool canRead();
                virtual jbool canWrite();
                virtual jbool exists();
                virtual jbool isDirectory();
                virtual jbool isFile();
                virtual jbool isHidden();
                virtual jlong lastModified();
                virtual jlong length();
                virtual jbool createNewFile();
                virtual jbool deleteFile();
                virtual void  deleteOnExit();
                virtual vector<JString>* list();
                virtual vector<JString>* list(JFilenameFilter* filter);
                virtual vector<JFile*>* listFiles();
                virtual vector<JFile*>* listFiles(JFilenameFilter* filter);
                virtual vector<JFile*>* listFiles(JFileFilter* filter);
                virtual jbool mkdir();
                virtual jbool mkdirs();
                virtual jbool renameTo(JFile* dest);
                virtual jbool setLastModified(jlong time);
                virtual jbool setReadOnly();
                virtual jbool setWritable(jbool writable, jbool ownerOnly);
                virtual jbool setWritable(jbool writable);
                virtual jbool setReadable(jbool readable,jbool ownerOnly);
                virtual jbool setReadable(jbool readable);
                virtual jbool setExecutable(jbool executable,jbool ownerOnly);
                virtual jbool setExecutable(jbool executable);
                virtual jbool canExecute();
                virtual jlong getTotalSpace();
                virtual jlong getFreeSpace();
                virtual jlong getUsableSpace();
                virtual jint compareTo(JFile* pathname);
                virtual jint compareTo(JObject*);
                virtual jbool equals(JObject* object);
                virtual jint hashCode();
                virtual JString toString();
                virtual jcpp::nio::file::JPath* toPath();
                virtual ~JFile();
        };
    }
}

#endif // JFILE_H
