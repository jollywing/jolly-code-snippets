
#include "inherit.h"
//#include <iostream>
//using namespace std;

void main()
{
	CHero hero("john", 100 );
	cout << hero.get_name() << endl;
	cout << hero.get_hp() << endl;
	
	//���Զ�̬
	CPeople people("mary");	

	//���ñ�������������ʱ�ͳ�ʼ��
	//���Ҳ����޸����ñ���ȥ������һ������
	CPeople & ref1 = people;
	ref1.print();
	//��Ϊrefʵ������people��
	//��������ĸ�ֵ���ʵ������peple=hero��
	//��ʵ�ǵ�����CPeople�ĸ�ֵ���캯��
	//���ƹ��캯����ϵͳ�ṩ�ġ�
	//ref = hero;
	//ref.print();

	CPeople & ref2 = hero;
	ref2.print();

	CPeople * ptr;
	ptr = &people;
	ptr->print();
	//�������Զ��ҽӣ�Ҫ����ָ�����͵�ת��
	ptr = &hero;
	ptr->print();
	
	return;
}
