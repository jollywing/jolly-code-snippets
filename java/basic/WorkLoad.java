/*
  程序设计过程一般概括为：
  1) 确定用户需求：要了解问题的细节，确定程序的输入输出。
  2) 分析和分解：把程序划分为多个逻辑子部分，并根据用户需求确定每个子任务需要满足的需求。
  3) 详细设计：程序员将类或方法分为多个子部分，叫做分解。每个小部分进一步细化，直到能编写出java语句为止，叫做细化。
  4) 实现：将算法转换成java语句。
  5) 测试：程序的第一个完整版本称为Alpha版本，通过内部测试修正大量的bug，推出beta版，由友好的外部用户测试，去除新发现的bug，推出正式版。
*/

/*
  外部文档说明：程序的输入、输出、前置条件，后置条件。写在方法外面。
  内部文档说明：指方法内部的注释
*/
import java.io.*;

//用户需求：确定计算机能否完成计算任务。
//假设计算机每周期完成一条指令，给定计算机的频率（GHZ），任务的大小（指令条数），截至期限（秒）。
//输出是计算机能否完成任务。
public class WorkLoad{

	/*--------------------------------------------------------
	  输入：计算机频率，任务大小，截至期限
	  输出：计算机能否完成任务。
	  前置条件：输入都为正数。
	  后置条件：无
	 *-------------------------------------------------------*/
	public static void main(String[] args) throws IOException {

		//数据词典，变量声明和定义
		float freq;		//computer frequency
		float taskSize;	//task size
		float dueDate;	//due date of task
		float timeCost;	//time cost
		String str;		//string to hold input
		BufferedReader in1 = new BufferedReader( new InputStreamReader( System.in ));

		/*
		  java中包含一些方法，能将字符串转换成int,double,boolean等类型
		  Integer.parseInt(str);
		  Double.parseDouble(str);
		  Boolean.valueOf(str).booleanValue();
		  ... ...
		*/

		//input computer frequency
		System.out.println("输入计算机频率（GHZ）:");
		str = in1.readLine();
		freq = Float.parseFloat(str);	

		//input task size
		System.out.println("输入任务大小（指令条数: M）:");
		str = in1.readLine();
		taskSize = Float.parseFloat(str);

		//input due date
		System.out.println("输入截止期限（秒）：");
		str = in1.readLine();
		dueDate = Float.parseFloat(str);

		//caculate time cost
		timeCost = taskSize / (freq * 1024);

		//output result
		if(timeCost > dueDate)
			System.out.println("计算机不能按时完成任务！");
		else
			System.out.println("计算机能够按时完成任务.");
	}
};