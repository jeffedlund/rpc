//include declaration
#include "${className}.h"

//namespace declaration
<#list namespace as ns>
${""?left_pad(ns_index*4)}namespace ${ns}{
</#list>

    class ${className}Class : public JClass{
        protected:

            <#list fields as field>
            //invocation of fields ${field.name}
            static JObject* staticGet${field.name}(JObject* object){
                ${className}* o=(${className}*)object;
                return o->${field.getter}();
            }

            static void staticSet${field.name}(JObject* obj,JObject* value){
                ${className}* o=(${className}*)object;
                o->${field.setter}((${field.type}*)value);
            }

            </#list>

        public:
            ${className}Class(){
                this->canonicalName="${canonicalName}";
                this->name="${name}";
                this->simpleName="${simpleName}";
                this->serialVersionUID=${serialVersionUID}ULL;

                //interfaces
                <#list interfaces as i>
                addInterface(${i}::getClazz());
                </#list>

                //fields
                <#list fields as field>
                addField(new JField("${field.name}",${field.type}::getClazz(),this,staticGet${field.name},staticSet${field.name}));
                </#list>
            }

            JClass* getSuperclass(){
                return ${parent}::getClazz();
            }

            JObject* newInstance(){
                return new ${className}();
            }
        };

        static JClass* clazz;

        JClass* ${className}::getClazz(){
            if (clazz==NULL){
                clazz=new ${className}Class();
            }
            return clazz;
        }

        ${className}(){
            //TODO
        }

        <#list fields as field>
        //field ${field.name}
        ${field.type}* ${className}::${field.getter}(){
            return ${field.name};
        }

        void ${className}::${field.setter}(${field.type}* ${field.name}){
            if (this->${field.name}!=NULL){
                delete this->${field.name};
            }
            this->${field.name}=${field.name};
        }

        </#list>

        ${className}::~${className}(){
            <#list fields as field>
            delete this->${field.name};
            </#list>
        }

<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

//${""?left_pad((namespace?size)*4)}