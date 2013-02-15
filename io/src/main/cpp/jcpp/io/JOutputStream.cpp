#include "JOutputStream.h"
#include "JIndexOutOfBoundsException.h"
#include "JNullPointerException.h"

namespace jcpp{
    namespace io{
        class JOutputStreamClass : public JClass{
        public:
            JOutputStreamClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.OutputStream";
                name="java.io.OutputStream";
                simpleName="OutputStream";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                return new JOutputStream();
            }
        };

        static JClass* clazz;

        JClass* JOutputStream::getClazz(){
            if (clazz==NULL){
                clazz=new JOutputStreamClass();
            }
            return clazz;
        }

        JOutputStream::JOutputStream():JObject(getClazz()){
        }

        JOutputStream::JOutputStream(JClass* _class):JObject(_class){
        }

        void JOutputStream::write(jint b){
        }

        void JOutputStream::write(jbyte b[]){
            jint length = sizeof(b);
            write(b, 0, length);
        }

        void JOutputStream::write(jbyte b[], int off, int len){
            if (b == 0) {
                throw new JNullPointerException();
            } else {
                jint length = len;
                if ((off < 0) || (off > length) || (len < 0) || ((off + len) > length) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return;
                }
                for (int i = 0 ; i < len ; i++) {
                    write(b[off + i]);
                }
            }
        }


        void JOutputStream::close(){
        }

        void JOutputStream::flush(){
        }

        void JOutputStream::writeBoolean(bool v){
        }

        void JOutputStream::writeByte(jbyte v){
        }

        void JOutputStream::writeChar(jushort v){
        }

        void JOutputStream::writeDouble(double v){
        }

        void JOutputStream::writeFloat(float v){
        }

        void JOutputStream::writeInt(jint v){
        }

        void JOutputStream::writeLong(jlong v){
        }

        void JOutputStream::writeShort(jshort v){
        }
    }
}
