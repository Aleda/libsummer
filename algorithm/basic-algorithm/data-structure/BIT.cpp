/*
 *  *这是一个随意编出来的树状数组,
 *   *很简单的函数,就三个,一个lowbit, 一个getnum, 一个motify()
 *    *主要是他实现的思路
 *     */ 


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const int maxn = 111;

int c[111];

int N;

int M;

int  LowBit(int t)
{
    return t & (-t);
}


int getNum(int p)//求和的时候注意是从大向小来求和 
{
    int sum = 0;
    while (p > 0)
    {
        sum += c[p];
        p -= LowBit(p);
    }
    return sum;
}

int Motify(int p, int b)
{
    while (p <= N) //这里一定注意要把你最大的范围都更新了,如果只更新到N的话,那么大于你给定的范围的话就出不来正确的
       // 结果了,比如,你就5个数字,如果让你求1-6的和,如果你没有更新到最大的话,是输出不了的,也就是输出的是错误
            //的答案的,如果你把范围扩展到最大的话,就不会出现这样的错误了 
    {
        c[p] += b;
        p += LowBit(p);
    }
}


int main()
{
    while (scanf("%d%d", &N, &M) != EOF)
    {
        int a, b;
        for (int i = 1; i <= N; i++)//注意是从1开始的,不是从零开始 
        {
            scanf("%d", &a);
            Motify(i, a);
        }
        char s[11];
        for (int i = 1; i <= M; i++)
        {
            scanf("%s", s);
            if (s[0] == 'Q')
            {
                scanf("%d%d", &a, &b);
                int ans = getNum(b) - getNum(a - 1);
                printf("%d\n", ans);
            }
            else if (s[0] == 'M')
            {
                scanf("%d%d", &a, &b);
                Motify(a, b);
            }
            for (int i = 1; i <= N; i++)
            {
                printf("c[%d] = %d\n", i, c[i]);
            }
        }
    }
    system("pause");
    return 0;
}

