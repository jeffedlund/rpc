#include "${class.className}.h"
#include "JClass.h"
#include "JInstantiationException.h"
<#list class.includes as include>
#include ${include}
</#list>

//use namespace declaration
<#list class.useNamespace as use>
using namespace ${use};
</#list>


//namespace declaration
<#list class.namespace as ns>
namespace ${ns}{
</#list>

	//static field access declaration
	<#list class.declaredFields as field>
		//static access to field ${field.name}
		static JObject* staticGet${field.name}(JObject* object){
            ${class.className}* o=(${class.className}*)object;
            return o->${field.getter}();
        }

        static void staticSet${field.name}(JObject* object,JObject* value){
            ${class.className}* o=(${class.className}*)object;
            o->${field.setter}((${field.type}*)value);
        }

    </#list>

    class ${class.className}Class : public JClass{
    public:
        ${class.className}Class():JClass(JClassLoader::getBootClassLoader()){
            canonicalName="${class.canonicalName}";
            name="${class.name}";
            simpleName="${class.simpleName}";

            <#list class.declaredFields as field>
			this->addField(new JField("${field.name}",${field.type}::getClazz(),staticGet${field.name},staticSet${field.name}));
			</#list>

            <#list class.interfaces as interface>
			addInterface(${interface}::getClazz());
			</#list>
        }

        JClass* getSuperclass(){
            return ${class.parentClass}::getClazz();
        }

        JObject* newInstance(){
            throw new JInstantiationException("cannot instantiate object of class "+getName());
        }
    };

    static JClass* clazz;

    JClass* ${class.className}::getClazz(){
        if (clazz==NULL){
            clazz= new ${class.className}Class();
        }
        return clazz;
    }

    ${class.className}::${class.className}(JClass* clazz):${class.parentClass}(clazz){
		<#list class.declaredFields as field>
			this->${field.name}=NULL;
		</#list>
    }

    ${class.className}::${class.className}():${class.parentClass}(getClazz()){
		<#list class.declaredFields as field>
			this->${field.name}=NULL;
		</#list>
    }

	//field declaration

	<#list class.declaredFields as field>
	//field ${field.name}
	${field.type}* ${class.className}::${field.getter}(){
		return ${field.name};
	}

	void ${class.className}::${field.setter}(${field.type}* ${field.name}){
		delete this->${field.name};
		this->${field.name}=${field.name};
	}

	</#list>


    ${class.className}::~${class.className}(){
		<#list class.declaredFields as field>
			delete ${field.name};
		</#list>
    }

<#list class.namespace as ns>
}
</#list>
