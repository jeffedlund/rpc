#ifndef JENUM_H
#define JENUM_H

#include "JObject.h"
#include "JClass.h"
using namespace std;

class JEnum;

class JEnumClass : public JClass{
    private :
      vector<JEnum*>* enums;

    public:
      JEnumClass();

      JEnum* valueOf(string value);
};

class JEnum: public JObject
{

protected:
    int ordinal;
    string name;
    JEnum(JEnumClass* enumClass,string name,int ordinal);

public:
    string getName();

    int getOrdinal();

    ~JEnum();
};

#endif // JENUM_H
