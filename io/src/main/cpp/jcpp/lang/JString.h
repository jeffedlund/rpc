#ifndef JSTRING_H
#define JSTRING_H

#include "JObject.h"
using namespace std;

class JString : public JObject
{
    string str;

public:
    JString();
    ~JString();

    static JClass* clazz;

    string getString();
    void setString(string str);

};

#endif // JSTRING_H
