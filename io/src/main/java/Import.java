import java.io.*;

public class Import{
	
	public static void main(String[] argv) throws Exception{
		ObjectInputStream ois=new ObjectInputStream(new FileInputStream(new File(argv[0])));
		System.out.println(ois.readObject());
		ois.close();
	}
}