#include "JStackTraceElement.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "JSerializable.h"
#include "JPrimitiveInt.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JStackTraceElementClass : public JClass{
            protected:
                static JObject* staticGetDeclaringClass(JObject* object){
                    JStackTraceElement* e=(JStackTraceElement*)object;
                    return e->getDeclaringClass();
                }

                static void staticSetDeclaringClass(JObject* object,JObject* value){
                    JStackTraceElement* th=(JStackTraceElement*)object;
                    th->setDeclaringClass((JString*)value);
                }

                static JObject* getMethodName(JObject* object){
                    JStackTraceElement* e=(JStackTraceElement*)object;
                    return e->getMethodName();
                }

                static void setMethodName(JObject* object,JObject* value){
                    JStackTraceElement* th=(JStackTraceElement*)object;
                    th->setMethodName((JString*)value);
                }

                static JObject* getFileName(JObject* object){
                    JStackTraceElement* e=(JStackTraceElement*)object;
                    return e->getFileName();
                }

                static void setFileName(JObject* object,JObject* value){
                    JStackTraceElement* th=(JStackTraceElement*)object;
                    th->setFileName((JString*)value);
                }

                static JObject* getLineNumber(JObject* object){
                    JStackTraceElement* e=(JStackTraceElement*)object;
                    return e->getPLineNumber();
                }

                static void setLineNumber(JObject* object,JObject* value){
                    JStackTraceElement* th=(JStackTraceElement*)object;
                    th->setPLineNumber((JPrimitiveInt*)value);
                }
          public:
            JStackTraceElementClass():JClass(){
                this->canonicalName="java.lang.StackTraceElement";
                this->name="java.lang.StackTraceElement";
                this->simpleName="StackTraceElement";
                this->serialVersionUID=6992337162326171013ULL;
                addField(new JField("declaringClass",JString::getClazz(),this,staticGetDeclaringClass,staticSetDeclaringClass));
                addField(new JField("methodName",JString::getClazz(),this,getMethodName,setMethodName));
                addField(new JField("fileName",JString::getClazz(),this,getFileName,setFileName));
                addField(new JField("lineNumber",JPrimitiveInt::getClazz(),this,getLineNumber,setLineNumber));
                addInterface(JSerializable::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JStackTraceElement();
            }
        };

        static JClass* clazz;

        JClass* JStackTraceElement::getClazz(){
            if (clazz==NULL){
                clazz=new JStackTraceElementClass();
            }
            return clazz;
        }

        JStackTraceElement::JStackTraceElement():JObject(getClazz()){
            declaringClass=NULL;
            methodName=NULL;
            fileName=NULL;
            lineNumber=NULL;
        }

        JStackTraceElement::JStackTraceElement(JString declaringClass,JString methodName,JString fileName,jint lineNumber):JObject(getClazz()){
            this->declaringClass=new JString(declaringClass);
            this->methodName=new JString(methodName);
            this->fileName=new JString(fileName);
            this->lineNumber=new JPrimitiveInt(lineNumber);
        }

        jbool JStackTraceElement::equals(JObject* other){
            if (other->getClass()!=JStackTraceElement::getClazz()){
                return false;
            }
            JStackTraceElement* se=dynamic_cast<JStackTraceElement*>(other);
            bool eq=true;
            if (se->declaringClass!=NULL && declaringClass!=NULL){
                eq=((*se->declaringClass)==(*declaringClass));
            }else{
                eq=se->declaringClass==NULL && declaringClass==NULL;
            }
            if (!eq){
                return false;
            }
            if (se->methodName!=NULL && methodName!=NULL){
                eq=((*se->methodName)==(*methodName));
            }else{
                eq=se->methodName==NULL && methodName==NULL;
            }
            if (!eq){
                return false;
            }
            if (se->fileName!=NULL && fileName!=NULL){
                eq=((*se->fileName)==(*fileName));
            }else{
                eq=se->fileName==NULL && fileName==NULL;
            }
            if (!eq){
                return false;
            }
            if (se->lineNumber!=NULL && lineNumber!=NULL){
                eq=((*se->lineNumber)==(*lineNumber));
            }else{
                eq=se->lineNumber==NULL && lineNumber==NULL;
            }
            if (!eq){
                return false;
            }else{
                return true;
            }
        }

        JString* JStackTraceElement::getDeclaringClass(){
            return declaringClass;
        }

        void JStackTraceElement::setDeclaringClass(JString* declaringClass){
            if (this->declaringClass!=NULL){
                delete this->declaringClass;
            }
            this->declaringClass=declaringClass;
        }

        JString* JStackTraceElement::getMethodName(){
            return methodName;
        }

        void JStackTraceElement::setMethodName(JString* methodName){
            if (this->methodName!=NULL){
                delete this->methodName;
            }
            this->methodName=methodName;
        }

        JString* JStackTraceElement::getFileName(){
            return fileName;
        }

        void JStackTraceElement::setFileName(JString* fileName){
            if (this->fileName!=NULL){
                delete this->fileName;
            }
            this->fileName=fileName;
        }

        JPrimitiveInt* JStackTraceElement::getPLineNumber(){
            return lineNumber;
        }

        void JStackTraceElement::setPLineNumber(JPrimitiveInt* lineNumber){
            if (this->lineNumber!=NULL){
                delete this->lineNumber;
            }
            this->lineNumber=lineNumber;
        }

        jint JStackTraceElement::getLineNumber(){
            return lineNumber->get();
        }

        void JStackTraceElement::setLineNumber(jint lineNumber){
            this->lineNumber->set(lineNumber);
        }

        jint JStackTraceElement::hashCode(){
            jint result = 31*declaringClass->hashCode() + methodName->hashCode();
            result = 31*result + fileName->hashCode();
            result = 31*result + lineNumber->hashCode();
            return result;
        }

        JString JStackTraceElement::toString(){
            JString ss;
            ss<<getDeclaringClass()->getString()<<"."<<getMethodName()->getString();
            ss<<"("<<getFileName()->getString()<<":"<<getPLineNumber()->toString()<<")";
            return ss;
        }

        JStackTraceElement::~JStackTraceElement(){
            delete declaringClass;
            delete methodName;
            delete fileName;
            delete lineNumber;
        }
    }
}

