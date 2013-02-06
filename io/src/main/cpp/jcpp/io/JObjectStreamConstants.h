#ifndef JOBJECTSTREAMCONSTANTS_H
#define JOBJECTSTREAMCONSTANTS_H

#include <QtGlobal>

//TODO add getClazz()
class JObjectStreamConstants {

public:
    /**
     * Magic number that is written to the stream header.
     */
    static const qint16 STREAM_MAGIC = (qint16)0xaced;

    /**
     * Version number that is written to the stream header.
     */
    static const qint16 STREAM_VERSION = 5;

    /* Each item in the stream is preceded by a tag
     */

    /**
     * First tag value.
     */
    const static qint8 TC_BASE = 0x70;

    /**
     * Null object reference.
     */
    const static qint8 TC_NULL = 	(qint8)0x70;

    /**
     * Reference to an object already written into the stream.
     */
    static const qint8 TC_REFERENCE =	(qint8)0x71;

    /**
     * new Class Descriptor.
     */
    static const qint8 TC_CLASSDESC =       (qint8)0x72;

    /**
     * new Object.
     */
    static const qint8 TC_OBJECT = 	(qint8)0x73;

    /**
     * new String.
     */
    const static qint8 TC_STRING = 	(qint8)0x74;

    /**
     * new Array.
     */
    const static qint8 TC_ARRAY = 	(qint8)0x75;

    /**
     * Reference to Class.
     */
    const static qint8 TC_CLASS = 	(qint8)0x76;

    /**
     * Block of optional data. Byte following tag indicates number
     * of bytes in this block data.
     */
    const static qint8 TC_BLOCKDATA = 	(qint8)0x77;

    /**
     * End of optional block data blocks for an object.
     */
    const static qint8 TC_ENDBLOCKDATA =	(qint8)0x78;

    /**
      * Reset stream context. All handles written into stream are reset.
      */
     static const qint8 TC_RESET = 	(qint8)0x79;

     /**
      * long Block data. The long following the tag indicates the
      * number of bytes in this block data.
      */
     const static qint8 TC_BLOCKDATALONG= (qint8)0x7A;

     /**
      * Exception during write.
      */
     const static qint8 TC_EXCEPTION = 	(qint8)0x7B;

     /**
      * Long string.
      */
     const static qint8 TC_LONGSTRING = 	(qint8)0x7C;

     /**
      * new Proxy Class Descriptor.
      */
     const static qint8 TC_PROXYCLASSDESC =	(qint8)0x7D;

     /**
      * new Enum constant.
      * @since 1.5
      */
     const static qint8 TC_ENUM =		(qint8)0x7E;

     /**
      * Last tag value.
      */
     const static qint8 TC_MAX = 		(qint8)0x7E;

    /**
     * First wire handle to be assigned.
     */
    const static qint32 baseWireHandle = 0x7e0000;


    /******************************************************/
    /* Bit Masks */

    /**
     * Bit mask for ObjectStreamClass flag. Indicates a Serializable class
     * defines its own writeObject method.
     */
    const static qint8 SC_WRITE_METHOD = 0x01;

    /**
     * Bit mask for ObjectStreamClass flag. Indicates Externalizable data
     * written in Block Data mode.
     * Added for PROTOCOL_VERSION_2.
     */
    const static qint8 SC_BLOCK_DATA = 0x08;

    /**
     * Bit mask for ObjectStreamClass flag. Indicates class is Serializable.
     */
    const static qint8 SC_SERIALIZABLE = 0x02;

    /**
     * Bit mask for ObjectStreamClass flag. Indicates class is Externalizable.
     */
    const static qint8 SC_EXTERNALIZABLE = 0x04;

    /**
     * Bit mask for ObjectStreamClass flag. Indicates class is an enum type.
     * @since 1.5
     */
    const static qint8 SC_ENUM = 0x10;

};

#endif // JOBJECTSTREAMCONSTANTS_H
