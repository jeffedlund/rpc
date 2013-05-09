#include "JSerializablePermission.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JSerializablePermissionClass : public JClass{
            protected:
                static JObject* staticGetActions(JObject* object){
                    JSerializablePermission* sp=(JSerializablePermission*)object;
                    return sp->actions;
                }

                static void staticSetActions(JObject* object,JObject* value){
                    JSerializablePermission* sp=(JSerializablePermission*)object;
                    delete sp->actions;
                    sp->actions=(JString*)value;
                }

            public:
                JSerializablePermissionClass(){
                    this->canonicalName="java.io.SerializablePermission";
                    this->name="java.io.SerializablePermission";
                    this->simpleName="SerializablePermission";
                    this->serialVersionUID=8537212141160296410ULL;

                    addField(new JField("actions",JString::getClazz(),this,staticGetActions,staticSetActions));
                }

                JClass* getSuperclass(){
                    return JBasicPermission::getClazz();
                }

                JObject* newInstance(){
                    return new JSerializablePermission();
                }
        };

        static JClass* clazz;

        JClass* JSerializablePermission::getClazz(){
            if (clazz==NULL){
                clazz=new JSerializablePermissionClass();
            }
            return clazz;
        }

        JSerializablePermission::JSerializablePermission():JBasicPermission(getClazz()){
            this->actions=new JString();
        }

        JSerializablePermission::JSerializablePermission(JString name):JBasicPermission(getClazz(),name){
            this->actions=new JString();
        }

        JSerializablePermission::JSerializablePermission(JString name,JString actions):JBasicPermission(getClazz(),name){
            this->actions=new JString(actions);
        }

        JSerializablePermission::~JSerializablePermission(){
            delete actions;
        }
    }
}
