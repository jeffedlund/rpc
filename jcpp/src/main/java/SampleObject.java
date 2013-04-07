import java.io.*;

public class SampleObject implements Serializable{
	private static final long serialVersionUID = 40;
	private boolean bool1=true;
	private byte byte1=1;
	private char c1='c';
	private double d1=1;
	private float f1=2;
	private long l1=3;
	private short s1=4;
	private int i1=5;

	SampleObject(){
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