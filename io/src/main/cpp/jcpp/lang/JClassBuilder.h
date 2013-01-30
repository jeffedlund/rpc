#ifndef JCLASSBUILDER_H
#define JCLASSBUILDER_H

#include "JObject.h"
#include "JClass.h"
using namespace  std;

class JClassBuilder {

public:
    virtual JClass* createClass(string className){
        return NULL;
    }

    virtual JObject* createObject(JClass* clazz){
        return NULL;
    }

};

#endif // JCLASSBUILDER_H
