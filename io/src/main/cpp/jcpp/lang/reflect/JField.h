#ifndef JFIELD_H
#define JFIELD_H

#include "JObject.h"
using namespace std;

class JField: public JObject{
private:
    string name;
    JClass* type;

protected:
    JField(string name,JClass* type);

public:

    static JClass* getClazz();

    string getName();

    JClass* getType();

    virtual JObject* get(JObject* object)=0;

    virtual void set(JObject* object, JObject* value)=0;

    string toString();
};
#endif // JFIELD_H
