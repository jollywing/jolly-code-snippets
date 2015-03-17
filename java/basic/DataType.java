
// COMPILE: javac -encoding GBK DataType.java
// The default encoding is UTF8

/*
  ����������ĸʹ�ô�д��ʽ���������ͱ����������ַ�ʹ��Сд��ʽ��
  ���һ����������һ�����ϵĵ�����ɣ�����Щ����������һ��
  ��һ�����ʺ����ÿ�����ʵ����ַ���Ҫ��д��
*/

public class DataType{
    // "String [] args" is same as "String args[]"
	public static void main(String args[]){

        // Java supports eight primitive data types:
        // byte, short, int, long, float, double, boolean and char.

		//java���������������ͣ�byte( 1byte ), short( 2byte ), int( 4byte ), long( 8byte ).
        // byteռһ���ֽڣ��ݷ��з�����������Χ�� -128 �� 127.
        // ������һ�� byte �����ĸ�ֵ���������Χ���ᱨ��
        // a byte variable has default value: 0
        byte bb = 127;
        System.out.printf("bb is byte variable with value of %d.\n", bb);

        // short type occupies 2 bytes, from -32768 to 32767.
        // A short variable has default value: 0
        short ss = -32768;
        System.out.printf("ss is short variable with value of %d.\n", ss);
        
		//Ĭ������£����γ���������������int, int ռ�ĸ��ֽڡ�
        // A int variable has default value: 0
		int i = 10;
		//final�ؼ����������峣������ʾ�������Ƶ�ֵ�����յģ���Զ����ı䡣
		//�ڳ������޸ĳ�����ֵ������ʱ�ᱨ��
		//��������������ĸ��д������֮�����»��߸�����
		final int MAX_COUNT = 10000;


		//���һ��������ʾLong���ͣ����������ĺ��渽��"L"����9999999999L��
        // A long variable has the default value 0L.

		//floatռ4���ֽ�
		//���������ÿ�ѧ�������洢����β����ָ�������֡�
		//float������24λβ����8λָ����
		//���float���͵ľ��ȴ�Լ��7λ��Ч���֣���Χ��Լ��10^-38��10^38��
		//���ÿ�ѧ��������ʾ���㳣��ʱ��ָ����E��e����һ����������������ɡ�
		//���㳣����Ĭ��������double,���ڸ��㳣������F��ʾfloat���ͣ�����D��ʾdouble���͡�
        // a float variable has default value 0.0f
		float f = 1.12345e20F;

		//double ռ8���ֽ�, 53λβ����11λָ����
		//���ȴ�Լ��15λ10ʮ������Ч���֣���Χ��Լ��10^-308��10^308.
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
		//'\n'��ʾ���У�������Ƶ���һ�еĿ�ʼ
		//'\r'��ʾ�س���������Ƶ���ǰ�е������
		//'\''��ʾ�����ţ�'\"'��ʾ˫����		
		System.out.println('\u0001');	//���Ϊ0001(16����)��unicode�ַ�
		System.out.println("max count = " + MAX_COUNT); //��+�����ַ�����ƴ��
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
