/*-------------------------------------------
  2007-12-10
  jiqing Wu
 *------------------------------------------*/

//�û����󣺲�ѯ����Ӣ�۵ļ��ܡ�
//���룺Ӣ�۵ı�š�
//���������Ϣ������ʾӢ�۵ļ��ܡ�

//�����ͷֽ⣺����ֻ��һ�����һ��main������

/*
  �ڲ��Ը�������Ƿ����ʱ������������������������ȵ�ֵ�������ڳ����в���ȣ���΢С����
  ����ʹ�á�������ȡ��ķ������˷�������⡣�������x�Ƿ����10ʱ�����Բ���
  Math.abs(x-10.0) <= 1E-10�Ƿ������
*/

/*
  ���������(?:)�����ȼ��ܵͣ����ڹ�ϵ���߼�����������ڸ�ֵ�������
*/
import javax.swing.*;		//JOptionPane�������������

public class HumHero{
	public static void main(String [] args){
		//variables
		int userInput;
		String str;
		//promt
		while( true )
		{
			str = JOptionPane.showInputDialog( null,"ѡ��Ҫ��ѯ��Ӣ�ۣ�\n1.��ħ��ʦ 2.ɽ��֮�� 3.ʥ��ʿ 4.Ѫħ��ʦ\n5.�˳�");
			//convert
			userInput = Integer.parseInt(str);
			//show message
			switch(userInput)
			{
			//case�����ֵ���������ͻ��ַ��ͣ���c++��Ҳ�����
			case 1:
				JOptionPane.showMessageDialog(null, "��ħ��ʦ��1.�ٻ�ˮԪ�� 2.��ѩ 3.�Ի͹⻷ 4.����");
				break;
			case 2:
				JOptionPane.showMessageDialog(null, "ɽ��֮����1.�籩֮�� 2.����һ�� 3.�ػ� 4.�����·�");
				break;
			case 3:
				JOptionPane.showMessageDialog(null, "ʥ��ʿ��1.ʥ�� 2.�����⻷ 3.��ʥ���� 4.����");
				break;
			case 4:
				JOptionPane.showMessageDialog(null, "Ѫħ��ʦ��1.����֮�� 2.���� 3.ħ����ȡ 4.����");
				break;
			case 5:
				System.exit(0);	//��ֹ����
				break;
			default:
				JOptionPane.showMessageDialog(null, "������Ĳ�����Чֵ!!");
			}
		}
	}
};