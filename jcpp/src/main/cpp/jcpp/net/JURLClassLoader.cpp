#include "JURLClassLoader.h"
#include "JIPackageLoader.h"
#include <QDir>
#include <QString>
#include <QPluginLoader>
#include <QObject>

namespace jcpp{
    namespace net{
        class JURLClassLoaderClass : public JClass{
        public:
          JURLClassLoaderClass(){
              this->canonicalName="java.net.URLClassLoader";
              this->name="java.lang.URLClassLoader";
              this->simpleName="URLClassLoader";
          }

          JClass* getSuperclass(){
              return JSecureClassLoader::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JURLClassLoader::getClazz(){
            if (clazz==NULL){
                clazz=new JURLClassLoaderClass();
            }
            return clazz;
        }

        JURLClassLoader::JURLClassLoader(vector<JFile*>* files,JClassLoader* parent):JSecureClassLoader(getClazz(),parent){
            this->files=files;
            loadClasses();
        }

        void JURLClassLoader::loadClasses(){
            JIPackageLoader* packageLoader=NULL;
            for (unsigned int i=0;i<files->size();i++){
                JFile* file=files->at(i);
                QFileInfo finfo(QString::fromStdString(file->getAbsolutePath()));
                if (finfo.isFile()){
                    QDir dir=finfo.dir();
                    QPluginLoader pluginLoader(dir.absoluteFilePath(finfo.fileName()));
                    QObject *plugin = pluginLoader.instance();
                    if (plugin){
                        packageLoader = qobject_cast<JIPackageLoader*>(plugin);
                        if (packageLoader!=NULL){
                            initClasses(packageLoader->getPackage());
                        }
                    }

                }else{
                    QDir dir(QString::fromStdString(file->getAbsolutePath()));
                    foreach (QString fileName, dir.entryList(QDir::Files)){
                        QPluginLoader pluginLoader(dir.absoluteFilePath(fileName));
                        QObject *plugin = pluginLoader.instance();
                        if (plugin) {
                            packageLoader = qobject_cast<JIPackageLoader*>(plugin);
                            if (packageLoader!=NULL){
                                initClasses(packageLoader->getPackage());
                            }
                        }
                    }
                }
            }
        }

        JURLClassLoader::~JURLClassLoader() {
            delete files;
        }
    }
}
