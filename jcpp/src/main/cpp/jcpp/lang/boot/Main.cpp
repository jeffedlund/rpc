#include "QCoreApplication"
#include "JURLClassLoader.h"
#include "JIPackageLoader.h"
#include "JPrimitiveArray.h"
#include "JString.h"
#include "JPrimitiveArray.h"
#include "JFile.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;
using namespace jcpp::net;
using namespace jcpp::io;

/*TODO
-define and use CmdLine parser
-print help command
-have a class Boot{setArgs, run()} and the main calling it
*/
int main(int argc, char* argv[]){
    QCoreApplication coreApp(argc,argv);

    vector<JString*>* array=new vector<JString*>();
    vector<JFile*>* cp=new vector<JFile*>();
    string mainClass="";

    jbool inCp=false;
    jbool inClassName=false;
    int i=1;
    for (i=1;i<argc;i++){
        string s=argv[i];
        if (s=="-classpath"){
            inCp=true;
            inClassName=false;
            continue;

        }else if (s=="-classname"){
            inClassName=true;
            inCp=false;
            continue;
        }

        if (inCp){
            inCp=false;
            jint current;
            jint next = -1;
            do{
              current = next + 1;
              next = s.find_first_of( ";", current );
              cp->push_back(new JFile(s.substr(current, next - current)));
            }while (next != string::npos);

        }else if (inClassName){
            mainClass=s;
            inClassName=false;

        }else{
            array->push_back(new JString(s));
        }
    }

    for (unsigned int i=0;i<cp->size();i++){
        cout<<"cp=="<<cp->at(i)->toString();
        cout<<"\r\n";
        cout.flush();
    }

    cout<<"mainclass="<<mainClass;
    cout.flush();
    JClassLoader::init();
    JURLClassLoader* urlClassLoader=new JURLClassLoader(cp,NULL);
    JClass* main=urlClassLoader->loadClass(mainClass);
    JMethod* method=main->getMethod("main",NULL);
    JPrimitiveArray* pa=new JPrimitiveArray(JString::getClazz(),(vector<JObject*>*)array);
    vector<JObject*> arguments;
    arguments.push_back(pa);
    method->invoke(NULL,&arguments);
    return coreApp.exec();
}



