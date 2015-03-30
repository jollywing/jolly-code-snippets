package test;

import java.lang.reflect.Array;
class B
{
  private float [] data_;

  public B(float [] data)
  {
    data_ = data;
  }

  public void printSysInfo()
  {
    String version = System.getProperty("java.version");
    String vmVender = System.getProperty("java.vendor");
    String osName = System.getProperty("os.name");
    
    System.out.println("OS: " + osName);
    System.out.println("Java Vendor: " + vmVender);
    System.out.println("Java Version: " + version);
    System.out.println("Version of class A: " + A.VERSION);
  }

  public void print()
  {
    System.out.println("This is an object of B class.");
    for (int i = 0; i < Array.getLength(data_); ++i)
    {
      System.out.println("" + data_[i]);
    }
  }
}
