#ifndef JFIELD_H
#define JFIELD_H

#include "JObject.h"

class JField: public JObject{
private:
    std::string name;
    JClass* type;

public:
    static JClass* clazz;

    JField(std::string name,JClass* type);

    std::string getName();

    JClass* getType();

    JObject* get(JObject* object);

    void set(JObject* object, JObject* value);

    std::string toString();
};
#endif // JFIELD_H
