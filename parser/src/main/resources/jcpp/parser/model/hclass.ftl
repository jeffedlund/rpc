#ifndef ${class.ifndef}
#define ${class.ifndef}

//include declaration
<#list class.includes as include>
#include ${include}
</#list>
#include "JObject.h"

//use namespace declaration
<#list class.useNamespace as use>
using namespace ${use};
</#list>


//namespace declaration
<#list class.namespace as ns>
namespace ${ns}{
</#list>

//class declaration
class ${class.className} : public ${class.parentClass} <#list class.interfaces as interface> , public ${interface} </#list> {
	protected:
		//field declaration
		<#list class.declaredFields as field>
		${field.type}* ${field.name};
		</#list>

		//constructor
		${class.className}(JClass* clazz);
	
	public:
		//default constructor
		${class.className}();
		static JClass* getClazz();

		//fields declaration

		<#list class.declaredFields as field>
		//field ${field.name}
		virtual ${field.type}* ${field.getter}();
		virtual void ${field.setter}(${field.type}* ${field.name});

		</#list>


		//methods declaration

		<#list class.declaredMethods as method>
		//method ${method.name}
		//TODO return type can be void or a pointer to a JObject
		virtual ${method.returnType}* ${method.name}(<#list method.parameterType as param>${param}*, </#list>)=0; //TODO bug with comma

		</#list>

		virtual string toString();

		virtual ~${class.className}();

};

<#list class.namespace as ns>
}
</#list>

#endif // ${class.ifndef}
