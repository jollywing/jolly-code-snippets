// 13:03 2007-12-7
//��ΪBufferReader��java.io���е�һ���ࡣ
//java.lang�а�����һЩ�ǳ������Ķ������ᱻ�Զ����뵽ÿ��java�����У�
//���Բ���Ҫ�ֶ����롣
//���������õ�System���Math�඼����java.lang��
import java.io.*;


public class MathFunc{

	//ʹ��BufferedReader����Ҫ��׽�쳣������thows IOException��������뱨��
	public static void main(String[] args) throws IOException {
		int x=4;
		/*
		++��--��Ϊ�����͵ݼ��������
		�ŵ�����ǰ����ΪԤ����Ԥ���������
		�ŵ������󣬳�Ϊ�����ͺ���������
		*/
		++x;

		int y=6;
		int z;
		//java.lang����Math�����������ѧ����
		//��Math.max(x,y); Math.min(x,y);
		//Math.random(); ����0-1֮���һ�������
		//Math.abs(x); ����ֵ
		//Math.sqrt(x); ƽ����
		//Math.pow(x,y); x��y�η�		
		z= Math.max(x,y);

		//java��3�ֱ�׼��io����System.in, System.out, System.err
		//System.out��������Ҫ�ķ�����print��println��
		System.out.print(z+"\n");
		//Math�л���������������Math.PI��Math.E
		System.out.println(Math.PI + "\t"+ Math.E);

		//�ӱ�׼�������ж������ݱȽ����ѣ���׼������һ��ֻ���ṩһ���ֽڵ����ݸ�����
		//����Ա���븺��Ѷ�������ֽ�������һ��
		//ʹ��BufferedReader���һ��������Խ���׼�������е����������������ַ�����
		//����readLine()�������һ�������ݺ󣬲Ű�������String����ʽ������
		//new�᷵���²����Ķ���ʵ����һ�����á�
		BufferedReader in1 = new BufferedReader( new InputStreamReader(System.in));
		System.out.print("Enter a string: ");
		System.out.println( in1.readLine() );
		
	}
};