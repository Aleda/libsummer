#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const int INF = 0x3fffffff;

const int MAXN = 100 + 11; //当点数小于1000的时候用矩阵还可以。 

int N, M;

int vis[MAXN];

int dis[MAXN];

int map[MAXN][MAXN];

int fa[MAXN];

void dijkstra(int start)
{
    for (int i = 1; i <= N; i++) //将所有的点都设置成INF 
    {
        dis[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
    dis[start] = 0; //源点设置成dis[start] = 0; 
    for (int i = 1; i <= N; i++)
    {
        int pos;
        int t = INF;
        for (int j = 1; j <= N; j++) //找到dis最小的值 
        {
            if (!vis[j] && t > dis[j])
            {
                t = dis[j];
                pos = j;
            }
        }
        vis[pos] = 1;
        for (int j = 1; j <= N; j++) //更新dis周围的所有点。 
        {
            if (!vis[j] && dis[j] > dis[pos] + map[pos][j] && map[pos][j] != 0x3f3f3f3f)
            {
                dis[j] = dis[pos] + map[pos][j];
                fa[j] = pos; //记录最短路径的路径 
            }
        }
    }
}

//int main()
//{
    //while (scanf("%d%d", &N, &M) != EOF)
    //{
        //int a, b, val;
        //memset(map, 0x3f, sizeof(map));
        //for (int i = 0; i < M; i++)
        //{
            //scanf("%d%d%d", &a, &b, &val);
            //if (map[a][b] > val)//判断重边 
            //{
                //map[a][b] = val;
                //map[b][a] = val;
            //}
        //}
        //dijkstra(1); //SSSP单源最短路。可以求出他能走到的所有点最短距离。 
        //int n;
        //scanf("%d", &n);
        //printf("%d\n", dis[n]);
        //printf("The road to %d is : \n", n);
        //int v = n;
        /*
         *      for (int i = 1; i <= N; i++)
         *              {
         *                          printf("%d--->%d\n", i, fa[i]);
         *                                  }
         *                                          */
        //while (v != 1 && v != 0)
        //{
            //printf("%d--->%d\n", v, fa[v]); //从终点打印最短路径。 
            //v = fa[v];
        //}
        //cout << endl;
    //}
    //system("pause");
    //return 0;
//}

