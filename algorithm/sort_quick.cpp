
#include<iostream>
using namespace std;

int Partition (int *L,int low, int high)
{
    while(low < high){
        int pt = L[low];
        while (low < high && L[high] >= pt)
            --high;
        L[low] = L[high];

        while (low < high && L[low] <= pt)
            ++low;

        L[high] = L[low];
        L[low] = pt;
    }
    return low;
}

void QSort (int *L, int low, int high)
{
    if (low < high)
    {
        int pl = Partition (L,low,high);
        QSort(L, low, pl - 1);
        QSort(L, pl + 1, high);
    }
}

int main(int argc, char *argv[])
{
    int narry[100], addr[100];
    int sum = 1, t;
    int i;

    cout << "Input number:" << endl;
    cin >> t;
    while (t != -1)
    {
        narry[sum] = t;
        addr[sum - 1] = t;
        sum ++;
        cin >> t;
    }

    sum -= 1;

    QSort (narry, 1, sum);

    for (i = 1; i <= sum; i++)
        cout << narry[i] << '\t';
    cout << endl;

    return 0;
}
