#include <iostream.h>

void main()
{
	int input_num;
	cout<<"请输入一个不多于5位的整数："<<endl;
	cin >> input_num;
	if (input_num < 0 || input_num >= 100000)
	{
		cout << "你输入了一个不合法的数！"<<endl;
		return;
	}

	int bit_num  = 0;
	int temp;
	temp = input_num;
	while(temp)
	{
		temp = temp / 10;
		bit_num ++;
	}

	cout<<"你输入的数逆序输出为："<<endl;
	int counter1, counter2;//用于循环计数
	for(counter1 = 1; counter1 <= bit_num; counter1 ++)
	{
		temp = input_num;
		for(counter2 = 1; counter2 < counter1; counter2 ++)
		{
			temp = temp / 10;
		}
		temp = temp % 10;
		cout << temp;
	}
	cout << endl;

	return;
}