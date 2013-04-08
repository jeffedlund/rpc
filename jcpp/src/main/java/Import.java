import java.io.*;
import java.util.*;

public class Import{
	
	public static void main(String[] argv) throws Exception{
		List<File> files=new ArrayList<File>();
		File f=new File(argv[0]);
		if (f.isDirectory()){
			for (File ftmp : f.listFiles()){
				if (ftmp.getName().indexOf(".ser")>0){
					files.add(ftmp);
				}
			}
		}else{
			files.add(f);
		}
		for (File tmp : files){
			try{
				System.out.println("Unmarshalling file "+tmp.getName());
				ObjectInputStream ois=new ObjectInputStream(new FileInputStream(tmp));
				Object o=ois.readObject();
				System.out.println(o);
				if (o instanceof Throwable){
					((Throwable)o).printStackTrace();
				}
				ois.close();
			}catch(Throwable e){
				System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				e.printStackTrace();
			}
		}
	}
}