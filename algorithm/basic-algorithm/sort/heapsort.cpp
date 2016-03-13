#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

void print(int *a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    cout << endl;
}

void heapify(int *a, int x, int n)
{
    int l = x << 1;
    int r = x << 1 | 1;
    int largest;
    if (l <= n && a[l] > a[x])
    {
        largest = l;
    }
    else 
    {
        largest = x;
    }
    if (r <= n && a[r] > a[largest])
    {
        largest = r;
    }
    if (largest != x)
    {
        int t = a[largest];
        a[largest] = a[x];
        a[x] = t;
        heapify(a, largest, n);
    }
}

void buildHeap(int *a, int n)
{
    //在堆中（也就是完全二叉树中），叶子结点的数目应当等于总结点数目（n - n / 2), 所以非叶子结点的数目为n/2（下整） 
    for (int i = n / 2; i >= 1; i--)
    {
        heapify(a, i, n);
    }
}

void heapSort(int *a, int n)
{
    buildHeap(a, n);
    print(a, n);
    for (int i = n; i > 1; i--)
    {
        int t = a[i];
        a[i] = a[1];
        a[1] = t;
        heapify(a, 1, i - 1);
    }
}

int main()
{
    int n;
    int a[100];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) //由于创建堆的时候，根结点的编号是从1开始的，所以如果依旧按照从0开始编写序号的话，就不方便 
    {
        scanf("%d", &a[i]);
    }
    heapSort(a, n);
    print(a, n);
    return 0;
}
