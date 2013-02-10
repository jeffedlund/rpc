import java.io.*;

public class Import{
	
	public static void main(String[] argv) throws Exception{
		ObjectInputStream ois=new ObjectInputStream(new FileInputStream(new File(argv[0])));
		Object o=ois.readObject();
		System.out.println(o);
		if (o instanceof Throwable){
			((Throwable)o).printStackTrace();
		}
		ois.close();
	}
}