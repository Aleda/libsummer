#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int N;

int a[10000];

void Quick_Sort (int  low, int high)
{
    if (low < high) //这个注意一定要写上,因为如果没有这个条件的话,将会出现无限循环的情况 
    {
        int i = low; // 这是两个动态的指针 
        int j = high;
        int pivot = a[low]; // 将这个关键之存到pivot里面 
        int pos = low; //这个指针是指向空缺的可以插入的位置上 
        while (i < j)
        {
            while (a[j] > pivot)
            {
                j--;
            }
            a[pos] = a[j];
            a[j] = pivot;
            pos = j;
            while (a[i] < pivot)
            {
                i++;
            }
            a[pos] = a[i];
            a[i] = pivot;
            pos = i;
        }
        Quick_Sort (low, pos - 1); // 这是递归调用算法 
        Quick_Sort (pos + 1, high);
    }
}

int main()
{
    cout << "Input the number that you want be sorted : " << endl;
    cin >> N;
    cout << "Please input the numbers : " << endl;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    Quick_Sort (0, N - 1);
    for (int  i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    system ("pause");
    return 0;
}


