import java.io.*;

public class Export{
	
	public static void main(String[] argv) throws Exception{
		ObjectOutputStream oos=new ObjectOutputStream(new FileOutputStream(new File(argv[0])));
		Class clazz=Class.forName(argv[1]);
		oos.writeObject(clazz.newInstance());
		oos.close();
	}
}