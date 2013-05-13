#ifndef JPACKAGE_H
#define JPACKAGE_H

#include "JString.h"
#include "vector"
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JClass;
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JPackage{
                protected:
                    JString* name;
                    JClass* _class;
                    vector<JClass*>* classes;
                    vector<JPackage*>* packages;
                    JPackage(JString name,JClass* _class);
                    void addClass(JClass* c);

                public:
                    static JClass* getClazz();
                    virtual JPackage* getSuperPackage()=0;
                    virtual vector<JPackage*>* getPackages()=0;
                    virtual JString toString();
                    virtual JClass* getClass();
                    virtual vector<JClass*>* getClasses();
                    virtual ~JPackage();
            };
        }
    }
}

#endif // JPACKAGE_H
