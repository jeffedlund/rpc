#ifndef JPACKAGE_H
#define JPACKAGE_H

#include "vector"
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        namespace reflect{
            class JPackage{
                protected:
                    string name;
                    JClass* _class;
                    vector<JClass*>* classes;
                    vector<JPackage*>* packages;

                    JPackage(string name,JClass* _class);
                    void addClass(JClass* c);

                public:
                    virtual JPackage* getSuperPackage()=0;

                    virtual vector<JPackage*>* getPackages()=0;

                    string toString();

                    JClass* getClass();

                    vector<JClass*>* getClasses();

                    static JClass* getClazz();

                    ~JPackage();

            };
        }
    }
}

#endif // JPACKAGE_H
