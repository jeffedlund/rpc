//include declaration
#include "${className}.h"

//namespace declaration
<#list namespace as ns>
${""?left_pad(ns_index*4)}namespace ${ns}{
</#list>

	<#list methods as method>
		static JObject* invoke${method.name}(JObject* object,vector<JObject*>* args){
			${className}* o=dynamic_cast<${className}*>(object);
			<#list method.parameterType as param>
			${param}* p${param_index} = dynamic_cast<${param}*>(args->at(${param_index}));
			</#list>
			<#if !method.getIsReturnTypeVoid()>JObject* result=</#if>o->${method.name}(<#list method.parameterType as param>p${param_index}<#if param_has_next>,</#if></#list>);
			<#if !method.getIsReturnTypeVoid()>return result;<#else>return NULL;</#if>
		}

	</#list>

	class ${className}Class : public JClass{
	public:
		${className}Class(){
			this->canonicalName="${canonicalName}";
            this->name="${name}";
            this->simpleName="${simpleName}";
            this->bIsInterface=true;

            <#list methods as method>
        	vector<JClass*>* param${method.name}=new vector<JClass*>();
        	<#list method.parameterType as ptype>
        	param${method.name}->push_back(${ptype}::getClazz());
        	</#list>
        	addMethod(new JMethod("${method.name}",this,${method.returnType}::getClazz(),param${method.name},invoke${method.name}));

            </#list>
		}

		JClass* getSuperclass(){
            return ${parent}::getClazz();
        }
    };
	
	static JClass* clazz;

    JClass* ${className}::getClazz(){
        if (clazz==NULL){
            clazz=new ${className}Class();
        }
        return clazz;
    }

    ${className}::~${className}(){
    }

<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

//${""?left_pad((namespace?size)*4)}