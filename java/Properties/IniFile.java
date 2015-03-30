
/**
 * IniFile: Load and Save config.ini
 * Author: WU Jiqing (jiqingwu@gmail.com)
 * Create: 2012-08-05
 * Update: 2012-08-06
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Properties;

/**
 * 配置文件读写类
 *
 */
public class IniFile
{
  private File file;
  private Properties properties;

  /**
   * Open file and load properties
   * If the file doesn't exist, then create it .
   */
  public IniFile(String fileName)
  {
    try
    {
      file = new File(fileName);
      if (!file.exists())
        file.createNewFile();
    }
    catch (IOException e)
    {
      e.printStackTrace();
      System.exit(2);
    }

    loadProperties();
  }
  
  /**
   * defaultConfig string can be null.
   */
  public IniFile(String fileName, String defaultConfig)
  {
    try
    {
      file = new File(fileName);
      if (!file.exists())
        file.createNewFile();
      FileOutputStream fos = new FileOutputStream(file);
      PrintWriter printer = new PrintWriter(fos);
      printer.println(defaultConfig);
      printer.close();
    }
    catch (IOException e)
    {
      e.printStackTrace();
      System.exit(2);
    }

    loadProperties();
  }

  /**
   * This is only called by Constructor
   */
  private void loadProperties()
  {
    try
    {
      properties = new Properties();
      FileInputStream fis = new FileInputStream(file);
      properties.load(fis);
      fis.close();
    }
    catch (IOException e)
    {
      e.printStackTrace();
      System.exit(1);
    }
  }
  
  /**
   * If the key doesn't exist, return null;
   */
  public String getProperty(String key)
  {
    return properties.getProperty(key);
  }

  public void setProperty(String key, String value)
  {
    properties.setProperty(key, value);
  }

  /**
   * After setting all properties, you should saveProperties.
   */
  public void saveProperties()
  {
    try
    {
      FileOutputStream fout = new FileOutputStream(file);
      properties.store(fout, "");
      fout.close();
    }
    catch (IOException e)
    {
      e.printStackTrace();
      System.exit(1);
    }
  }

  public static void main(String args[])
  {
    IniFile ini1 = new IniFile("test1.ini");
    ini1.setProperty("good", "Jhon");
    ini1.setProperty("bad", "Jack");
    ini1.setProperty("ugly", "Hellen");
    ini1.saveProperties();
  }

}