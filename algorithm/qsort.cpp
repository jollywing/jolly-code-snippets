
#include<iostream>
using namespace std;

int Partition (int *L,int low, int high)
{
    int temp = L[low];
    int pt = L[low];
    while (low < high)
    {
        while (low < high && L[high] >= pt)
            --high;
        L[low] = L[high];
        while (low < high && L[low] <= pt)
            ++low;
        L[low] = temp;
    }
    L[low] = temp;
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

    for (int i = 1; i <= sum; i++)
        cout << narry[i] << '\t';
    cout << endl;

    int k;
    cout << "Please input place you want:" << endl;
    cin >> k;
    int aa = 1;
    int kk = 0;
    for (;;)
    {
        if (aa == k)
            break;
        if (narry[kk] != narry[kk + 1])
        {
            aa += 1;
            kk++;
        }
    }

    cout << "The NO." << k << "number is:" << narry[sum - kk] << endl;

    cout << "And it's place is:" ;
    for (i = 0;i < sum;i++)
    {
        if (addr[i] == narry[sum - kk])
            cout << i << '\t';
    }

    return 0;
}
