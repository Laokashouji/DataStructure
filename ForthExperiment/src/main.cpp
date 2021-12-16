#include <cstdio>
#include "graph.h"
#include "myalgorithm.h"
#include "myiostream.h"

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt","w",stdout);
    Graph G;
    G.init();
    if (!dijkstra(G))
    {
        printf("There is no short_path!");
        return 0;
    }
    if (!AOE(G))
        printf("There is no critical_path!");

    return 0;
}

