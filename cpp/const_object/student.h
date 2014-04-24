
enum degree {master, doctor};	/*ö�ٱ����Ķ���*/

class cStudent
{
public:
	cStudent(char * = "", char * = "",int = 0, enum degree = master);
	void SetStudent(char * n, int a, enum degree d);
	char * GetName() const;	//const��ʾ����ı�������ݳ�Ա��
	int GetAge() const;
	enum degree GetDegree() const;
	void PrintStudent() const;

private:
	char * strName;
	const char * strSex;
	int nAge;
	enum degree eDegree;

};