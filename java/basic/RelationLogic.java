/*
  2007-12-9 jiqing Wu
*/

//�û����󣺲��Զ�java���߼��͹�ϵ����������ճ̶ȡ�
//�������ݣ�
//1����ϵ���������������˭�����ȼ��ߣ�
//2����ϵ���������������������ȹ�ϵ��
//3���߼������&&��&������||��|������

//�����ͷֽ⣺
//����ֻ��һ�����һ��main������

//��ϸ��ƣ�α������ϸ��
import java.io.*;

public class RelationLogic{
	public static void main(String [] args) throws IOException {
		
		//�����ֵ�
		int			userInput;
		String		str;
        
        // java.lang.System ��������Ա��out, err, in
        // err �� out �������� java.io.PrintStream;
        // in �������� java.io.InputStream
        // java.io.InputStreamReader ֻ�ܶ�ȡ�����ַ�
        // java.io.BufferedReader ����˻��幦�ܣ�һ�ο��Զ�ȡһ�С�
		BufferedReader in1 = new BufferedReader( new InputStreamReader(System.in));

		//promt: this program ...
		System.out.println("������򽫳����������⣬�������java�й�ϵ���߼�����������������");

		//promt: 1==3>1
		System.out.println("�ж������ʽ�Ľ����1 == 3 > 1 ��");
		System.out.println("��ѡ�𰸣�1.true; 2.false" );
		System.out.print("�������ѡ��");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if( userInput == 1)
			System.out.println("�ش���ȷ��");
		else
			System.out.println("�ش����");
		
		System.out.println("\n�뿴��һ���⡣\n");

		//promt: 7 + 3 < 2 + 11
		System.out.println("�ж�������ʽ�Ľ����7 + 3 < 2 + 11");
		System.out.println("��ѡ�𰸣�1. 1; 2. 18");
		System.out.print("�������ѡ��");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if ( userInput == 1)
			System.out.println("�ش���ȷ��");
		else
			System.out.println("�ش����");
		

		//&&��Ϊ�߼��룬&��Ϊ�����߼���
		//||��Ϊ�߼���&��Ϊ�����߼���
		//&&֧�ֶ�·���㣬��������ʽ1Ϊ�٣����ټ�����Ϊ�٣����ټ�����ʽ2��
		//&���ܽ����Σ��������ʽ��Ҫ����
		//||��|�������������
		System.out.println("\n�뿴��һ���⡣\n");

		System.out.println("int i=10, j = 9;");
		System.out.println("test = i>10 && j++ > 10;");
		System.out.println("��������ִ�����j��ֵΪ��");
		System.out.println("1. 10; 2. 9;");
		str = in1.readLine();
		userInput = Integer.parseInt(str);
		if ( userInput == 2)
			System.out.println("�ش���ȷ��");
		else
			System.out.println("�ش����");

		System.out.println("���Խ�����");
		
	}
};
