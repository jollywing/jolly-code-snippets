//2007-12-6 jiqing
/*
  你应该经常提醒自己：
  如果6个月后我再回顾这个程序，还能这么容易理解它吗？
  其他人看了我的代码，能很容易理解我的工作吗？
*/

//一元算术运算从右向左求值

public class Operations{
	public static void main(String[] args){

		//当表达式结果的数据类型与所赋值的变量的数据类型不同时，会自动进行赋值转换。
		//整型表达式的结果赋给浮点变量，属于扩展转换，是合法的。
		float f;
		f = 20;
		//浮点表达式的结果被赋给整型变量，属于缩小转换，是非法的。
		//但可以使用强制类型转换实现。
		int i;
		//i = f;	illegal
		i = (int)f;

		//通常算术运算仅在两个相同类型的数值之间进行。
		//包含两个类型的表达式称为混合模式表达式，
		//包含两种类型数值的计算称为混合模式计算。
		//当一个double型的数值和一个int型的数值运算时，
		//int类型的会被自动转换成double类型的值，存到一个临时变量中，
		//然后进行浮点型的运算，这种自动转换称为数值提升。

		//数值提升规则：
		//如果一个是double, 则另一个被转换成double.
		//否则如果一个是float，另一个被转换成float，
		//否则如果一个是long，另一个被转换成long。
		//否则两个都被转换成int类型。
		//尽量避免使用混合模式的表达式，因为可读性差。
		f = f + i;
		System.out.println(f);

        System.out.println("integer divided by integer, the result is INTEGER.");
        int int1 = 23, int2 = 4;
        System.out.println( int1 + "/" + int2 + " = " + (int1 /int2));
        System.out.println("\'%\' represents MOD ");
        System.out.println( int1 + "%" + int2 + " = " + (int1 % int2));
	}
};





