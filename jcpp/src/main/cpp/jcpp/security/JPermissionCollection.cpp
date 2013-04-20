#include "JPermissionCollection.h"
#include "JClass.h"
#include "JEnumeration.h"
#include "JStringBuilder.h"

using namespace jcpp::util;

namespace jcpp{
    namespace security{
        class JPermissionCollectionClass : public JClass{
            protected:
                static JObject* staticGetReadonly(JObject* object){
                    JPermissionCollection* pc=(JPermissionCollection*)object;
                    return pc->readOnly;
                }

                static void staticSetName(JObject* object,JObject* value){
                    JPermissionCollection* pc=(JPermissionCollection*)object;
                    delete pc->readOnly;
                    pc->readOnly=(JPrimitiveBoolean*)value;
                }

            public:
                JPermissionCollectionClass(){
                    this->canonicalName="java.security.PermissionCollection";
                    this->name="java.security.PermissionCollection";
                    this->simpleName="PermissionCollection";
                    this->serialVersionUID=-6727011328946861783ULL;
                    addInterface(JSerializable::getClazz());
                    addField(new JField("readOnly",JPrimitiveBoolean::getClazz(),this,staticGetReadonly,staticSetName));
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JPermissionCollection::getClazz(){
            if (clazz==NULL){
                clazz=new JPermissionCollectionClass();
            }
            return clazz;
        }

        JPermissionCollection::JPermissionCollection(JClass* _class):JObject(_class){
            this->readOnly=new JPrimitiveBoolean(false);
        }

        void JPermissionCollection::setReadOnly(){
            readOnly->set(true);
        }

        jbool JPermissionCollection::isReadOnly(){
            return readOnly->get();
        }

        string JPermissionCollection::toString(){
            JEnumeration* enum_ = elements();
            JStringBuilder* sb = new JStringBuilder();
            sb->append(JObject::toString()+" (\n");
            while (enum_->hasMoreElements()) {
                sb->append(" ");
                sb->append(enum_->nextElement()->toString());
                sb->append("\n");
            }
            sb->append(")\n");
            string s=sb->toString();
            delete enum_;
            delete sb;
            return s;
        }

        JPermissionCollection::~JPermissionCollection(){
            delete readOnly;
        }
    }
}
