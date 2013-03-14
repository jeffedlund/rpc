#include "JMyClass.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "inc1.h"
#include "inc2.h"
#include "inc3.h"

//use namespace declaration
using namespace use_n1;
using namespace use_n2;
using namespace use_n3;


//namespace declaration
namespace n1{
namespace n2{
namespace n3{

	//static field access declaration
		//static access to field f1
		static JObject* staticGetf1(JObject* object){
            JMyClass* o=(JMyClass*)object;
            return o->getF1();
        }

        static void staticSetf1(JObject* object,JObject* value){
            JMyClass* o=(JMyClass*)object;
            o->setF1((t1*)value);
        }

		//static access to field f2
		static JObject* staticGetf2(JObject* object){
            JMyClass* o=(JMyClass*)object;
            return o->getF2();
        }

        static void staticSetf2(JObject* object,JObject* value){
            JMyClass* o=(JMyClass*)object;
            o->setF2((t2*)value);
        }

		//static access to field f3
		static JObject* staticGetf3(JObject* object){
            JMyClass* o=(JMyClass*)object;
            return o->getF3();
        }

        static void staticSetf3(JObject* object,JObject* value){
            JMyClass* o=(JMyClass*)object;
            o->setF3((t3*)value);
        }


    class JMyClassClass : public JClass{
    public:
        JMyClassClass():JClass(JClassLoader::getBootClassLoader()){
            canonicalName="n1.n2.n3.JMyClass";
            name="n1.n2.n3.JMyClass";
            simpleName="JMyClass";
            serialVersionUID=11,111ULL;

			this->addField(new JField("f1",t1::getClazz(),staticGetf1,staticSetf1));
			this->addField(new JField("f2",t2::getClazz(),staticGetf2,staticSetf2));
			this->addField(new JField("f3",t3::getClazz(),staticGetf3,staticSetf3));

			addInterface(JI1::getClazz());
			addInterface(JI2::getClazz());
			addInterface(JI3::getClazz());
        }

        JClass* getSuperclass(){
            return JParentClass::getClazz();
        }

        JObject* newInstance(){
            throw new JInstantiationException("cannot instantiate object of class "+getName());
        }
    };

    static JClass* clazz;

    JClass* JMyClass::getClazz(){
        if (clazz==NULL){
            clazz= new JMyClassClass();
        }
        return clazz;
    }

    JMyClass::JMyClass(JClass* clazz):JParentClass(clazz){
			this->f1=NULL;
			this->f2=NULL;
			this->f3=NULL;
    }

    JMyClass::JMyClass():JParentClass(getClazz()){
			this->f1=NULL;
			this->f2=NULL;
			this->f3=NULL;
    }

	//field declaration

	//field f1
	t1* JMyClass::getF1(){
		return f1;
	}

	void JMyClass::setF1(t1* f1){
		delete this->f1;
		this->f1=f1;
	}

	//field f2
	t2* JMyClass::getF2(){
		return f2;
	}

	void JMyClass::setF2(t2* f2){
		delete this->f2;
		this->f2=f2;
	}

	//field f3
	t3* JMyClass::getF3(){
		return f3;
	}

	void JMyClass::setF3(t3* f3){
		delete this->f3;
		this->f3=f3;
	}


	string JMyClass::toString(){
		string str="";
		if (f1!=NULL){
			str+="[f1="+f1->toString()+"]";
		}
		if (f2!=NULL){
			str+="[f2="+f2->toString()+"]";
		}
		if (f3!=NULL){
			str+="[f3="+f3->toString()+"]";
		}
		return str;
	}


    JMyClass::~JMyClass(){
			delete f1;
			delete f2;
			delete f3;
    }

}
}
}
