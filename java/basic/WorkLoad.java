/*
  ������ƹ���һ�����Ϊ��
  1) ȷ���û�����Ҫ�˽������ϸ�ڣ�ȷ����������������
  2) �����ͷֽ⣺�ѳ��򻮷�Ϊ����߼��Ӳ��֣��������û�����ȷ��ÿ����������Ҫ���������
  3) ��ϸ��ƣ�����Ա����򷽷���Ϊ����Ӳ��֣������ֽ⡣ÿ��С���ֽ�һ��ϸ����ֱ���ܱ�д��java���Ϊֹ������ϸ����
  4) ʵ�֣����㷨ת����java��䡣
  5) ���ԣ�����ĵ�һ�������汾��ΪAlpha�汾��ͨ���ڲ���������������bug���Ƴ�beta�棬���Ѻõ��ⲿ�û����ԣ�ȥ���·��ֵ�bug���Ƴ���ʽ�档
*/

/*
  �ⲿ�ĵ�˵������������롢�����ǰ������������������д�ڷ������档
  �ڲ��ĵ�˵����ָ�����ڲ���ע��
*/
import java.io.*;

//�û�����ȷ��������ܷ���ɼ�������
//��������ÿ�������һ��ָ������������Ƶ�ʣ�GHZ��������Ĵ�С��ָ�����������������ޣ��룩��
//����Ǽ�����ܷ��������
public class WorkLoad{

	/*--------------------------------------------------------
	  ���룺�����Ƶ�ʣ������С����������
	  �����������ܷ��������
	  ǰ�����������붼Ϊ������
	  ������������
	 *-------------------------------------------------------*/
	public static void main(String[] args) throws IOException {

		//���ݴʵ䣬���������Ͷ���
		float freq;		//computer frequency
		float taskSize;	//task size
		float dueDate;	//due date of task
		float timeCost;	//time cost
		String str;		//string to hold input
		BufferedReader in1 = new BufferedReader( new InputStreamReader( System.in ));

		/*
		  java�а���һЩ�������ܽ��ַ���ת����int,double,boolean������
		  Integer.parseInt(str);
		  Double.parseDouble(str);
		  Boolean.valueOf(str).booleanValue();
		  ... ...
		*/

		//input computer frequency
		System.out.println("��������Ƶ�ʣ�GHZ��:");
		str = in1.readLine();
		freq = Float.parseFloat(str);	

		//input task size
		System.out.println("���������С��ָ������: M��:");
		str = in1.readLine();
		taskSize = Float.parseFloat(str);

		//input due date
		System.out.println("�����ֹ���ޣ��룩��");
		str = in1.readLine();
		dueDate = Float.parseFloat(str);

		//caculate time cost
		timeCost = taskSize / (freq * 1024);

		//output result
		if(timeCost > dueDate)
			System.out.println("��������ܰ�ʱ�������");
		else
			System.out.println("������ܹ���ʱ�������.");
	}
};