//include declaration
#include "${className}.h"

//namespace declaration
<#list namespace as ns>
${""?left_pad(ns_index*4)}namespace ${ns}{
</#list>

        ${className}::${className}Class::${className}Class():JProxyClass(){
            this->canonicalName="${canonicalName}";
            this->name="${name}";
            this->simpleName="${simpleName}";
            this->bIsProxy=true;
            addInterface(${interfaces[0]}::getClazz());
        }

        JClass* ${className}::${className}Class::getSuperclass(){
            return JProxy::getClazz();
        }

        JObject* ${className}::${className}Class::newInstance(){
            return new ${className}();
        }

        static JClass* clazz;

        JClass* ${className}::getClazz(){
            if (clazz==NULL){
                clazz=new ${className}Class();
            }
            return clazz;
        }

        ${className}::${className}():JProxy(getClazz()){
        }

	   <#list methods as method>
            ${method.returnType} ${className}::${method.name}(<#list method.parameterType as param>${param}* p${param_index}<#if param_has_next>,</#if> </#list>){
                vector<JObject*> args;
                <#list method.parameterType as param>
                args.push_back(p${param_index});
                </#list>
                <#if !method.getIsReturnTypeVoid()>${method.returnType}* r=</#if>invoke("${method.name}",&args);
                return <#if !method.getIsReturnTypeVoid()>r<#else>NULL</#if>;
            }
    	</#list>

        ${className}::~${className}(){
        }

<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

//${""?left_pad((namespace?size)*4)}