
import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Properties;

class FileTest
{
  
  public static void main(String args[])
  {
    File file = new File("test.txt");
    if (file.exists() == false)
    {
      System.out.println("test.txt dosen't exist, create it.");
      try
      {
        file.createNewFile();
      }
      catch (IOException e)
      {
        System.out.println("create test.txt failed！Now exit!");
        e.printStackTrace();
        System.exit(1);
      }
    } // end if (file.exists)

    try
    {
      FileInputStream fis = new FileInputStream(file);
      Properties ps = new Properties();
      ps.load(fis);
      fis.close();
      System.out.println("hello: " + ps.getProperty("hello"));
      System.out.println("Node: " + ps.getProperty("Node"));

      ps.setProperty("Youth", "beauty");
      FileOutputStream fos = new FileOutputStream(file);
      ps.store(fos, "jiqing");
      fos.close();
    }
    catch (IOException e)
    {
      e.printStackTrace();
      System.exit(2);
    }

    // try{
    //   FileOutputStream fos = new FileOutputStream(file);
    //   PrintWriter printer = new PrintWriter(fos);
    //   printer.print("hello=good life\nNode=yes\n");
    //   printer.close();
    // }
    // catch (FileNotFoundException e)
    // {
    //   e.printStackTrace();
    //   System.exit(3);
    // }
  } // end main()

}