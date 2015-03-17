
// COMPILE: javac -encoding GBK DataType.java
// The default encoding is UTF8

/*
  类名的首字母使用大写形式，方法名和变量名的首字符使用小写形式。
  如果一个变量名由一个以上的单词组成，将这些单词连接在一起，
  第一个单词后面的每个单词的首字符都要大写。
*/

public class DataType{
    // "String [] args" is same as "String args[]"
	public static void main(String args[]){

        // Java supports eight primitive data types:
        // byte, short, int, long, float, double, boolean and char.

		//java具有四种整数类型：byte( 1byte ), short( 2byte ), int( 4byte ), long( 8byte ).
        // byte占一个字节，容放有符号整数，范围从 -128 到 127.
        // 如果你给一个 byte 变量的赋值超过这个范围，会报错。
        // a byte variable has default value: 0
        byte bb = 127;
        System.out.printf("bb is byte variable with value of %d.\n", bb);

        // short type occupies 2 bytes, from -32768 to 32767.
        // A short variable has default value: 0
        short ss = -32768;
        System.out.printf("ss is short variable with value of %d.\n", ss);
        
		//默认情况下，整形常量的数据类型是int, int 占四个字节。
        // A int variable has default value: 0
		int i = 10;
		//final关键字用来定义常量，表示赋给名称的值是最终的，永远不会改变。
		//在程序中修改常量的值，编译时会报错。
		//常量名的所有字母大写，单词之间用下划线隔开。
		final int MAX_COUNT = 10000;


		//如果一个常量表示Long类型，必须在它的后面附上"L"，如9999999999L。
        // A long variable has the default value 0L.

		//float占4个字节
		//浮点数采用科学计数法存储，分尾数和指数两部分。
		//float类型有24位尾数，8位指数。
		//因此float类型的精度大约是7位有效数字，范围大约是10^-38到10^38。
		//当用科学计数法表示浮点常量时，指数由E或e加上一个正整数或负整数组成。
		//浮点常量的默认类型是double,可在浮点常量后附上F表示float类型，附上D表示double类型。
        // a float variable has default value 0.0f
		float f = 1.12345e20F;

		//double 占8个字节, 53位尾数，11位指数。
		//精度大约是15位10十进制有效数字，范围大约是10^-308到10^308.
        // a double variable has default value 0.0d
		double d = 12345678.76543;

        // float and double should never be used for precise values,
        // such as currency. For that, you will need to use the
        // java.math.BigDecimal class instead.

        // the size of boolean variable is not precisely defined.
        // a boolean variable has the default value: false.
        boolean cloudy = true;
        System.out.println("Cloudy? " + cloudy);

        // different from c and cpp, char in java is a 16 bit unicode character.
        // from 0 ('\u0000') to 65535 ('\uffff').
        // A char variable has the default value '\u0000'.
        char c = 'F';
        // a char equal to a integer, but in formating output, need manual conversion.
        System.out.printf("char c is %c, also equals to the int value %d.\n", c, (int)c);
        char cc = 101;
        System.out.printf("char cc is %c!\n", cc);
        char cc1 = 'e';
        System.out.println("cc == cc1? " + (cc == cc1));
        short cc_int = 101;
        System.out.println("cc == cc_int? " + (cc == cc_int));

		//output		
		//'\n'表示换行，将光标移到下一行的开始
		//'\r'表示回车，将光标移到当前行的最左边
		//'\''表示单引号，'\"'表示双引号		
		System.out.println('\u0001');	//序号为0001(16进制)的unicode字符
		System.out.println("max count = " + MAX_COUNT); //用+进行字符串的拼接
		System.out.println(i + "\t"+ f +"\t"+ d);

        // For convinience, though String is not a primitive data type,
        // Java provides the support to String.
        // A string object has the default value 'null'
        // However, if you access a uninitialized String variable,
        // the compiler will report error!
        String str = null;
        System.out.printf("String str has the default value: %s\n", str);

        // The default values is fit for global variables.
        // Local variables are slightly different;
        // the compiler never assigns a default value to an
        // uninitialized local variable. If you cannot initialize your
        // local variable where it is declared, make sure to
        // assign it a value before you attempt to use it.
        // Accessing an uninitialized local variable will
        // result in a compile-time error!
	}
};
