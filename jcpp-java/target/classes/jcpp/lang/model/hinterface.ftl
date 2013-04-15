#ifndef ${ifndef}
#define ${ifndef}

//include declaration
<#list includes as include>
#include ${include}
</#list>

//use namespace declaration
<#list namespaces as use>
using namespace ${use};
</#list>

//namespace declaration
<#list namespace as ns>
${""?left_pad(ns_index*4)}namespace ${ns}{
</#list>

//class declaration
class ${className} : public ${parent} <#list interfaces as interface> , public ${interface} </#list> {
	
	public:
		static JClass* getClazz();

		//methods declaration
		<#list methods as method>
		virtual ${method.returnType} <#if !method.getIsReturnTypeVoid()>*</#if> ${method.name}(<#list method.parameterType as param>${param}* <#if param_has_next>,</#if> </#list>)=0;
		</#list>

		virtual ~${className}();

};
<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

#endif // ${ifndef}

//${""?left_pad((namespace?size)*4)}