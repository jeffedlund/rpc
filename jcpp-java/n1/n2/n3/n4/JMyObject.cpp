//include declaration
#include "JMyObject.h"

//namespace declaration
namespace n1{
    namespace n2{
        namespace n3{
            namespace n4{

    class JMyObjectClass : public JClass{
        protected:

            //invocation of fields f1
            static JObject* staticGetf1(JObject* object){
                JMyObject* o=(JMyObject*)object;
                return o->getF1();
            }

            static void staticSetf1(JObject* obj,JObject* value){
                JMyObject* o=(JMyObject*)object;
                o->setF1((JR1*)value);
            }

            //invocation of fields f2
            static JObject* staticGetf2(JObject* object){
                JMyObject* o=(JMyObject*)object;
                return o->getF2();
            }

            static void staticSetf2(JObject* obj,JObject* value){
                JMyObject* o=(JMyObject*)object;
                o->setF2((JCollection*)value);
            }


        public:
            JMyObjectClass(){
                this->canonicalName="n1.n2.n3.n4.MyObject";
                this->name="n1.n2.n3.n4.MyObject";
                this->simpleName="MyObject";
                this->serialVersionUID=0ULL;

                //interfaces
                addInterface(JI1::getClazz());
                addInterface(JI2::getClazz());

                //fields
                addField(new JField("f1",JR1::getClazz(),this,staticGetf1,staticSetf1));
                addField(new JField("f2",JCollection::getClazz(),this,staticGetf2,staticSetf2));
            }

            JClass* getSuperclass(){
                return JMyParent::getClazz();
            }

            JObject* newInstance(){
                return new JMyObject();
            }
        };

        static JClass* clazz;

        JClass* JMyObject::getClazz(){
            if (clazz==NULL){
                clazz=new JMyObjectClass();
            }
            return clazz;
        }

        JMyObject(){
            //TODO
        }

        //field f1
        JR1* JMyObject::getF1(){
            return f1;
        }

        void JMyObject::setF1(JR1* f1){
            if (this->f1!=NULL){
                delete this->f1;
            }
            this->f1=f1;
        }

        //field f2
        JCollection* JMyObject::getF2(){
            return f2;
        }

        void JMyObject::setF2(JCollection* f2){
            if (this->f2!=NULL){
                delete this->f2;
            }
            this->f2=f2;
        }



        JMyObject::~JMyObject(){
            delete this->f1;
            delete this->f2;
        }

            }
        }
    }
}

//                