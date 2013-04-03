#include "JREFLECT.h"
#include "JLANG.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            JREFLECT::JREFLECT():JPackage("jcpp.lang",JPackage::getClazz()){//better class
                classes->push_back(JAccessibleObject::getClazz());
                classes->push_back(JField::getClazz());
                classes->push_back(JInvocationHandler::getClazz());
                classes->push_back(JMember::getClazz());
                classes->push_back(JMethod::getClazz());
                classes->push_back(JModifier::getClazz());
                classes->push_back(JPackage::getClazz());
                classes->push_back(JProxy::getClazz());
            }

            JPackage* JREFLECT::getSuperPackage(){
                return JLANG::getPackage();
            }

            vector<JPackage*>* JREFLECT::getPackages(){
                if (packages->size()==0){
                }
                return packages;
            }

            static JREFLECT* jreflect=NULL;

            JREFLECT* JREFLECT::getPackage(){
                if (jreflect==NULL){
                    jreflect=new JREFLECT();
                }
                return jreflect;
            }

            JREFLECT::~JREFLECT(){
            }
        }
    }
}
