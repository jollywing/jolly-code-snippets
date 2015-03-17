/*-------------------------------------------
  2007-12-10
  jiqing Wu
 *------------------------------------------*/

//用户需求：查询人族英雄的技能。
//输入：英雄的编号。
//输出：在消息框上显示英雄的技能。

//分析和分解：程序只有一个类和一个main方法。

/*
  在测试浮点变量是否相等时，由于舍入误差，两个理论上相等的值，可能在程序中不相等，有微小的误差。
  可以使用“近似相等”的方法来克服这个问题。例如测试x是否等于10时，可以测试
  Math.abs(x-10.0) <= 1E-10是否成立。
*/

/*
  条件运算符(?:)的优先级很低，低于关系和逻辑运算符，高于赋值运算符。
*/
import javax.swing.*;		//JOptionPane类属于这个包。

public class HumHero{
	public static void main(String [] args){
		//variables
		int userInput;
		String str;
		//promt
		while( true )
		{
			str = JOptionPane.showInputDialog( null,"选择要查询的英雄：\n1.大魔法师 2.山丘之王 3.圣骑士 4.血魔法师\n5.退出");
			//convert
			userInput = Integer.parseInt(str);
			//show message
			switch(userInput)
			{
			//case后面的值必须是整型或字符型，在c++中也是如此
			case 1:
				JOptionPane.showMessageDialog(null, "大魔法师：1.召唤水元素 2.暴雪 3.辉煌光环 4.传送");
				break;
			case 2:
				JOptionPane.showMessageDialog(null, "山丘之王：1.风暴之锤 2.雷霆一击 3.重击 4.天神下凡");
				break;
			case 3:
				JOptionPane.showMessageDialog(null, "圣骑士：1.圣光 2.耐力光环 3.神圣护盾 4.复活");
				break;
			case 4:
				JOptionPane.showMessageDialog(null, "血魔法师：1.烈焰之击 2.放逐 3.魔法吸取 4.火凤凰");
				break;
			case 5:
				System.exit(0);	//终止程序
				break;
			default:
				JOptionPane.showMessageDialog(null, "你输入的不是有效值!!");
			}
		}
	}
};