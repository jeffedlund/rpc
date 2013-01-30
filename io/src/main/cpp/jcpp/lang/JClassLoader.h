#ifndef JCLASSLOADER_H
#define JCLASSLOADER_H

#include "JClassBuilder.h"
#include <map>

using namespace std;

class JClassLoader {
protected:
    map<string, JClassBuilder> classBuilders;

public:
    JClassLoader();

    static JClassLoader* BOOT_CLASS_LOADER;

    void addClassBuilder(string className,JClassBuilder jClassBuilder);

    JObject* createObject(string string);

    ~JClassLoader();
};


#endif // JCLASSLOADER__H
