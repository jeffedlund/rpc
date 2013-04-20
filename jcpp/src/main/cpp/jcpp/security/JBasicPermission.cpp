#include "JBasicPermission.h"
#include "JClass.h"

namespace jcpp{
    namespace security{
        class JBasicPermissionClass : public JClass{
            protected:
                static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                    JBasicPermission* bp=(JBasicPermission*)object;
                    bp->readObject((JObjectInputStream*)args->at(0));
                    return NULL;
                }

            public:
                JBasicPermissionClass(){
                    this->canonicalName="java.security.BasicPermission";
                    this->name="java.security.BasicPermission";
                    this->simpleName="BasicPermission";
                    this->serialVersionUID=6279438298436773498ULL;
                    addInterface(JSerializable::getClazz());

                    vector<JClass*>* paramType=new vector<JClass*>();
                    paramType->push_back(JObjectInputStream::getClazz());
                    addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));
                }

                JClass* getSuperclass(){
                    return JPermission::getClazz();
                }

                JObject* newInstance(){
                    return new JBasicPermission();
                }
        };

        static JClass* clazz;

        JClass* JBasicPermission::getClazz(){
            if (clazz==NULL){
                clazz=new JBasicPermissionClass();
            }
            return clazz;
        }

        JBasicPermission::JBasicPermission(JClass* _class):JPermission(_class){
        }

        JBasicPermission::JBasicPermission(JClass* _class,string name):JPermission(_class,name){
            init(name);
        }

        JBasicPermission::JBasicPermission(string name):JPermission(getClazz(),name){
            init(name);
        }

        JBasicPermission::JBasicPermission():JPermission(getClazz(),""){
        }

        void JBasicPermission::init(string name){
            jint len = name.length();
            if (len == 0) {
                throw new JIllegalArgumentException("name can't be empty");
            }
            jchar last = (jchar)name.at(len - 1);

            if (last == '*' && (len == 1 || name.at(len - 2) == '.')) {
                wildcard = true;
                if (len == 1) {
                    path = "";
                } else {
                    path = name.substr(0, len - 1);
                }
            } else {
                if (name=="exitVM") {
                    wildcard = true;
                    path = "exitVM.";
                    exitVM = true;
                } else {
                    path = name;
                }
            }
        }

        string JBasicPermission::getCanonicalName(){
            return exitVM ? "exitVM.*" : getName();
        }

        jbool JBasicPermission::implies(JPermission* permission){
            if ((permission == NULL) || (permission->getClass() != getClass())){
                return false;
            }

            JBasicPermission* that = (JBasicPermission*) permission;

            if (this->wildcard) {
                if (that->wildcard) {
                    return false;//TODO that->path.startsWith(path);
                } else {
                    return (that->path.length() > this->path.length());//TODO  && that->path.startsWith(this->path);
                }
            } else {
                if (that->wildcard) {
                    return false;
                }else {
                    return this->path==that->path;
                }
            }
        }

        jbool JBasicPermission::equals(JObject* object){
            if (object == this){
                return true;
            }
            if ((object == NULL) || (object->getClass() != getClass())){
                return false;
            }
            JBasicPermission* bp = (JBasicPermission*) object;
            return getName()==bp->getName();
        }

        jint JBasicPermission::hashCode(){
            return JString::hashCode(getName());
        }

        string JBasicPermission::getActions(){
            return "";
        }

        JPermissionCollection* JBasicPermission::newPermissionCollection(){
            return NULL;//TODO new JBasicPermissionCollection(getClass());
        }

        void JBasicPermission::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            init(getName());
        }

        JBasicPermission::~JBasicPermission(){
        }
    }
}
