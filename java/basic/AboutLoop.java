//2007-12-12
//jiqing Wu

// ��׼ƫ���ǹ��ڶ����ķ�ɢ�����һ����������׼ƫ��Խ��Խ��ɢ��

/*
  ��Ҫ��forѭ���ڲ�������������������������������ᵼ�²���Ԥ��Ľ����
  ����������ӣ�
  for( double i= 0.1; i< 1.0; i += 0.1 )
	do something;
  ���ѭ��Ӧ������9�Σ���ʵ���ϣ�������������������10�Σ�
  ���е�ʮ��ʱ��i��ֵ������0.99999999....
*/

//ѭ��Ƕ��ʱ���ڲ�ѭ���ڵ�break���ֻ����ֹ�ڲ���ѭ�������Ҫ�����ⲿѭ��������ʹ�ô���ŵ�break
//ͬ����Ҳ�������ڲ�ѭ������ʹ�ô���ŵ�continue����ִ���ⲿ��ѭ����
//c++��֧����һ���ԣ�ֻ��ʹ��goto �����ʵ�֡�
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