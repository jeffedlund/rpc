#ifndef JEXTERNALIZABLEOBJECT_H
#define JEXTERNALIZABLEOBJECT_H

#include "JExternalizable.h"

namespace jcpp{
    namespace io{
    class JExternalizableObject : public JObject, public JExternalizable{
        private:
            JPrimitiveBoolean* bool1;
            JPrimitiveByte* byte1;
            JPrimitiveChar* c1;
            JPrimitiveDouble* d1;
            JPrimitiveFloat* f1;
            JPrimitiveLong* l1;
            JPrimitiveShort* s1;
            JPrimitiveInt* i1;

        public:
            JExternalizableObject();

            static JClass* getClazz();

            bool operator==(JObject &other);

            JPrimitiveBoolean* getBool1();

            void setBool1(JPrimitiveBoolean* bool1);

            JPrimitiveByte* getByte1();

            void setByte1(JPrimitiveByte* byte1);

            JPrimitiveChar* getC1();

            void setC1(JPrimitiveChar* c1);

            JPrimitiveDouble* getD1();

            void setD1(JPrimitiveDouble* d1);

            JPrimitiveFloat* getF1();

            void setF1(JPrimitiveFloat* f1);

            JPrimitiveLong* getL1();

            void setL1(JPrimitiveLong* l1);

            JPrimitiveShort* getS1();

            void setS1(JPrimitiveShort* s1);

            JPrimitiveInt* getI1();

            void setI1(JPrimitiveInt* i1);

            string toString();

            virtual void writeExternal(JObjectOutputStream* out);

            virtual void readExternal(JObjectInputStream* in);

            virtual ~JExternalizableObject();
        };
    }
}

#endif // JEXTERNALIZABLEOBJECT_H
