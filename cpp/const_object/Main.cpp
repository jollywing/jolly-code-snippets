#include "student.h"

main()
{
	cStudent stu1("黎明", "男", 25, master);
	const cStudent stu2("吴晓慧", "女", 22, master);
	stu1.PrintStudent ();
	stu2.PrintStudent();/*const成员函数可以调用const对象*/
	stu1.SetStudent ("郭靖", 40, doctor);
	/*stu2.SetStudent(...) 非const成员函数不能调用const对象*/
	stu1.PrintStudent ();

	return;
}