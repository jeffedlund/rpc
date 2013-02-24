#include "JMethodDigester.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JConnection.h"
#include "JConnectionException.h"
#include "JConnectionOutputStream.h"
#include "JConnectionInputStream.h"
#include "Collections.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JMethodDigesterClass : public JClass{
                      public:
                        JMethodDigesterClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.MethodDigester";
                            this->name="jcpp.rmi.server.impl.connection.MethodDigester";
                            this->simpleName="MethodDigester";
                        }

                        JClass* getSuperclass(){
                            return JObject::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JMethodDigester();
                        }
                    };

                    static JClass* clazz;

                    JClass* JMethodDigester::getClazz(){
                        if (clazz==NULL){
                            clazz=new JMethodDigesterClass();
                        }
                        return clazz;
                    }

                    JMethodDigester::JMethodDigester():JObject(getClazz()){
                        digestToMethodMap = new map<JClass*, map<long, JMethod*>*>();
                        methodToDigestMap = new map<JClass*, map<JMethod*, long>*>();
                    }

                    JMethod* JMethodDigester::getMethodFromDigest(JObject* object, long digest){
                        JMethod* m;
                        lock();
                        JClass* classObject = object->getClass();
                        map<long, JMethod*>* internalMap = getFromMap(digestToMethodMap,classObject);
                        if (internalMap == NULL) {
                            createDigests(classObject);
                            internalMap = getFromMap(digestToMethodMap,classObject);
                        }
                        m=getFromMap(internalMap,digest);
                        unlock();
                        return m;
                    }

                    vector<JMethod*>* JMethodDigester::getMethods(JObject* object){
                        vector<JMethod*>* vec;
                        lock();
                        JClass* classObject = object->getClass();
                        map<long, JMethod*>* internalMap = getFromMap(digestToMethodMap,classObject);
                        if (internalMap == NULL) {
                            createDigests(classObject);
                            internalMap = getFromMap(digestToMethodMap,classObject);
                        }
                        vec=getValues(internalMap);
                        unlock();
                        return vec;
                    }

                    long JMethodDigester::getDigestFromMethod(JMethod* method){
                        long l;
                        lock();
                        JClass* classObject = method->getDeclaringClass();
                        map<JMethod*, long>* internalMap = getFromMap(methodToDigestMap,classObject);
                        if (internalMap == NULL) {
                            createDigests(classObject);
                            internalMap = getFromMap(methodToDigestMap,classObject);
                        }
                        l=getFromMap(internalMap,method);
                        unlock();
                        return l;
                    }

                    void JMethodDigester::clear(){
                        methodToDigestMap->clear();
                        digestToMethodMap->clear();
                    }

                    void JMethodDigester::createDigests(JClass* classObject){
                        map<long, JMethod*>* iDigestToMethodMap = new map<long, JMethod*>();
                        map<JMethod*, long>* iMethodToDigestMap = new map<JMethod*, long>();

                        vector<JMethod*>* methods = classObject->getMethods();
                        for (unsigned int i=0;i<methods->size();i++){
                            JMethod* method=methods->at(i);
                            vector<JClass*>* paramTypes = method->getParameterType();
                            string args = "";
                            for (unsigned int j=0;j<paramTypes->size();j++){
                                JClass* param=paramTypes->at(i);
                                args += param->getName();
                                if (j<paramTypes->size()-1){
                                    args+= ",";
                                }
                            }
                            string methodId = method->getName() + ":" + args;
                            unsigned char * cId= new unsigned char[methodId.size() + 1];
                            copy(methodId.begin(), methodId.end(), cId);
                            cId[methodId.size()] = '\0';

                            MD5 context;
                            context.update(cId, methodId.size()+1);
                            context.finalize();
                            unsigned char* dig=context.raw_digest();

                            long digest = 0;
                            for (int k = 0; k < 8; k++) {
                                digest += (dig[7 - k] ^ dig[15 - k]) << (64 - (8 * (k + 1)));
                            }
                            iDigestToMethodMap->insert(pair<long,JMethod*>(digest, method));
                            iMethodToDigestMap->insert(pair<JMethod*,long>(method, digest));
                            delete cId;
                        }
                        digestToMethodMap->insert(pair<JClass*,map<long,JMethod*>*>(classObject, iDigestToMethodMap));
                        methodToDigestMap->insert(pair<JClass*,map<JMethod*,long>*>(classObject, iMethodToDigestMap));
                    }

                    JMethodDigester::~JMethodDigester(){
                        delete methodToDigestMap;
                        delete digestToMethodMap;
                    }
                }
            }
        }
    }
}


