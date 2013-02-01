#ifndef JCLASSLOADER_H
#define JCLASSLOADER_H

#include "JClassBuilder.h"
#include <map>

using namespace std;

class JClassLoader {//TODO exetnds JOBject
protected:
    map<string, JClass*>* classes;

public:
    JClassLoader();

    static JClassLoader* getBootClassLoader();

    void addClasses(JClassBuilder* jClassBuilder);

    JClass* loadClass(string string);

    ~JClassLoader();
};


#endif // JCLASSLOADER__H
