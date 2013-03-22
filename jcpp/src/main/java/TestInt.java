public class TestInt{

	public static void main(String[] argv){
		int v=1234;
		int i=(v>>>0) & 0xFF;
		byte b=(byte)((v >>> 0) & 0xFF);
		System.out.println("i="+i);
		System.out.println("b="+b);
		byte i1=0;
		byte i2=0;
		byte i3=0;
		byte i4=-46;
		System.out.println(""+(i1|i2|i3|i4));
		System.out.println(""+((i1|i2|i3|i4)<0));

		int r=((i1 << 24) + (i2 << 16) + (i3 << 8) + (i4 << 0));
		System.out.println("r=="+r);
		System.out.println(""+(-46 & 0xFF));
	}
}