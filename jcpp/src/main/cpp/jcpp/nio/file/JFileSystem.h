#ifndef JFILESYSTEM_H
#define JFILESYSTEM_H

#include "JWatchService.h"
#include "JString.h"
#include "JCloseable.h"
#include "JObject.h"
#include "JSet.h"
#include "JIterable.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystem : public JObject  , public JCloseable  {
                protected:
                    JFileSystem();
                public:
                    static JClass* getClazz();
                    //TODO virtual JFileSystemProvider* provider()=0;
                    virtual void  close()=0;
                    virtual jbool isOpen()=0;
                    virtual jbool isReadOnly()=0;
                    virtual string getSeparator()=0;
                    virtual JIterable* getRootDirectories()=0;
                    virtual JIterable* getFileStores()=0;
                    virtual JSet* supportedFileAttributeViews()=0;
                    //TODO virtual JPath* getPath(string first, vector<string>* more)=0;
                    //TODO virtual JPathMatcher* getPathMatcher(string syntaxAndPattern)=0;
                    //TODO virtual JUserPrincipalLookupService* getUserPrincipalLookupService()=0;
                    virtual JWatchService* newWatchService()=0;
                    virtual ~JFileSystem();
            };
        }
    }
}

#endif // JFILESYSTEM_H
