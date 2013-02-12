#include "JStackTraceElement.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "JSerializable.h"
#include "JPrimitiveInt.h"
using namespace std;

namespace jcpp{
    namespace lang{
        static JObject* getDeclaringClass(JObject* object){
            JStackTraceElement* e=(JStackTraceElement*)object;
            return e->getDeclaringClass();
        }

        static void setDeclaringClass(JObject* object,JObject* value){
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
            return e->getLineNumber();
        }

        static void setLineNumber(JObject* object,JObject* value){
            JStackTraceElement* th=(JStackTraceElement*)object;
            th->setLineNumber((JPrimitiveInt*)value);
        }

        class JStackTraceElementClass : public JClass{
          public:
            JStackTraceElementClass():JClass(){
                this->canonicalName="java.lang.StackTraceElement";
                this->name="java.lang.StackTraceElement";
                this->simpleName="StackTraceElement";
                this->serialVersionUID=6992337162326171013ULL;
                addField(new JField("declaringClass",JString::getClazz(),getDeclaringClass,setDeclaringClass));
                addField(new JField("methodName",JString::getClazz(),getMethodName,setMethodName));
                addField(new JField("fileName",JString::getClazz(),getFileName,setFileName));
                addField(new JField("lineNumber",JPrimitiveInt::getClazz(),getLineNumber,setLineNumber));
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
        }

        JStackTraceElement::JStackTraceElement(JString* declaringClass,JString* methodName,JString* fileName,JPrimitiveInt* lineNumber):JObject(getClazz()){
            this->declaringClass=declaringClass;
            this->methodName=methodName;
            this->fileName=fileName;
            this->lineNumber=lineNumber;
        }

        bool JStackTraceElement::operator==(JObject &other){
            if (other.getClass()!=JStackTraceElement::getClazz()){
                return false;
            }
            JStackTraceElement* se=dynamic_cast<JStackTraceElement*>(&other);
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
            this->declaringClass=declaringClass;
        }

        JString* JStackTraceElement::getMethodName(){
            return methodName;
        }

        void JStackTraceElement::setMethodName(JString* methodName){
            this->methodName=methodName;
        }

        JString* JStackTraceElement::getFileName(){
            return fileName;
        }

        void JStackTraceElement::setFileName(JString* fileName){
            this->fileName=fileName;
        }

        JPrimitiveInt* JStackTraceElement::getLineNumber(){
            return lineNumber;
        }

        void JStackTraceElement::setLineNumber(JPrimitiveInt* lineNumber){
            this->lineNumber=lineNumber;
        }

        string JStackTraceElement::toString(){
            stringstream ss;
            ss<<getDeclaringClass()->getString()<<"."<<getMethodName()->getString();
            ss<<"("<<getFileName()->getString()<<":"<<getLineNumber()->toString()<<")";
            return ss.str();
        }

        JStackTraceElement::~JStackTraceElement(){
            delete declaringClass;
            delete methodName;
            delete fileName;
            delete lineNumber;
        }
    }
}

