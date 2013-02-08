#ifndef JFIELD_H
#define JFIELD_H

#include "JObject.h"
using namespace std;

class JField: public JObject{
public:
    typedef JObject* (*getter)(JObject* objet);
    typedef void (*setter)(JObject* object,JObject* value);

private:
    string name;
    JClass* type;
    getter g;
    setter s;

public:
    JField(string name,JClass* type);
    JField(string name,JClass* type,getter g,setter s);

    static JClass* getClazz();

    string getName();

    JClass* getType();

    virtual JObject* get(JObject* object);

    virtual void set(JObject* object, JObject* value);

    string toString();
};
#endif // JFIELD_H
