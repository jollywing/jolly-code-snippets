// 13:03 2007-12-7
//因为BufferReader是java.io包中的一个类。
//java.lang中包含了一些非常基础的东西，会被自动导入到每个java程序中，
//所以不需要手动导入。
//例如我们用的System类和Math类都属于java.lang。
import java.io.*;


public class MathFunc{

	//使用BufferedReader必须要捕捉异常，加上thows IOException，否则编译报错
	public static void main(String[] args) throws IOException {
		int x=4;
		/*
		++和--称为递增和递减运算符。
		放到变量前，成为预增和预减运算符。
		放到变量后，成为后增和后减运算符。
		*/
		++x;

		int y=6;
		int z;
		//java.lang包的Math类中有许多数学方法
		//如Math.max(x,y); Math.min(x,y);
		//Math.random(); 返回0-1之间的一个随机数
		//Math.abs(x); 绝对值
		//Math.sqrt(x); 平方根
		//Math.pow(x,y); x的y次方		
		z= Math.max(x,y);

		//java有3种标准的io对象：System.in, System.out, System.err
		//System.out有两个重要的方法：print和println。
		System.out.print(z+"\n");
		//Math中还定义了两个常量Math.PI和Math.E
		System.out.println(Math.PI + "\t"+ Math.E);

		//从标准输入流中读入数据比较困难，标准输入流一次只能提供一个字节的数据给程序
		//程序员必须负责把多个输入字节连接在一起。
		//使用BufferedReader类的一个对象可以讲标准输入流中的数据组成有意义的字符串。
		//它的readLine()方法获得一整行数据后，才把数据以String的形式给程序。
		//new会返回新产生的对象实例的一个引用。
		BufferedReader in1 = new BufferedReader( new InputStreamReader(System.in));
		System.out.print("Enter a string: ");
		System.out.println( in1.readLine() );
		
	}
};