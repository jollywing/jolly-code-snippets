//name: ArrayandFile
//function: learn array and file access
//author: jiqing
//date: 2008-3-12
import java.io.*;

public class ArrayandFile{

//java������±��0��ʼ��
//����ͨ��arrayname.length��������ĳ��ȡ����鳤���ڴ���ʱָ�������ֲ��䡣
	public static void main(String[] args) {
		//����һ�����������������С
		final int ARRAY_SIZE = 7;

		int [] days;	//�ⴴ����һ���������ã�������ָ��null��
		//��ʱxָ��һ��7Ԫ���顣�´�����Ԫ�س�ʼֵΪ0��
		days = new int[ARRAY_SIZE];	
		//�������п���д�ɣ�double[] x = new double[ARRAY_SIZE];
		//Ҳ������ͬһ�����д���������ú��������
		//double [] x = new double[5], y= new double[10];

		//����ʹ�������ʼ���������������������
		int[] comers = {10, 8, 0,1,4,6,8};
		//һ���������ÿ��Ա���ֵ����һ����������
		//�磺int[] x= comers;
		//���ǣ����һ���Ѿ���ֵ�����ñ������µ�ֵ��
		//����ԭ��ָ���������Ҳ���ܷ��ʣ���������й¶
		//й¶�����ݻᱻjava���������ջ��ƻ���

		// java�еĶ��ļ�
		// ʹ��FileReader���ļ���ֻ��һ�ζ���һ���ַ�
		// ʹ��BufferedReader��װFileReader��readLine()һ�ζ���һ�С�
		// �����ļ���β��readLine���ص��ַ���Ϊ�ա�
		BufferedReader in1 = new BufferedReader( new FileReader("data") );

		// java�е�д�ļ�
		// ��FileWriter���Դ��ļ�����ֻ��һ��д��һ���ַ�
		// ��BufferedWriter�洢����ַ�������һ���͵��ļ��С�
		// PrintWriter�����ǿ���ʹ��print��println������
		PrintWriter out = new PrintWriter( new BufferedWriter( new FileWriter("data")));
		// д��֮�󣬹ر��ļ�
		out.close();
		// �ر��ļ�
		in1.close();
		for(int i=0; i < days.length; ++i) {
		}

		//���ڻ���gui�ĳ���ʹ�������������ֹ
		System.exit(0);
	}
}
