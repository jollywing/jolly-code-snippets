#include <iostream.h>
#include <string.h>

class landscape
{
public:
	landscape();
	void setlandscape(char *, char *);
	void printdiscript();
//	~landscape();

private:
	char * name;
	char * discript;
};

landscape::landscape()
{
	name = NULL;
	discript = NULL;
}

void landscape::setlandscape (char * n, char * d)/*ǧ������˷�������*/
{
	name = new char();/*ʹ��strcpyǰҪ��ס�����ڴ�,�����в���ָ������*/
	discript = new char();
	strcpy(name, n); //������#include <string.h>
	strcpy(discript, d);

}

void landscape::printdiscript ()
{
	cout<<name<<endl;
	cout<<discript<<endl;
	cout<<endl;
}
/*landscape::~landscape ()
{
	delete name;
	delete discript;
}*/

void main()
{
	landscape XIHU, YANGZHOU;
	XIHU.setlandscape ("����", "ɽ����ɽ¥��¥���������輸ʱ�ݣ�");
	YANGZHOU.setlandscape ("����", "����ʮ��ᣬ��������ݣ�");
	XIHU.printdiscript ();
	YANGZHOU.printdiscript ();
	return;
}
