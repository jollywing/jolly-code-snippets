#include <iostream.h>

void main()
{
	int input_num;
	cout<<"������һ��������5λ��������"<<endl;
	cin >> input_num;
	if (input_num < 0 || input_num >= 100000)
	{
		cout << "��������һ�����Ϸ�������"<<endl;
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

	cout<<"����������������Ϊ��"<<endl;
	int counter1, counter2;//����ѭ������
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