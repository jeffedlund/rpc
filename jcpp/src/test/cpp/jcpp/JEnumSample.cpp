#include "JEnumSample.h"
#include <sstream>
#include "JField.h"

namespace jcpp{
    static JObject* staticGetFieldString(JObject* object){
        JEnumSample* b=(JEnumSample*)object;
        return b->getFieldString();
    }

    static void staticSetFieldString(JObject* obj,JObject* value){
        JEnumSample* b=(JEnumSample*)obj;
        b->setFieldString((JString*)value);
    }

    JEnumSample::JEnumSampleClass::JEnumSampleClass():JEnumClass(){
        this->canonicalName="jcpp.EnumSample";
        this->name="jcpp.EnumSample";
        this->simpleName="EnumSample";
        addField(new JField("fieldString",JString::getClazz(),this,staticGetFieldString,staticSetFieldString));
    }

    JClass* JEnumSample::JEnumSampleClass::getSuperclass(){
        return JEnum::getClazz();
    }

    void JEnumSample::JEnumSampleClass::fillEnumConstants(){
        addEnumConstant(JEnumSample::E1);
        addEnumConstant(JEnumSample::E2);
        addEnumConstant(JEnumSample::E3);
        addEnumConstant(JEnumSample::E4);
        addEnumConstant(JEnumSample::E5);
    }

    static JClass* clazz;

    JClass* JEnumSample::getClazz(){
        if (clazz==NULL){
            clazz=new JEnumSampleClass();
        }
        return clazz;
    }

    JEnumSample::JEnumSample(JString* fieldString, JString* name, JPrimitiveInt* ordinal):JEnum((JEnumSampleClass*)getClazz(),name,ordinal){
        this->fieldString=fieldString;
    }

    JEnumSample* JEnumSample::E1 = new JEnumSample(new JString("E1"),new JString("E1"),new JPrimitiveInt(0));

    JEnumSample* JEnumSample::E2 = new JEnumSample(new JString("E2"),new JString("E2"),new JPrimitiveInt(1));

    JEnumSample* JEnumSample::E3 = new JEnumSample(new JString("E3"),new JString("E3"),new JPrimitiveInt(2));

    JEnumSample* JEnumSample::E4 = new JEnumSample(new JString("E4"),new JString("E4"),new JPrimitiveInt(3));

    JEnumSample* JEnumSample::E5 = new JEnumSample(new JString("E5"),new JString("E5"),new JPrimitiveInt(4));

    JString* JEnumSample::getFieldString(){
        return fieldString;
    }

    void JEnumSample::setFieldString(JString* fs){
        this->fieldString=fs;
    }

    string JEnumSample::toString(){
        string s=JEnum::toString();
        s=s+"[FieldString:"+fieldString->toString()+"]";
        return s;
    }

    JEnumSample::~JEnumSample(){
        delete fieldString;
    }
}
