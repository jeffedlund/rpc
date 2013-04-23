#include "JStandardOpenOption.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            JStandardOpenOption::JStandardOpenOptionClass::JStandardOpenOptionClass(){
                this->canonicalName="java.nio.file.StandardOpenOption";
                this->name="java.nio.file.StandardOpenOption";
                this->simpleName="StandardOpenOption";
                addInterface(JOpenOption::getClazz());
            }

            void JStandardOpenOption::JStandardOpenOptionClass::fillEnumConstants(){
                addEnumConstant(JStandardOpenOption::READ);
                addEnumConstant(JStandardOpenOption::WRITE);
                addEnumConstant(JStandardOpenOption::APPEND);
                addEnumConstant(JStandardOpenOption::TRUNCATE_EXISTING);
                addEnumConstant(JStandardOpenOption::CREATE);
                addEnumConstant(JStandardOpenOption::CREATE_NEW);
                addEnumConstant(JStandardOpenOption::DELETE_ON_CLOSE);
                addEnumConstant(JStandardOpenOption::SPARSE);
                addEnumConstant(JStandardOpenOption::SYNC);
                addEnumConstant(JStandardOpenOption::DSYNC);
            }

            static JClass* clazz;

            JClass* JStandardOpenOption::getClazz(){
                if (clazz==NULL){
                    clazz=new JStandardOpenOptionClass();
                }
                return clazz;
            }

            JStandardOpenOption::JStandardOpenOption(JString* name, JPrimitiveInt* ordinal):JEnum((JEnumClass*)getClazz(),name,ordinal){
            }

            JStandardOpenOption* JStandardOpenOption::READ = new JStandardOpenOption(new JString("READ"),new JPrimitiveInt(0));

            JStandardOpenOption* JStandardOpenOption::WRITE = new JStandardOpenOption(new JString("WRITE"),new JPrimitiveInt(1));

            JStandardOpenOption* JStandardOpenOption::APPEND = new JStandardOpenOption(new JString("APPEND"),new JPrimitiveInt(2));

            JStandardOpenOption* JStandardOpenOption::TRUNCATE_EXISTING = new JStandardOpenOption(new JString("TRUNCATE_EXISTING"),new JPrimitiveInt(3));

            JStandardOpenOption* JStandardOpenOption::CREATE = new JStandardOpenOption(new JString("CREATE"),new JPrimitiveInt(4));

            JStandardOpenOption* JStandardOpenOption::CREATE_NEW = new JStandardOpenOption(new JString("CREATE_NEW"),new JPrimitiveInt(5));

            JStandardOpenOption* JStandardOpenOption::DELETE_ON_CLOSE = new JStandardOpenOption(new JString("DELETE_ON_CLOSE"),new JPrimitiveInt(6));

            JStandardOpenOption* JStandardOpenOption::SPARSE = new JStandardOpenOption(new JString("SPARSE"),new JPrimitiveInt(7));

            JStandardOpenOption* JStandardOpenOption::SYNC = new JStandardOpenOption(new JString("SYNC"),new JPrimitiveInt(8));

            JStandardOpenOption* JStandardOpenOption::DSYNC = new JStandardOpenOption(new JString("DSYNC"),new JPrimitiveInt(9));

            JStandardOpenOption::~JStandardOpenOption(){
            }
        }
    }
}
