#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const int maxe = 10011;

const int maxn = 111;

const int INF = 0x3fffffff;

int K;

int N;

int R;

struct Edge
{
    int v;
    int length;
    int val;
    int next;
}e[maxe];

int head[maxn];

int vis[maxn];

int min_len;

int idx;

void init()
{
    idx = 0;
    min_len = INF;
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
}

void addEdge(int a, int b, int length, int val)
{
    e[idx].v = b;
    e[idx].length = length;
    e[idx].val = val;
    e[idx].next = head[a];
    head[a] = idx++;
}

void DFS(int v, int now_len, int now_money)
{
    if (now_len >= min_len)
    {
        return ;
    }
    if (v == N && now_len < min_len)
    {
        min_len = now_len;
        return ;
    }
    int p = head[v];
    while (p != -1)
    {
        int point = e[p].v;
        int len = e[p].length;
        int money = e[p].val;
        if (!vis[point] && now_money + money <= K)
        {
            vis[point] = 1;
            DFS(point, now_len + len, now_money + money);
            vis[point] = 0;
        }
        p = e[p].next;
    }
    return ;
}
int main()
{
    while (scanf("%d", &K) != EOF)
    {
        init();
        scanf("%d", &N);
        scanf("%d", &R);
        int S, D, L, T;
        for (int i = 0; i < R; i++)
        {
            scanf("%d%d%d%d", &S, &D, &L, &T);
            addEdge(S, D, L, T);
            //addEdge(D, S, L, T);
        }
        DFS(1, 0, 0);
        printf("%d\n", min_len);
    }
    return 0;
}

