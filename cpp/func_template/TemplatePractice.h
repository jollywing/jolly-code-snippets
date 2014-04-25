/*=================================
	��ģ��ͺ���ģ�����ϰ
	by jiqing 2007-10-30

	note:
	һ����˵��ͷ�ļ���ֻ�ź�������
	������cpp�ļ��ж���
	������ģ��Ҫ��ͷ�ļ��ж���
 *================================*/
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <vector>
using namespace std;

/*----------------------------------
	ð������ĺ���ģ��
 ----------------------------------*/
template<class object>	//Ҳ����д��template<typename object>����һ����
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
	��������ĺ���ģ��
	����ڶ����������3���������n��
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