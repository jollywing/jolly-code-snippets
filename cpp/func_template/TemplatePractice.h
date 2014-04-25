/*=================================
	类模板和函数模板的练习
	by jiqing 2007-10-30

	note:
	一般来说，头文件里只放函数声明
	函数在cpp文件中定义
	但函数模板要在头文件中定义
 *================================*/
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <vector>
using namespace std;

/*----------------------------------
	冒泡排序的函数模板
 ----------------------------------*/
template<class object>	//也可以写成template<typename object>，是一样的
void BubbleSort( vector<object> & objectArray )
{
	int i, j;
	object t;

	for( i=1; i<objectArray.size(); ++i){
		for( j=0; j < objectArray.size() - i; ++j){
			if(objectArray[j] > objectArray[j+1]){
				t = objectArray[j];
				objectArray[j] = objectArray[j+1];
				objectArray[j+1] = t;
			}
		}
	}
}

/*-----------------------------------
	插入排序的函数模板
	插入第二个，插入第3个，插入第n个
 -----------------------------------*/
template<typename object>
void InsertSort( vector<object> &objectArray )
{
	int i, j;
	object t;

	for( i = 1; i<objectArray.size(); ++i){
		//get a element
		t = objectArray[i];
		//if previous element larger than t, move backward
		for(j=i; objectArray[j-1]>t && j>0; --j)
			objectArray[j] = objectArray[j-1];
		objectArray[j] = t;
	}	
}

#endif