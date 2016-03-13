#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;

const int MAXN = 111;

typedef double Matrix[MAXN][MAXN];

void gauss_elimination(Matrix A, int n) //A代表着矩阵，而n代表着一共有多少个方程组 
{
    for (int i = 0; i < n; i++)//这里其实到n - 1就可以了，因为最后一行是不用在消的。当然加上1也不会错咯。 
    {
        int r = i;
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[j][i]) > fabs(A[r][i]))
            {
                r = j;
            }
        } //这里是找到一行的对应的第i个未知量的系数绝对值最大，这样消去的时候就能避免误差，因为绝对值大， 
        if (r != i) //第二行乘的也就大，留下来是大于1的几率也就大，也就是出现小小小数的几率当然也就小咯。 
        {
            for (int j = 0; j <= n; j++)
            {
                swap(A[r][j], A[i][j]);
            }
        }
        for (int k = i + 1; k < n; k++) //开始进行消元 
        {
            double f = A[k][i] / A[i][i];//先找到一个系数，使得可以消去这第i个位置常量 
            for (int j = i; j <= n; j++)
            {
                A[k][j] -= f * A[i][j];//从i开始，每个都要消去。 
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)// 从最后一个开始带入，向上求解各个位置量，用A[i][n]来存储 
    {
        for (int j = i + 1; j < n; j++)
        {
            A[i][n] -= A[j][n] * A[i][j]; //A[j][n]就代表的是第j个未知量的解，如上所述。 
        }
        A[i][n] /= A[i][i];
    }

}


int main()
{
    Matrix A;
    int n;
    n = 2;
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 3;
    A[1][2] = 4;
    gauss_elimination(A, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d = %lf\n", i + 1, A[i][n]);
    }
    system("pause");
    return 0;
}


