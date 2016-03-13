#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

/*
 *  *这个问题是我独自想清楚的，其实只要自己动脑筋，其实许多问题都是可以解决的，下一步需要解决的就是大于10位数的
 *   *四则运算，这个运算只能解决一位数的四则运算还是比较不方便的。一会就得自己学着解决大数问题的四则运算。
 *    */ 

using namespace std;

const int MAXN = 1000;

int lch[MAXN];

int rch[MAXN];

char op[MAXN];

int nc;

int buildTree(char *s, int x, int y)
{
    int c1 = -1;
    int c2 = -1;
    int p = 0;
    if (x == y)
    {
        int u = nc++;
        lch[u] = 0;
        rch[u] = 0;
        op[u] = s[x];
        return u;
    }
    for (int i = x; i <= y; i++)
    {
        switch (s[i])
        {
            case '(' : p++; break;
            case ')' : p--; break;
            case '+' : case '-' : if (!p) c1 = i; break; //c1表示最右边的+ -的标号， 
            case '*' : case '/' : if (!p) c2 = i; break; //c2表示最右边的* /的标号。 
        }
    }
    if (c1 < 0) //如果右边没有+ -的话，那就得取* /; 
    {
        c1 = c2;
    }
    if (c1 < 0) //如果也没有* /的话，而且并不是一个简单的数字，那就说明肯定有括号。 
    {
        return buildTree(s, x + 1, y - 1);
    }
    int u = nc++;
    lch[u] = buildTree(s, x, c1 - 1);
    rch[u] = buildTree(s, c1 + 1, y);
    op[u] = s[c1];
    return u;
}

void init()
{
    nc = 0;
}

int BFS(int root) // BFS求解BFS的结果（仔细想，问题非常的奇妙） 
{
    switch (op[root])
    {
        case '+' : return BFS(lch[root]) + BFS(rch[root]); break;
        case '-' : return BFS(lch[root]) - BFS(rch[root]); break;
        case '*' : return BFS(lch[root]) * BFS(rch[root]); break;
        case '/' : return BFS(lch[root]) / BFS(rch[root]); break;
    }
    return op[root] - '0';
}

//int main()
//{
    //char str[123]; 
    //while (scanf("%s", str) != EOF)
    //{

        //init();
        //int len = strlen(str);
        //int root = buildTree(str, 0, len - 1);
        /*
         *      for (int i = 0; i < nc; i++)
         *              {
         *                          printf("i = %d op[i] = %c\n", i, op[i]);
         *                                  }
         *                                          */
        //int ans = BFS(root);
        /*
         *      int o1, o2;
         *              int ans = op[0] - '0';
         *                      int cnt = 0;
         *                              while (cnt + 2 < nc)
         *                                      {
         *                                                  cnt += 2;
         *                                                              switch (op[cnt])
         *                                                                          {
         *                                                                                          case '+' : ans += op[cnt - 1] - '0'; break;
         *                                                                                                          case '-' : ans -= op[cnt - 1] - '0'; break;
         *                                                                                                                          case '*' : ans *= op[cnt - 1] - '0'; break;
         *                                                                                                                                          case '/' : ans /= op[cnt - 1] - '0'; break;
         *                                                                                                                                                      }
         *                                                                                                                                                              }
         *                                                                                                                                                                      //这样的方法是不行的 例如2+4*2 
         *                                                                                                                                                                              */
        //printf("ans = %d\n", ans);
    //}
    //system("pause");
    //return 0;
//}

