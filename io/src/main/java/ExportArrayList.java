import java.io.*;
import java.util.*;

public class ExportArrayList{
	
	public static void main(String[] argv) throws Exception{
		ArrayList l=new ArrayList();
		l.add(new Short((short)1));
		l.add(new Long(2));
		l.add(new Integer(3));
		l.add(new Float(4));
		ObjectOutputStream oos=new ObjectOutputStream(new FileOutputStream(new File(argv[0])));
		oos.writeObject(l);
		oos.close();
	}
}