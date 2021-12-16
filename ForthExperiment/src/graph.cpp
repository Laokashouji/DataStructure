#include "graph.h"
#include "myiostream.h"
#include <cstring>
#include <iostream>
#include <fstream>

#define MaxfilenameLength 50

using namespace std;
//初始化图
void Graph::init()
{
    //选择输入源
    char filename[MaxfilenameLength];
    ifstream in;
    if (read_mode(filename))
    {
        in.open(filename);
        if (!in)
        {
            printf("Failed to open file!");
            return;
        }
    }
    //读入图
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> data[i];
    int x, y, z;
    memset(head, 0, sizeof(head));
    memset(tail, 0, sizeof(tail));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y, z, i);
    }
    char st[MaxNodeNameSize], ed[MaxNodeNameSize];
    cin >> st >> ed;
    int flag = 0;
    for (int i = 0; i < n; i++)
        if (!strcmp(st, data[i]))
            s = i, flag++;
        else if (!strcmp(ed, data[i]))
            e = i, flag++;
        else if (flag == 2)
            break;

    if (in)
        in.close();
}

//链式前向星加边
void Graph::addEdge(int x, int y, int z, int tot)
{
    edges[tot].from = x;
    edges[tot].to = y;
    edges[tot].length = z;
    edges[tot].next = head[x];
    edges[tot].nextf = tail[y];
    head[x] = tot;
    tail[y] = tot;
}

Graph Graph::reverse()
{
    Graph G;
    G.m = m, G.s = e, G.e = s, G.n = n;
    memcpy(G.data, data, sizeof(data));
    int tot=0;
    for (int i = 1; i <= m; i++)
    {
        Edge &e = edges[i];
        G.addEdge(e.to, e.from, e.length, i);
    }
    return G;
}