#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <string>

/*
 * SPFA是可以判断负环的：加入某点的次数大于n-1的时候肯定是存在负环的。
 * 所以SPFA是个很不错的万能算法； 
 * */

using namespace std;

const int MAXN = 100 + 11;

const int MAXE = MAXN * MAXN;

const int INF = 0x3fffffff;

int inq[MAXN];

int use[MAXN]; 

int N, M;

int idx;

int d[MAXN];

int head[MAXN];

struct Edge
{
    int from;
    int to;
    int val;
    int next;
}e[MAXE];

queue <int> Q;


void addEdge(int from, int to, int val)
{
    e[idx].from = from;
    e[idx].to = to;
    e[idx].val = val;
    e[idx].next = head[from];
    head[from] = idx++;
}

void init()
{
    for (int i = 0; i <= N; i++)
    {
        d[i] = INF;
    }
    memset(head, -1, sizeof(head));
    memset(inq, 0, sizeof(inq));
    memset(use, 0, sizeof(use));
    idx = 0;
    while (!Q.empty())
    {
        Q.pop();
    }
}

int SPFA(int start)
{
    Q.push(start);
    d[start] = 0;
    inq[start] = 1;
    use[start]++;
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        inq[v] = 0;
        for (int i = head[v]; i != -1; i = e[i].next)
        {
            int from = e[i].from;
            int to = e[i].to;
            int val = e[i].val;
            if (d[v] + val < d[to])
            {
                d[to] = d[v] + val;
                if (!inq[to])
                {
                    Q.push(to);
                    use[to]++;
                    if (use[to] >= N)
                    {
                        return -1;
                    }
                    inq[to] = 1;
                }
            }
        }
    }
    return 1;
}

//int main()
//{
    //while (scanf("%d%d", &N, &M) != EOF)
    //{
        //int a, b, val;
        //init();
        //for (int i = 0; i < M; i++)
        //{
            //scanf("%d%d%d", &a, &b, &val);
            //addEdge(a, b, val); //这次我建立单向边； 
        //}
        //int start, end;
        //scanf("%d%d", &start, &end);
        //int ans = SPFA(start);
        //if (ans == -1)
        //{
            //printf("This graph has a negtive circle!");
        //}
        //else
        //{
            //printf("the ans is : %d\n", d[end]);
        //}
    //}
    //system("pause");
    //return 0;
//}
/*
 * 4 4
 * 1 2 2
 * 2 3 1
 * 3 4 4
 * 4 2 -5
 * 1
 * 3
 *
 * 4 4
 * 1 2 2
 * 2 3 1
 * 3 4 4
 * 4 2 -6
 * 1
 * 3
 * */

