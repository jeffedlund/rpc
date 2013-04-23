#ifndef JSECUREDIRECTORYSTREAM_H
#define JSECUREDIRECTORYSTREAM_H

#include "JClass.h"
#include "JLinkOption.h"
#include "JInterface.h"
#include "JSet.h"
#include "JDirectoryStream.h"
#include "JObject.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace nio{
        namespace file{
            class JSecureDirectoryStream : public JDirectoryStream  {
                protected:
                public:
                    static JClass* getClazz();
                    virtual JSecureDirectoryStream* newDirectoryStream(JObject* path, vector<JLinkOption*>* options)=0;
                    //TODO virtual JSeekableByteChannel * newByteChannel(JObject* path, JSet* options, vector<JFileAttribute*>* attrs);
                    virtual void  deleteFile(JObject* path)=0;
                    virtual void  deleteDirectory(JObject* path)=0;
                    virtual void  move(JObject* srcPath, JSecureDirectoryStream* targetDir, JObject* targetPath)=0;
                    //TODO virtual JFileAttributeView * getFileAttributeView(JClass* type)=0;
                    //TODO virtual JFileAttributeView * getFileAttributeView(JObject* path, JClass* type, vector<JLinkOption*>* options)=0;
                    virtual ~JSecureDirectoryStream();
            };
        }
    }
}

#endif // JSECUREDIRECTORYSTREAM_H
