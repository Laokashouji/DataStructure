#include <queue>
#include <cstring>
#include "myalgorithm.h"
using namespace std;

bool dijkstra(Graph &G)
{
    // d保存每个点到起点的最短路, 除起点的最短路为0外, 其他点初始化为INF
    int d[MaxNodeSize];
    memset(d, 0x3f, sizeof(d));
    d[G.s] = 0;

    // p保存每个点在最短路中的前驱节点
    int path[MaxNodeSize];
    memset(path, -1, sizeof(path));
    //用优先队列+链式前向星的dijkstra算法提高速度
    // pair第一维保存该点的最小距离的相反数以使距离最小的优先级最高, 第二维保存点的编号
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, G.s));

    // v保存该点是否访问过
    int v[MaxNodeSize];
    memset(v, 0, sizeof(v));

    //开始dijkstra
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (v[x])
            continue;
        v[x] = 1;
        for (int i = G.head[x]; i; i = G.edges[i]._next())
        {
            int y = G.edges[i]._to(), z = G.edges[i]._length();
            if (d[y] > d[x] + z)
            {
                d[y] = d[x] + z;
                path[y] = x;
                q.push(make_pair(-d[y], y));
            }
        }
    }

    //输出最短路
    if (d[G.e] < INF)
    {
        print_minpath(path, G, G.e);
        return true;
    }
    return false;
}
