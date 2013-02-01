#ifndef JENUM_H
#define JENUM_H

#include "JObject.h"
#include "JClass.h"
#include "JInstantiationException.h"
using namespace std;


class JEnum: public JObject{

protected:

    class JEnumClass : public JClass{
      public:
        JEnumClass(){
            this->canonicalName="java.lang.Enum";
            this->name="java.lang.Enum";
            this->simpleName="Enum";
            this->bIsEnum=true;
        }

        JClass* getSuperclass(){
            return JObject::getClazz();
        }

        virtual JObject* newInstance(){
            throw new JInstantiationException("cannot instantiate enum of class "+getName());
        }
    };

    int ordinal;
    string name;
    JEnum(JEnumClass* _class,string name,int ordinal);

public:
    static JClass* getClazz();

    string getName();

    int getOrdinal();

    string toString();

    ~JEnum();
};

#endif // JENUM_H
