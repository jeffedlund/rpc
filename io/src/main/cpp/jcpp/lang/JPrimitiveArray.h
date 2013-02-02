#ifndef JPRIMITIVEARRAY_H
#define JPRIMITIVEARRAY_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
using namespace std;


class JPrimitiveArray : public JObject{
private:
    vector<JObject*>* objects;

public:
    JPrimitiveArray(JClass* arrayClass);

    JObject* get(int i);

    void set(int i,JObject* value);

    ~JPrimitiveArray();
};

#endif // JPRIMITIVEARRAY_H
