//name: ArrayandFile
//function: learn array and file access
//author: jiqing
//date: 2008-3-12
import java.io.*;

public class ArrayandFile{

//java数组的下标从0开始。
//可以通过arrayname.length访问数组的长度。数组长度在创建时指定并保持不变。
	public static void main(String[] args) {
		//定义一个常量，控制数组大小
		final int ARRAY_SIZE = 7;

		int [] days;	//这创建了一个数组引用，但是它指向null。
		//这时x指向一个7元数组。新创建的元素初始值为0。
		days = new int[ARRAY_SIZE];	
		//上面两行可以写成：double[] x = new double[ARRAY_SIZE];
		//也可以在同一声明中创建多个引用和数组对象：
		//double [] x = new double[5], y= new double[10];

		//可以使用数组初始化器声明并创建数组对象。
		int[] comers = {10, 8, 0,1,4,6,8};
		//一个数组引用可以被赋值给另一个数组引用
		//如：int[] x= comers;
		//但是，如果一个已经有值的引用被赋给新的值，
		//则他原来指向的数据再也不能访问，叫做数据泄露
		//泄露的数据会被java的垃圾回收机制回收

		// java中的读文件
		// 使用FileReader打开文件，只能一次读入一个字符
		// 使用BufferedReader包装FileReader，readLine()一次读入一行。
		// 到达文件结尾，readLine返回的字符串为空。
		BufferedReader in1 = new BufferedReader( new FileReader("data") );

		// java中的写文件
		// 用FileWriter可以打开文件，但只能一次写入一个字符
		// 用BufferedWriter存储输出字符，可以一起发送到文件中。
		// PrintWriter让我们可以使用print和println方法。
		PrintWriter out = new PrintWriter( new BufferedWriter( new FileWriter("data")));
		// 写完之后，关闭文件
		out.close();
		// 关闭文件
		in1.close();
		for(int i=0; i < days.length; ++i) {
		}

		//对于基于gui的程序，使用这个调用来终止
		System.exit(0);
	}
}
