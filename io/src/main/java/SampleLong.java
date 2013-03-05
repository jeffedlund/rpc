import java.io.*;

public class SampleLong {

	public static void main(String[] argv){
		long l=-1907493020;
		byte[] b=new byte[8];
		b[7] = (byte) (l >>> 0);
        b[6] = (byte)(l >>> 8);
        b[5] = (byte)(l >>> 16);
        b[4] = (byte)(l >>> 24);
        b[3] = (byte)(l >>> 32);
        b[2] = (byte)(l >>> 40);
        b[1] = (byte)(l >>> 48);
        b[0] = (byte)(l >>> 56);

        System.out.println("0 ="+b[0]);
        System.out.println("1 ="+b[1]);
        System.out.println("2 ="+b[2]);
        System.out.println("3 ="+b[3]);
        System.out.println("4 ="+b[4]);
        System.out.println("5 ="+b[5]);
        System.out.println("6 ="+b[6]);
        System.out.println("7 ="+b[7]);

        long l1=(b[7] & 0xFFL) << 0;
        long l2=(b[6] & 0xFFL) << 8;
        long l3=(b[5] & 0xFFL) << 16;
        long l4=(b[4] & 0xFFL) << 24;
        long l5=(b[3] & 0xFFL) << 32;
        long l6=(b[2] & 0xFFL) << 40;
        long l7=(b[1] & 0xFFL) << 48;
        long l8=b[0] << 56;
        long nl=l1+l2+l3+l4+l5+l6+l7+l8;
        assert nl==l;

        System.out.println("0 ="+l1);
        System.out.println("1 ="+l2);
        System.out.println("2 ="+l3);
        System.out.println("3 ="+l4);
        System.out.println("4 ="+l5);
        System.out.println("5 ="+l6);
        System.out.println("6 ="+l7);
        System.out.println("7 ="+l8);
	}
}