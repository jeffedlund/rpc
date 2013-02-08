#ifndef JPRIMITIVEARRAY_H
#define JPRIMITIVEARRAY_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
using namespace std;


class JPrimitiveArray : public JObject{
private:
    vector<JObject*>* objects;
    int len;

public:
    JPrimitiveArray(JClass* arrayClass,int len=10);

    bool operator==(JPrimitiveArray &other);

    static JClass* getClazz(JClass* componentType);

    int size();

    void setSize(int len);

    JObject* get(int i);

    void set(int i,JObject* value);

    ~JPrimitiveArray();
};

#endif // JPRIMITIVEARRAY_H
