//2007-12-12
//jiqing Wu

// 标准偏差是关于度量的发散程序的一个衡量；标准偏差越大，越发散。

/*
  不要在for循环内部将浮点变量用作索引变量，舍入误差会导致不可预测的结果。
  看下面的例子：
  for( double i= 0.1; i< 1.0; i += 0.1 )
	do something;
  这个循环应当运行9次，但实际上，由于舍入误差可能运行10次，
  运行第十次时，i的值可能是0.99999999....
*/

//循环嵌套时，内部循环内的break语句只能终止内部的循环，如果要跳出外部循环，可以使用带标号的break
//同样，也可以在内部循环体内使用带标号的continue继续执行外部的循环。
//c++不支持这一特性，只能使用goto 标号来实现。
public class AboutLoop {
	public static void main(String [] args){
		int i, j;
		for(i=1; i < 5; ++i)
			for(j = 1; j < 5; ++j)
				System.out.println(i + " * " + j +" = " + i*j);
		System.out.println(" ");

outer1:	for(i=1; i < 5; ++i)
			for(j = 1; j < 5; ++j)
			{
				if (j == 4)	break outer1;
				System.out.println(i + " * " + j +" = " + i*j);
			}
		System.out.println(" ");

outer2:	for(i=1; i<5; ++i)
	inner:	for(j=1; j<5; ++j)
			{
				if(j == 4 )	continue outer2;
				System.out.println(i + " * " + j +" = " + i*j);
			}
		System.out.println(" ");
		
	}
};