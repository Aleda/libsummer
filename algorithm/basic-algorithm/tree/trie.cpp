#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const int MAXNODE = 1000000 + 11;

const int SEGMA_SIZE = 26;

struct Trie
{
    int ch[MAXNODE][SEGMA_SIZE];
    int val[MAXNODE];
    int size;
    Trie()
    {
        size = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    void clear()
    {
        size = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int idx(char c) // Çó³ö×Ö·ûËù¶ÔÓ¦µÄid 
    {
        return c - 'a';
    }
    void insert(char *s, int v)
    {
        int n = strlen(s);
        int u = 0;
        for (int i = 0; i < n; i++)
        {
            int id = idx(s[i]);
            if (!ch[u][id])
            {
                memset(ch[size], 0, sizeof(ch[size]));
                val[size] = 0;
                ch[u][id] = size++;
            }
            u = ch[u][id];
        }
        val[u] = v;
    }
    int search(char *s)
    {
        int n = strlen(s);
        int u = 0;
        for (int i = 0; i < n; i++)
        {
            int id = idx(s[i]);
            if (!ch[u][id])
            {
                return 0;
            }
            u = ch[u][id];
        }
        if (val[u] == 1)
        {
            return 1;
        }
    }

}trie;

//int main()
//{
    //char str[111];
    //int N, M;
    //while (scanf("%d%d", &N, &M) != EOF)
    //{
        //trie.clear();
        //for (int i = 0; i < N; i++)
        //{
            //scanf("%s", str);
            //trie.insert(str, 1);
        //}
        //for (int i = 0; i < M ; i++)
        //{
            //scanf("%s", str);
            //int ans = trie.search(str);
            //if (ans == 1)
            //{
                //printf("The string exists\n");
            //}
            //else
            //{
                //printf("The string doesn`t exist\n");
            //}
        //}
    //}
    //system("pause");
    //return 0;
//}
