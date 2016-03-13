#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 100;

int d[MAXN];

int LIS(int *A, int LEN)
{
    int len = 0;
    d[0] = A[0];
    for (int i = 1; i < LEN; i++)
    {
        if (A[i] > d[len]) //严格递增 
        {
            d[++len] = A[i]; 
        }
        else
        {
            int t = lower_bound(d, d + len, A[i]) - d;
            d[t] = A[i];
        }
    }
    return len + 1;
}

//int main()
//{
    //int N;
    //int A[MAXN];
    //while (scanf("%d", &N) != EOF)
    //{
        //for (int i = 0; i < N; i++)
        //{
            //scanf("%d", &A[i]);
        //}
        /*
         *      如果是字符串也好说，就是用个for循环换成整形数组就行了，一样的道理。 
         *              */
        //int ans = LIS(A, N);
        //printf("The longest length about this array is : %d\n", ans);
        //printf("They are:\n");
        //for (int i = 0; i < ans; i++)
        //{
            //printf("%d ", d[i]);
        //}
        //printf("\n");
    //}
    //system("pause");
    //return 0;
//}

