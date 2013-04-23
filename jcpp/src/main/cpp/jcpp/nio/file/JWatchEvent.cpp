#include "JWatchEvent.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchEventClass : public JClass{
                public:
                    JWatchEventClass(){
                        this->canonicalName="java.nio.file.WatchEvent";
                        this->name="java.nio.file.WatchEvent";
                        this->simpleName="WatchEvent";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }

                    void fillDeclaredClasses(){
                        addDeclaredClass(JWatchEvent::JKind::getClazz());
                        addDeclaredClass(JWatchEvent::JModifier::getClazz());
                    }
            };

            static JClass* clazz;

            JClass* JWatchEvent::getClazz(){
                if (clazz==NULL){
                    clazz=new JWatchEventClass();
                }
                return clazz;
            }

            class JWatchKindClass : public JClass{
                public:
                    JWatchKindClass(){
                        this->canonicalName="java.nio.file.WatchEvent$Kind";
                        this->name="java.nio.file.WatchEvent$Kind";
                        this->simpleName="WatchEvent$Kind";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }

                    virtual JClass* getDeclaringClass(){
                        return JWatchEvent::getClazz();
                    }
            };

            static JClass* kindClazz;
            JClass* JWatchEvent::JKind::getClazz(){
                if (kindClazz==NULL){
                    kindClazz=new JWatchKindClass();
                }
                return kindClazz;
            }

            class JWatchModifierClass : public JClass{
                public:
                    JWatchModifierClass(){
                        this->canonicalName="java.nio.file.WatchEvent$Modifier";
                        this->name="java.nio.file.WatchEvent$Modifier";
                        this->simpleName="WatchEvent$Modifier";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }

                    virtual JClass* getDeclaringClass(){
                        return JWatchEvent::getClazz();
                    }
            };

            static JClass* modifierClazz;
            JClass* JWatchEvent::JModifier::getClazz(){
                if (modifierClazz==NULL){
                    modifierClazz=new JWatchModifierClass();
                }
                return modifierClazz;
            }

            JWatchEvent::~JWatchEvent(){
            }
        }
    }
}
