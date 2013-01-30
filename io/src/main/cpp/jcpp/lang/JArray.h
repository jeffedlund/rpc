#ifndef JARRAY_H
#define JARRAY_H

#include "JObject.h"
#include "JClass.h"
#include <vector>

class JArrayClass : public JClass{
    public:
      JArrayClass(JClass* componentType);
};

class JArray : public JObject
{
private:
    std::vector<JObject*>* objects;

public:
    JArray(JArrayClass* arrayClass);

    ~JArray();
};

#endif // JARRAY_H
