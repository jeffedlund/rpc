#include "JClass.h"
#include <iostream>

using namespace std;




int main(int argc, char *argv[])
{
    JClass* toto = JClass::clazz;
    cout<<"Hello " << toto;
    cout<<toto->toString();
    string str;
    cin>>str;
    return 0;
}

