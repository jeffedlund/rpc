#ifndef JOBJECTSTREAMCONSTANTS_H
#define JOBJECTSTREAMCONSTANTS_H

#include "Object.h"

namespace jcpp{
            namespace io{
        //TODO add getClazz()
        class JObjectStreamConstants {

        public:
            /**
             * Magic number that is written to the stream header.
             */
            static const jshort STREAM_MAGIC = (jshort)0xaced;

            /**
             * Version number that is written to the stream header.
             */
            static const jshort STREAM_VERSION = 5;

            /* Each item in the stream is preceded by a tag
             */

            /**
             * First tag value.
             */
            const static jbyte TC_BASE = 0x70;

            /**
             * Null object reference.
             */
            const static jbyte TC_NULL = 	(jbyte)0x70;

            /**
             * Reference to an object already written into the stream.
             */
            static const jbyte TC_REFERENCE =	(jbyte)0x71;

            /**
             * new Class Descriptor.
             */
            static const jbyte TC_CLASSDESC =       (jbyte)0x72;

            /**
             * new Object.
             */
            static const jbyte TC_OBJECT = 	(jbyte)0x73;

            /**
             * new String.
             */
            const static jbyte TC_STRING = 	(jbyte)0x74;

            /**
             * new Array.
             */
            const static jbyte TC_ARRAY = 	(jbyte)0x75;

            /**
             * Reference to Class.
             */
            const static jbyte TC_CLASS = 	(jbyte)0x76;

            /**
             * Block of optional data. Byte following tag indicates number
             * of bytes in this block data.
             */
            const static jbyte TC_BLOCKDATA = 	(jbyte)0x77;

            /**
             * End of optional block data blocks for an object.
             */
            const static jbyte TC_ENDBLOCKDATA =	(jbyte)0x78;

            /**
              * Reset stream context. All handles written into stream are reset.
              */
             static const jbyte TC_RESET = 	(jbyte)0x79;

             /**
              * long Block data. The long following the tag indicates the
              * number of bytes in this block data.
              */
             const static jbyte TC_BLOCKDATALONG= (jbyte)0x7A;

             /**
              * Exception during write.
              */
             const static jbyte TC_EXCEPTION = 	(jbyte)0x7B;

             /**
              * Long string.
              */
             const static jbyte TC_LONGSTRING = 	(jbyte)0x7C;

             /**
              * new Proxy Class Descriptor.
              */
             const static jbyte TC_PROXYCLASSDESC =	(jbyte)0x7D;

             /**
              * new Enum constant.
              * @since 1.5
              */
             const static jbyte TC_ENUM =		(jbyte)0x7E;

             /**
              * Last tag value.
              */
             const static jbyte TC_MAX = 		(jbyte)0x7E;

            /**
             * First wire handle to be assigned.
             */
            const static jint baseWireHandle = 0x7e0000;


            /******************************************************/
            /* Bit Masks */

            /**
             * Bit mask for ObjectStreamClass flag. Indicates a Serializable class
             * defines its own writeObject method.
             */
            const static jbyte SC_WRITE_METHOD = 0x01;

            /**
             * Bit mask for ObjectStreamClass flag. Indicates Externalizable data
             * written in Block Data mode.
             * Added for PROTOCOL_VERSION_2.
             */
            const static jbyte SC_BLOCK_DATA = 0x08;

            /**
             * Bit mask for ObjectStreamClass flag. Indicates class is Serializable.
             */
            const static jbyte SC_SERIALIZABLE = 0x02;

            /**
             * Bit mask for ObjectStreamClass flag. Indicates class is Externalizable.
             */
            const static jbyte SC_EXTERNALIZABLE = 0x04;

            /**
             * Bit mask for ObjectStreamClass flag. Indicates class is an enum type.
             * @since 1.5
             */
            const static jbyte SC_ENUM = 0x10;

        };
    }
}

#endif // JOBJECTSTREAMCONSTANTS_H
