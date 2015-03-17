/*-------------------------------------------------------------
 * name: go_through_list.cpp
 * desc: two methods of going through list.
 * author: jiqing Wu. 2007-10-06
 *----------------------------------------------------------*/
#include <stdio.h>

struct listElement
{
	int m_data;
	listElement * next;
};

//typedef struct listElement ListElement;

void go_through_list_while(listElement *);
void go_through_list_for(listElement *);
void delete_list( listElement *);

int main()
{
	listElement * listRoot = new listElement;
	listRoot->m_data = 0;
	
	listElement * temp = listRoot;
	int i;
	for(i = 1; i<= 10; ++i)
	{
		temp->next = new listElement;
		temp = temp->next;
		temp->m_data = i;
	}
	temp->next = 0;
	
	go_through_list_while(listRoot);
	go_through_list_for(listRoot);
	
	delete_list(listRoot);
	return 0;
}

void delete_list(listElement * root)
{
	if (!root)
		return;
		
	listElement * temp, * temp_next;
	temp = root;
	while (temp != 0)
	{
		temp_next = temp->next;
		printf("delete node %d. \n", temp->m_data);
		delete temp;
		temp = temp->next;
	}
}

void go_through_list_while( listElement* root)
{
 	listElement *p;
 	p=root;
 	while(p!=NULL)
 	{
 	     	printf("%d\t", p->m_data);
 	     	p = p -> next; 
 	}
 	printf("\n");
}

void go_through_list_for( listElement* root)
{
	listElement *p;
	for(p = root; p != NULL; p = p->next)
	{
	 	printf("%d\t",p->m_data);	 	
	}
	printf("\n it is  too easy!\n");	
	
}

