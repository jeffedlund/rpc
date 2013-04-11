//include declaration
#include "JMyInterface.h"

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

		static JObject* invokem1(JObject* object,vector<JObject*>* args){
			JMyInterface* o=dynamic_cast<JMyInterface*>(object);
			JP1* p0 = dynamic_cast<JP1*>(args->at(0));
			JP2* p1 = dynamic_cast<JP2*>(args->at(1));
			o->m1(p0,p1);
			return NULL;
		}

		static JObject* invokem2(JObject* object,vector<JObject*>* args){
			JMyInterface* o=dynamic_cast<JMyInterface*>(object);
			JP1* p0 = dynamic_cast<JP1*>(args->at(0));
			JP2* p1 = dynamic_cast<JP2*>(args->at(1));
			JObject* result=o->m2(p0,p1);
			return result;
		}


	class JMyInterfaceClass : public JClass{
	public:
		JMyInterfaceClass(){
			this->canonicalName="n1.n2.n3.n4.MyInterface";
            this->name="n1.n2.n3.n4.MyInterface";
            this->simpleName="MyInterface";
            this->bIsInterface=true;

        	vector<JClass*>* paramm1=new vector<JClass*>();
        	paramm1->push_back(JP1::getClazz());
        	paramm1->push_back(JP2::getClazz());
        	addMethod(new JMethod("m1",this,void::getClazz(),paramm1,invokem1));

        	vector<JClass*>* paramm2=new vector<JClass*>();
        	paramm2->push_back(JP1::getClazz());
        	paramm2->push_back(JP2::getClazz());
        	addMethod(new JMethod("m2",this,JR1::getClazz(),paramm2,invokem2));

		}

		JClass* getSuperclass(){
            return JMyParent::getClazz();
        }
    };
	
	static JClass* clazz;

    JClass* JMyInterface::getClazz(){
        if (clazz==NULL){
            clazz=new JMyInterfaceClass();
        }
        return clazz;
    }

    JMyInterface::~JMyInterface(){
    }

            }
        }
    }
}

//                