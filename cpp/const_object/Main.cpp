#include "student.h"

main()
{
	cStudent stu1("����", "��", 25, master);
	const cStudent stu2("������", "Ů", 22, master);
	stu1.PrintStudent ();
	stu2.PrintStudent();/*const��Ա�������Ե���const����*/
	stu1.SetStudent ("����", 40, doctor);
	/*stu2.SetStudent(...) ��const��Ա�������ܵ���const����*/
	stu1.PrintStudent ();

	return;
}