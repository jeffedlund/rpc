#include "JPackage.h"
#include "JClass.h"
#include <sstream>
#include "JInstantiationException.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JPackageClass : public JClass{
                public:
                    JPackageClass():JClass(){
                        canonicalName="java.lang.Package";
                        name="java.lang.Package";//bof...
                        simpleName="Package";
                        bIsPackage=true;
                    }

                    JClass* getSuperclass(){
                        return NULL;
                    }
            };

            static JClass* clazz;

            JClass* JPackage::getClazz(){
                if (clazz==NULL){
                    clazz=new JPackageClass();
                }
                return clazz;
            }

            JPackage::JPackage(JString name,JClass* _class){
                this->name=name;
                this->_class=_class;
                this->classes=new vector<JClass*>();
                this->packages=new vector<JPackage*>();
            }

            void JPackage::addClass(JClass* c){
                classes->push_back(c);
            }

            JString JPackage::toString(){
                return "package "+name;
            }

            JClass* JPackage::getClass(){
                return _class;
            }

            vector<JClass*>* JPackage::getClasses(){
                return classes;
            }

            JPackage::~JPackage() {
                delete classes;
                delete packages;
            }
        }
    }
}

