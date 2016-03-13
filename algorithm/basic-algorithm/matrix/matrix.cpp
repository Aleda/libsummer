#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;


struct Matrix
{
    const static int MAXN = 200;
    int data[MAXN][MAXN];
    int n, m;
    int MOD;
    Matrix()
    {
        n = 3;
        m = 3;
        MOD = 110100;
    }
    /*
     *  Matrix(int a, int b, int mod)
     *      {
     *              n = a;
     *                      m = b;
     *                              MOD = mod;
     *                                  }
     *                                      */
    Matrix operator * (const Matrix &t) const 
    {
        Matrix e;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                e.data[i][j] = 0;
                for (int k = 0; k < m; k++)
                {
                    e.data[i][j] += (long long)data[i][k] * t.data[k][j] % MOD;
                }
                e.data[i][j] %= MOD;
            }
        }
        return e;
    }
    Matrix setE()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                data[i][j] = (i == j) ? 1 : 0;
            }
        }

    }
    Matrix print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf(j == m - 1 ? "%d\n" : "%d ", data[i][j]);
            }
        }
    }
    Matrix readData()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &data[i][j]);
            }
        }
    }

};

//int main()
//{
//Matrix m;
//m.readData();
//Matrix n;
//n.readData();
//m.print();
//n.print();
//Matrix  temp = m * n;
//temp.print();
//system("pause");
//return 0;
//}
