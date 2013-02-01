#ifndef JFIELD_H
#define JFIELD_H

#include "JObject.h"

class JField: public JObject{
private:
    std::string name;
    JClass* type;

public:
    JField(std::string name,JClass* type);

    static JClass* getClazz();

    std::string getName();

    JClass* getType();

    JObject* get(JObject* object);

    void set(JObject* object, JObject* value);

    std::string toString();
};
#endif // JFIELD_H
