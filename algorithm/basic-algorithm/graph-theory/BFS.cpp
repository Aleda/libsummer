#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

const int maxv = 111;

const int maxe = 1111;

int N;

int M;

int head[maxv];

struct Edge
{
    int v;
    int wight;
    int next;
}e[maxe];

int idx;

int vis[maxv];

void Init()
{
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    idx = 0;

}

void addEdge(int a, int b)
{
    e[idx].v = b;
    //e[idx].wight = val;
    e[idx].next = head[a];
    head[a] = idx++;
}

void BFS(int x)
{
    queue <int > q;
    q.push(x);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        if (!vis[x])//从队列里面拿出来的点也是要判断一下的,因为可能存进去的是同一个点 
        {
            vis[x] = 1;//这个点已经被访问了,因为你建的是双向图; 
            cout << x << endl;
        }
        else
        {
            continue;
        }
        int p = head[x];
        while (p != -1)
        {
            int v = e[p].v;
            if (!vis[v])//如果没有被访问才放进去,如果已经访问了,就不能放进去了,要不然就无线循环了 
            {
                q.push(v);
            }
            p = e[p].next;
        }
    }
}


int main()
{
    while (scanf("%d%d", &N, &M) != EOF)
    {
        Init();
        int a, b;
        for (int i = 1; i <= M; i++)
        {
            scanf("%d%d", &a, &b);
            addEdge(a, b);
            addEdge(b, a);
        }
        BFS(1);
    } 
    system("pause");
    return 0;
}

