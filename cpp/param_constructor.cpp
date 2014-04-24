
#include <iostream>
using namespace std;

struct CLS
{
  int m_i;
  CLS( int i ) : m_i(i) {}

  // CLS()
  // {
  //   // This is not correct
  //   // It equals: CLS temp = CLS(2);
  //   CLS(2);
  // }

  CLS():CLS(2){};
};

struct STR
{
  int m_value;
  STR(int v){m_value = v;};
  STR(){STR(5);};
};

int main(int argc, char *argv[])
{
  CLS obj; // equal to: CLS obj = CLS();
  cout << obj.m_i << endl;

  CLS *obj1 = new CLS();
  cout << obj1->m_i << endl;
  delete obj1;

  STR obj2;
  cout << obj2.m_value << endl;
  STR *obj3 = new STR;
  cout << obj3->m_value << endl;
  
  return 0;
}
