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
        class JFile : public JObject  , public JSerializable  , public JComparable  {
            protected:
                static jcpp::io::JFileSystem* fs;
                JString* path;
                jint prefixLength;
                jcpp::nio::file::JPath* filePath;
                JFile();
                JFile(string pathname,jint prefix);
                JFile(string child,JFile* parent);
                jint getPrefixLength();
                static string slashify(string path, jbool isDirectory);
                virtual void writeObject(JObjectOutputStream* out);
                virtual void readObject(JObjectInputStream* in);
                friend class JFileClass;

            public:
                static JClass* getClazz();
                static jchar separatorChar;
                static string separator;
                static jchar pathSeparatorChar;
                static string pathSeparator;
                static vector<JFile*>* listRoots();
                static JFile* createTempFile(string prefix, string suffix, JFile* directory);
                static JFile* createTempFile(string prefix, string suffix);

                JFile(string pathname);
                JFile(string parent,string child);
                JFile(JFile* parent,string child);
                //TODO JFile(JURI* uri);
                virtual string getName();
                virtual string getParent();
                virtual JFile* getParentFile();
                virtual string getPath();
                virtual jbool isAbsolute();
                virtual string getAbsolutePath();
                virtual JFile* getAbsoluteFile();
                virtual string getCanonicalPath();
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
                virtual vector<string>* list();
                virtual vector<string>* list(JFilenameFilter* filter);
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
                virtual string toString();
                virtual jcpp::nio::file::JPath* toPath();
                virtual ~JFile();
        };
    }
}

#endif // JFILE_H
