#include "JClass.h"
#include "JDouble.h"
#include <iostream>

using namespace std;




int main(int argc, char *argv[])
{
    JClass* toto = JClass::getClazz();
    JObject object;
    cout<<object.toString();
    string str;
    cin>>str;
    cout<<object.getClass()->getSerialVersionUID();
    cin>>str;
    JDouble* jdouble=new JDouble(45);
    cout<<jdouble->toString();
    cin>>str;
    cout<<jdouble->getClass()->getSerialVersionUID();
    cout<<"clazz=="<<JClass::getClazz()->getName();
    cout<<"jdouble class=="<<jdouble->getClass()->getName();
    cout<<"jdouble class.class=="<<jdouble->getClass()->getClass()->getName();
    cin>>str;
    return 0;
}

