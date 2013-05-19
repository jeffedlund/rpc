#include "JLogRecord.h"
#include "JClass.h"
#include "JSystem.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace logging{
            class JLogRecordClass : public JClass{
                protected:
                    static JObject* staticGetLevel(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->level;
                    }

                    static void staticSetLevel(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->level!=NULL){
                            delete lr->level;
                        }
                        lr->level=(JLevel*)value;
                    }

                    static JObject* staticGetSequenceNumber(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->sequenceNumber;
                    }

                    static void staticSetSequenceNumber(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->sequenceNumber!=NULL){
                            delete lr->sequenceNumber;
                        }
                        lr->sequenceNumber=(JPrimitiveLong*)value;
                    }

                    static JObject* staticGetsourceClassName(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->sourceClassName;
                    }

                    static void staticSetsourceClassName(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->sourceClassName!=NULL){
                            delete lr->sourceClassName;
                        }
                        lr->sourceClassName=(JString*)value;
                    }

                    static JObject* staticGetsourceMethodName(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->sourceMethodName;
                    }

                    static void staticSetsourceMethodName(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->sourceMethodName!=NULL){
                            delete lr->sourceMethodName;
                        }
                        lr->sourceMethodName=(JString*)value;
                    }

                    static JObject* staticGetmessage(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->message;
                    }

                    static void staticSetmessage(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->message!=NULL){
                            delete lr->message;
                        }
                        lr->message=(JString*)value;
                    }

                    static JObject* staticGetthreadID(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->threadID;
                    }

                    static void staticSetthreadID(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->threadID!=NULL){
                            delete lr->threadID;
                        }
                        lr->threadID=(JPrimitiveInt*)value;
                    }

                    static JObject* staticGetmillis(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->millis;
                    }

                    static void staticSetmillis(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->millis!=NULL){
                            delete lr->millis;
                        }
                        lr->millis=(JPrimitiveLong*)value;
                    }

                    static JObject* staticGetthrown(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->thrown;
                    }

                    static void staticSetthrown(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->thrown!=NULL){
                            delete lr->thrown;
                        }
                        lr->thrown=(JThrowable*)value;
                    }

                    static JObject* staticGetloggerName(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->loggerName;
                    }

                    static void staticSetloggerName(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->loggerName!=NULL){
                            delete lr->loggerName;
                        }
                        lr->loggerName=(JString*)value;
                    }

                    static JObject* staticGetresourceBundleName(JObject* object){
                        JLogRecord* lr=(JLogRecord*)object;
                        return lr->resourceBundleName;
                    }

                    static void staticSetresourceBundleName(JObject* object,JObject* value){
                        JLogRecord* lr=(JLogRecord*)object;
                        if (lr->resourceBundleName!=NULL){
                            delete lr->resourceBundleName;
                        }
                        lr->resourceBundleName=(JString*)value;
                    }

                public:
                    JLogRecordClass(){
                        this->canonicalName="java.util.logging.LogRecord";
                        this->name="java.util.logging.LogRecord";
                        this->simpleName="LogRecord";
                        this->serialVersionUID=5372048053134512534ULL;
                        addInterface(JSerializable::getClazz());
                        addField(new JField("level",JLevel::getClazz(),this,staticGetLevel,staticSetLevel));
                        addField(new JField("sequenceNumber",JPrimitiveLong::getClazz(),this,staticGetSequenceNumber,staticSetSequenceNumber));
                        addField(new JField("sourceClassName",JString::getClazz(),this,staticGetsourceClassName,staticSetsourceClassName));
                        addField(new JField("sourceMethodName",JString::getClazz(),this,staticGetsourceMethodName,staticSetsourceMethodName));
                        addField(new JField("message",JString::getClazz(),this,staticGetmessage,staticSetmessage));
                        addField(new JField("threadID",JPrimitiveInt::getClazz(),this,staticGetthreadID,staticSetthreadID));
                        addField(new JField("millis",JPrimitiveLong::getClazz(),this,staticGetmillis,staticSetmillis));
                        addField(new JField("thrown",JThrowable::getClazz(),this,staticGetthrown,staticSetthrown));
                        addField(new JField("loggerName",JString::getClazz(),this,staticGetloggerName,staticSetloggerName));
                        addField(new JField("resourceBundleName",JString::getClazz(),this,staticGetresourceBundleName,staticSetresourceBundleName));
                    }

                    JClass* getSuperclass(){
                        return JObject::getClazz();
                    }

                    JObject* newInstance(){
                        return new JLogRecord();
                    }
            };

            static JClass* clazz;

            JClass* JLogRecord::getClazz(){
                if (clazz==NULL){
                    clazz=new JLogRecordClass();
                }
                return clazz;
            }

            JLogRecord::JLogRecord():JObject(getClazz()){
                level=NULL;
                sequenceNumber=NULL;
                sourceClassName=NULL;
                sourceMethodName=NULL;
                message=NULL;
                threadID=NULL;
                millis=NULL;
                thrown=NULL;
                loggerName=NULL;
                resourceBundleName=NULL;
                parameters=NULL;
            }

            static jlong staticSN = 0;
            static jlong nextStaticSN(){
                JLogRecord::getClazz()->lock();
                staticSN++;
                jlong i=staticSN;
                JLogRecord::getClazz()->unlock();
                return i;
            }

            JLogRecord::JLogRecord(JLevel* level,JString message):JObject(getClazz()){
                this->level=level;
                this->message=new JString(message);
                this->threadID=new JPrimitiveInt();//TODO
                this->millis=new JPrimitiveLong(JSystem::currentTimeMillis());
                this->sequenceNumber=new JPrimitiveLong(nextStaticSN());
                sourceClassName=NULL;
                sourceMethodName=NULL;
                thrown=NULL;
                loggerName=NULL;
                resourceBundleName=NULL;
                parameters=NULL;
            }

            JString* JLogRecord::getLoggerName(){
                return loggerName;
            }

            void JLogRecord::setLoggerName(JString name){
                if (loggerName!=NULL){
                    delete loggerName;
                }
                loggerName=new JString(name);
            }

            JLevel* JLogRecord::getLevel(){
                return level;
            }

            void JLogRecord::setLevel(JLevel* level){
                this->level=level;
            }

            jlong JLogRecord::getSequenceNumber(){
                return sequenceNumber->get();
            }

            void JLogRecord::setSequenceNumber(jlong nb){
                sequenceNumber->set(nb);
            }

            JString* JLogRecord::getSourceClassName(){
                return sourceClassName;
            }

            void JLogRecord::setSourceClassName(JString name){
                if (sourceClassName!=NULL){
                    delete sourceClassName;
                }
                this->sourceClassName=new JString(name);
            }

            JString* JLogRecord::getSourceMethodName(){
                return sourceMethodName;
            }

            void JLogRecord::setSourceMethodName(JString name){
                if (sourceMethodName!=NULL){
                    delete sourceMethodName;
                }
                this->sourceMethodName=new JString(name);
            }

            JString* JLogRecord::getMessage(){
                return message;
            }

            void JLogRecord::setMessage(JString name){
                if (message!=NULL){
                    delete message;
                }
                this->message=new JString(name);
            }

            JPrimitiveArray* JLogRecord::getParameters(){
                return parameters;
            }

            void JLogRecord::setParameters(JPrimitiveArray* a){
                this->parameters=a;
            }

            jint JLogRecord::getThreadID(){
                return threadID->get();
            }

            void JLogRecord::setThreadID(jint id){
                threadID->set(id);
            }

            jlong JLogRecord::getMillis(){
                return millis->get();
            }

            void JLogRecord::setMillis(jlong m){
                millis->set(m);
            }

            JThrowable* JLogRecord::getThrown(){
                return thrown;
            }

            void JLogRecord::setThrown(JThrowable* th){
                thrown=th;
            }

            void JLogRecord::writeObject(JObjectOutputStream* out){
                out->defaultWriteObject();
                out->writeByte(1);
                out->writeByte(0);
                if (parameters == NULL) {
                    out->writeInt(-1);
                    return;
                }
                out->writeInt(parameters->size());
                for (int i = 0; i < parameters->size(); i++) {
                    if (parameters->get(i) == NULL) {
                        out->writeObject(NULL);
                    } else {
                        JString str=parameters->get(i)->toString();
                        out->writeObject(&str);
                    }
                }
            }

            void JLogRecord::readObject(JObjectInputStream* in){
                in->defaultReadObject();

                jbyte major = in->readByte();
                jbyte minor = in->readByte();
                if (major != 1) {
                    JString ss("LogRecord: bad version: ");
                    ss<<major<<"."<<minor;
                    throw new JIOException(ss);
                }
                jint len = in->readInt();
                if (len == -1) {
                    parameters = NULL;
                } else {
                    parameters = new JPrimitiveArray(JObject::getClazz(),len);
                    for (int i = 0; i < parameters->size(); i++) {
                        parameters->set(i,in->readObject());
                    }
                }
            }

            JLogRecord::~JLogRecord(){
                if (sequenceNumber!=NULL){
                    delete sequenceNumber;
                }
                if (sourceClassName!=NULL){
                    delete sourceClassName;
                }
                if (sourceMethodName!=NULL){
                    delete sourceMethodName;
                }
                if (message!=NULL){
                    delete message;
                }
                if (threadID!=NULL){
                    delete threadID;
                }
                if (millis!=NULL){
                    delete millis;
                }
                if (loggerName!=NULL){
                    delete loggerName;
                }
                if (resourceBundleName!=NULL){
                    delete resourceBundleName;
                }
            }
        }
    }
}

