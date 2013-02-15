#include "JInputStream.h"
#include "Object.h"

namespace jcpp{
    namespace io{
        class JInputStreamClass : public JClass{
        public:
            JInputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.InputStream";
                name="java.io.InputStream";
                simpleName="InputStream";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JInputStream();
            }
        };

        static JClass* clazz;

        JClass* JInputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JInputStreamClass();
            }
            return clazz;
        }

        JInputStream::JInputStream():JObject(getClazz()){
        }

        JInputStream::JInputStream(JClass* _class):JObject(_class){
        }

        jlong JInputStream::available() {
            return 0;
        }

        bool JInputStream::waitForReadyRead(int i) {
            return false;
        }

        jint JInputStream::read() {
            return 0;
        }

        jint JInputStream::read(jbyte b[], int off, int len) {
            return 0;
        }

        jbyte JInputStream::peekByte() {
            return 0;
        }

        jbyte JInputStream::readByte() {
            return 0;
        }

        jshort JInputStream::readShort() {
            return 0;
        }

        jushort JInputStream::readUnsignedShort() {
            return 0;
        }

        jint JInputStream::readInt() {
            return 0;
        }

        jlong JInputStream::readLong() {
            return 0;
        }

        float JInputStream::readFloat() {
            return 0;
        }

        double JInputStream::readDouble() {
            return 0;
        }

        char JInputStream::readChar() {
            return 0;
        }

        bool JInputStream::readBool() {
            return 0;
        }

        void JInputStream::close() {
        }

        JInputStream::~JInputStream() {
        }
    }
}
