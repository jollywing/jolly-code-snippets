/*=================================
	��ģ��ͺ���ģ�����ϰ
	by jiqing 2007-10-30
 *================================*/
#include "TemplatePractice.h"
#include <iostream>

int main()
{
	int x;
	vector<int> intArray;

	cout <<"now, show bubble sort."<<endl;
	cout << "input some integers:" <<endl;

	//	linux��^d (ctrl+d)��������
	//	windows��^z(ctrl+z)��������
	//	ÿ���ûس���������cin.get()��ȡ����������
	//	��������������ʱ��^zҲ���ܽ�������
	//	^z������뻺������^zǰ���Զఴ�����س�����ջ�����
	//	Ϊʲôwindows��^dҲ������ѭ����
	while( cin >> x){	
		intArray.push_back(x);
	}

	BubbleSort( intArray );
	cout << "your input are sorted, they are:" << endl;
	for(x=0; x < intArray.size(); ++x){
		cout << intArray[x] <<'\t';
	}
	cout << endl;
	
	cout <<"***************************" <<endl;
	cout <<"now ,show insert sort." <<endl;
	intArray.clear();
	
	cout << "input some integers:" <<endl;
	
	//	cin����eof�󣬽�������������־��������Ч
	//	��cin.clear()�����־
	cin.clear();
	while( cin >> x){
		intArray.push_back(x);
	}

	InsertSort(intArray);
	cout << "your input are sorted, they are:" << endl;
	for(x=0; x < intArray.size(); ++x){
		cout << intArray[x] <<'\t';
	}
	cout << endl;

	return 0;
}