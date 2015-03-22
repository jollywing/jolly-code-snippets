#include <iostream>
using namespace std;

void printSubSets(int a[], int size){
    int pass = 2 << (size - 1);
    for(int i = 0; i < pass; i++){
        int tempNum = i;
        int pos = size - 1;
        while(pos >= 0 && tempNum != 0){
            if((tempNum & 0x1) != 0){
                cout << a[pos] << " ";
            }
            tempNum = tempNum >> 1;
            pos --;
        }
        cout << endl;
    }
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    printSubSets(a, 7);
    return 0;
}
