#include "JPermission.h"
#include "JClass.h"

namespace jcpp{
    namespace security{
        class JPermissionClass : public JClass{
            protected:
                static JObject* staticGetName(JObject* object){
                    JPermission* p=(JPermission*)object;
                    return p->name;
                }

                static void staticSetName(JObject* object,JObject* value){
                    JPermission* p=(JPermission*)object;
                    delete p->name;
                    p->name=(JString*)value;
                }

            public:
                JPermissionClass(){
                    this->canonicalName="java.security.Permission";
                    this->name="java.security.Permission";
                    this->simpleName="Permission";
                    this->serialVersionUID=-5636570222231596674ULL;
                    addInterface(JGuard::getClazz());
                    addInterface(JSerializable::getClazz());
                    addField(new JField("name",JString::getClazz(),this,staticGetName,staticSetName));

                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JPermission::getClazz(){
            if (clazz==NULL){
                clazz=new JPermissionClass();
            }
            return clazz;
        }

        JPermission::JPermission(JClass* _class,string name):JObject(_class){
            this->name=new JString(name);
        }

        JPermission::JPermission(JClass* _class):JObject(_class){
            this->name=new JString("");
        }

        void JPermission::checkGuard(JObject*){
            //TODO
        }

        string JPermission::getName(){
            return name->getString();
        }

        JPermissionCollection* JPermission::newPermissionCollection(){
            return NULL;
        }

        string JPermission::toString(){
            string actions = getActions();
            if (actions.length() == 0) { // OPTIONAL
                return "(\"" + getClass()->getName() + "\" \"" + getName() + "\")";
            } else {
                return "(\"" + getClass()->getName() + "\" \"" + getName()+ "\" \"" + actions + "\")";
            }
        }

        JPermission::~JPermission(){
            if (name!=NULL){
                delete name;
            }
        }
    }
}