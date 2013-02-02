#ifndef JCLASSLOADER_H
#define JCLASSLOADER_H

#include "JClassBuilder.h"
#include <map>
using namespace std;

class JClassLoader : public JObject{
protected:
    map<string, JClass*>* classes;

public:
    JClassLoader();

    static JClassLoader* getBootClassLoader();

    void addClasses(JClassBuilder* jClassBuilder);

    JClass* loadClass(string string);

    static JClass* getClazz();

    ~JClassLoader();
};


#endif // JCLASSLOADER__H
