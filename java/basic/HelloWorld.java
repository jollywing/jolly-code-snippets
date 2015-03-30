/*
  一个java程序由一个或多个类组成。
  每个java程序必须至少有一个用户自定义类，类中包含一个main方法，
  是程序开始执行的地方。
*/

// 类定义以public关键字开始，意味着该类可以在程序中任意地方访问
// 如果没有 public 修饰，则只能被同一包中的其它类访问
// 文件名要和文件中声明为 public 的类命相同，
// 所以一个文件中只能有一个 public 类。

// 根据惯例，类名中每一个单词首字母大写，且没有空格和下划线
// 所定义的类名必须与包含类的文件名相同！！！！
public class HelloWorld{
	public static void main(String[] args){
		System.out.println("first java program: Hello World !");
	}
}	//类定义的末尾，不管有没有分号，编译都不会报错。

// 编译：javac -encoding GBK HelloWorld.java
// 如果你的文件是 UTF-8 编码，则使用 javac -encoding UTF-8 HelloWorld.java
//编译后生成字节码HelloWorld.class，调用java解释器执行：
// java HelloWorld
