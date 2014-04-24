/*=================================
	类模板和函数模板的练习
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

	//	linux用^d (ctrl+d)结束输入
	//	windows用^z(ctrl+z)结束输入
	//	每次敲回车，都会用cin.get()读取缓冲区数据
	//	当缓冲区有数据时，^z也不能结束输入
	//	^z不会放入缓冲区，^z前可以多按几个回车以清空缓冲区
	//	为什么windows下^d也会跳出循环？
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
	
	//	cin遇到eof后，将设置流结束标志，不再有效
	//	用cin.clear()清除标志
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