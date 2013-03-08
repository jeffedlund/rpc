import java.io.*;

public class ExportBoolean{
	
	public static void main(String[] argv) throws Exception{
		ObjectOutputStream oos=new ObjectOutputStream(new FileOutputStream(new File(argv[0])));
		oos.writeBoolean(true);
		oos.close();
	}
}