#ifndef JBOOTCLASSBUILDER_H
#define JBOOTCLASSBUILDER_H

#include "JObject.h"
#include "JClass.h"
using namespace  std;

class JBootClassBuilder : public JClassBuilder {
    vector<JClass*> * classes;

public:
    JBootClassBuilder();

    void addClass(JClass* clazz);
    vector<JClass*>* getClasses();
};

#endif // JBOOTCLASSBUILDER_H
