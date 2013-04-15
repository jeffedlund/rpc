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
class ${className} : public ${parent} <#list interfaces as i> , public ${i} </#list> {
	protected:
		<#list fields as field>
		${field.type}* ${field.name};
		</#list>
		friend class ${className}Class;
	
	public:
		static JClass* getClazz();
		${className}();

		<#list fields as field>
		//field ${field.name}
		${field.type}* ${field.getter}();
		void ${field.setter}(${field.type}* ${field.name});

		</#list>


		<#list methods as method>
		//method ${method.name}
		virtual ${method.returnType} <#if !method.getIsReturnTypeVoid()>*</#if> ${method.name}(<#list method.parameterType as param>${param}* p${param_index}<#if param_has_next>,</#if> </#list>);
		</#list>

		virtual ~${className}();

};
<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

#endif // ${ifndef}

//${""?left_pad((namespace?size)*4)}