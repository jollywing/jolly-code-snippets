
package test;

// import java.lang.reflect.Array;
// We needn't Array.getLength(arrayname), just use arrayname.length
class A
{
  public static final String VERSION = "0.0.1";

  public static void main(String [] args)
  {
    float [] data = new float[10];
    for( int i = 0; i < data.length; i++)
      data[i] = i * i;
    B b = new B(data);
    b.print();
    b.printSysInfo();
  }
}

