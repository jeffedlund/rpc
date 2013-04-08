package jcpp.io;

import java.io.*;

public class ExternalizableObject implements Externalizable{
	private static final long serialVersionUID = 40;
	public boolean bool1=true;
	public byte byte1=1;
	public char c1='c';
	public double d1=1;
	public float f1=2;
	public long l1=3;
	public short s1=4;
	public int i1=5;

	public ExternalizableObject(){
	}

    public void writeExternal(ObjectOutput out) throws IOException{
        out.writeBoolean(bool1);
        out.writeByte(byte1);
        out.writeChar(c1);
        out.writeDouble(d1);
        out.writeFloat(f1);
        out.writeLong(l1);
        out.writeShort(s1);
        out.writeInt(i1);
    }

    public void readExternal(ObjectInput in) throws IOException{
        bool1=in.readBoolean();
        byte1=in.readByte();
        c1=in.readChar();
        d1=in.readDouble();
        f1=in.readFloat();
        l1=in.readLong();
        s1=in.readShort();
        i1=in.readInt();
    }

	public String toString(){
		return "[bool1:"+bool1+"]"+
				"[byte1:"+byte1+"]"+
				"[c1:"+c1+"]"+
				"[d1:"+d1+"]"+
				"[f1:"+f1+"]"+
				"[l1:"+l1+"]"+
				"[s1:"+s1+"]"+
				"[i1:"+i1+"]";
	}
}