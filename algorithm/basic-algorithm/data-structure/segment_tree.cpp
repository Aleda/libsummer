#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const int MAXNODE = 1000 * 4;

struct Tree
{
    int val;
    int L, R;
}tree[MAXNODE];

void pushUp(int i)
{
    tree[i].val = max(tree[i << 1].val, tree[i << 1 | 1].val);
}

void buildTree(int i, int L, int R)
{
    tree[i].L = L;
    tree[i].R = R;
    tree[i].val = 0;
    if (L == R)
    {
        int val;
        scanf("%d", &val); 
        tree[i].val = val;
        return ;
    }
    int mid = L + (R - L) / 2;
    buildTree(i << 1, L, mid);
    buildTree(i << 1 | 1, mid + 1, R);
    pushUp(i); 
}

void update(int i, int key, int val)
{
    if (tree[i].L == key && tree[i].R == key)
    {
        tree[i].val = val;
        return ; 
    }
    int mid = tree[i].L + (tree[i].R - tree[i].L) / 2;
    if (key <= mid)
    {
        update(i << 1, key, val);
    }
    else
    {
        update(i << 1 | 1, key, val);
    }
    pushUp(i);
}

int query(int i, int L, int R)
{
    if (L <= tree[i].L && R >= tree[i].R)
    {
        return tree[i].val;
    }
    int mid = tree[i].L + (tree[i].R - tree[i].L) / 2;
    if (R <= mid)
    {
        return query(i << 1, L, R);
    }
    else if (L > mid)
    {
        return query(i << 1 | 1, L, R);
    }
    else
    {
        return max(query(1 << 1, L, mid), query(i << 1 | 1, mid + 1, R));
    }
}


//int main()
//{
    //int N, M;
    //while (scanf("%d%d", &N, &M) != EOF)
    //{
        //buildTree(1, 1, N);
        //int temp;
        //int a, b;
        //for (int i = 0; i < M; i++)
        //{
            //scanf("%d", &temp);
            //if (temp == 0)
            //{
                //scanf("%d%d", &a, &b);
                //update(1, a, b);
            //}
            //else
            //{
                //scanf("%d%d", &a, &b);
                //int ans = query(1, a, b);
                //printf("The ans is : %d\n", ans);
            //}
        //}

    //}
    //system("pause");
    //return 0;
//}
