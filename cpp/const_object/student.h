
enum degree {master, doctor};	/*枚举变量的定义*/

class cStudent
{
public:
	cStudent(char * = "", char * = "",int = 0, enum degree = master);
	void SetStudent(char * n, int a, enum degree d);
	char * GetName() const;	//const表示不会改变类的数据成员。
	int GetAge() const;
	enum degree GetDegree() const;
	void PrintStudent() const;

private:
	char * strName;
	const char * strSex;
	int nAge;
	enum degree eDegree;

};