#include "JFileVisitResult.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JFileVisitResult::JFileVisitResultClass::JFileVisitResultClass(){
                this->canonicalName="java.nio.file.FileVisitResult";
                this->name="java.nio.file.FileVisitResult";
                this->simpleName="FileVisitResult";
            }

            void JFileVisitResult::JFileVisitResultClass::fillEnumConstants(){
                addEnumConstant(JFileVisitResult::CONTINUE);
                addEnumConstant(JFileVisitResult::TERMINATE);
                addEnumConstant(JFileVisitResult::SKIP_SUBTREE);
                addEnumConstant(JFileVisitResult::SKIP_SIBLINGS);
            }

            static JClass* clazz;

            JClass* JFileVisitResult::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileVisitResultClass();
                }
                return clazz;
            }

            JFileVisitResult::JFileVisitResult(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),new JString(name),new JPrimitiveInt(ordinal)){
            }

            JFileVisitResult* JFileVisitResult::CONTINUE = new JFileVisitResult(new JString("CONTINUE"),new JPrimitiveInt(0));

            JFileVisitResult* JFileVisitResult::TERMINATE = new JFileVisitResult(new JString("TERMINATE"),new JPrimitiveInt(1));

            JFileVisitResult* JFileVisitResult::SKIP_SUBTREE = new JFileVisitResult(new JString("SKIP_SUBTREE"),new JPrimitiveInt(2));

            JFileVisitResult* JFileVisitResult::SKIP_SIBLINGS = new JFileVisitResult(new JString("SKIP_SIBLINGS"),new JPrimitiveInt(3));

            JFileVisitResult::~JFileVisitResult(){
            }
        }
    }
}
