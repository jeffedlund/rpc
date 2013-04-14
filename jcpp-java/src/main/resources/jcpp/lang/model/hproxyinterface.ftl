#ifndef ${ifndef}
#define ${ifndef}

//include declaration
<#list includes as include>
#include ${include}
</#list>
#include "JProxy.h"

//use namespace declaration
<#list namespaces as use>
using namespace ${use};
</#list>
using namespace jcpp::lang::reflect;

//namespace declaration
<#list namespace as ns>
${""?left_pad(ns_index*4)}namespace ${ns}{
</#list>

//class declaration
class ${className} : public JProxy <#list interfaces as interface> , public ${interface} </#list> {
	protected:
		class ${className}Class : public JProxyClass{
		public:
			${className}Class();
			virtual JClass* getSuperclass();
			virtual JObject* newInstance();
		};

	public:
		${className}();
		static JClass* getClazz();

		//methods declaration
		<#list methods as method>
		virtual ${method.returnType} <#if !method.getIsReturnTypeVoid()>*</#if> ${method.name}(<#list method.parameterType as param>${param}* p${param_index}<#if param_has_next>,</#if> </#list>);
										</#list>

		virtual ~${className}();

};
<#list namespace as ns>
${""?left_pad(((namespace?size - 1)-ns_index)*4)}}
</#list>

#endif // ${ifndef}
