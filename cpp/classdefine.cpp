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

void landscape::setlandscape (char * n, char * d)/*千万别忘了返回类型*/
{
	name = new char();/*使用strcpy前要记住分配内存,括号中不必指定数量*/
	discript = new char();
	strcpy(name, n); //别忘了#include <string.h>
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
	XIHU.setlandscape ("西湖", "山外青山楼外楼，西湖歌舞几时休！");
	YANGZHOU.setlandscape ("扬州", "腰缠十万贯，骑鹤下扬州！");
	XIHU.printdiscript ();
	YANGZHOU.printdiscript ();
	return;
}
