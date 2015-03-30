/*
  2007-12-9 jiqing Wu
*/

//用户需求：测试对java中逻辑和关系运算符的掌握程度。
//测试内容：
//1。关系运算符和相等运算符谁的优先级高；
//2。关系运算符和算术运算符的优先关系。
//3。逻辑运算符&&和&的区别，||和|的区别

//分析和分解：
//程序只有一个类和一个main方法。

//详细设计：伪代码逐步细化
import java.io.*;

public class RelationLogic{
	public static void main(String [] args) throws IOException {
		
		//数据字典
		int			userInput;
		String		str;
        
        // java.lang.System 有三个成员：out, err, in
        // err 和 out 的类型是 java.io.PrintStream;
        // in 的类型是 java.io.InputStream
        // java.io.InputStreamReader 只能读取单个字符
        // java.io.BufferedReader 添加了缓冲功能，一次可以读取一行。
		BufferedReader in1 = new BufferedReader( new InputStreamReader(System.in));

		//promt: this program ...
		System.out.println("这个程序将出三道测试题，考察你对java中关系和逻辑运算符的掌握情况。");

		//promt: 1==3>1
		System.out.println("判断这个等式的结果：1 == 3 > 1 ：");
		System.out.println("备选答案：1.true; 2.false" );
		System.out.print("输入你的选择：");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if( userInput == 1)
			System.out.println("回答正确！");
		else
			System.out.println("回答错误！");
		
		System.out.println("\n请看下一道题。\n");

		//promt: 7 + 3 < 2 + 11
		System.out.println("判断这个表达式的结果：7 + 3 < 2 + 11");
		System.out.println("备选答案：1. 1; 2. 18");
		System.out.print("输入你的选择：");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if ( userInput == 1)
			System.out.println("回答正确！");
		else
			System.out.println("回答错误！");
		

		//&&称为逻辑与，&称为布尔逻辑与
		//||称为逻辑或，&称为布尔逻辑或
		//&&支持短路计算，即如果表达式1为假，则不再计算结果为假，不再计算表达式2。
		//&不管结果如何，两个表达式都要计算
		//||和|的区别与此类似
		System.out.println("\n请看下一道题。\n");

		System.out.println("int i=10, j = 9;");
		System.out.println("test = i>10 && j++ > 10;");
		System.out.println("上面的语句执行完后，j的值为：");
		System.out.println("1. 10; 2. 9;");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if ( userInput == 2)
			System.out.println("回答正确！");
		else
			System.out.println("回答错误！");

		System.out.println("测试结束。");
		
	}
};
