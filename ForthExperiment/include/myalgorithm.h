#pragma once

#include "graph.h"

#define INF 0x3f3f3f3f

bool dijkstra(Graph &G); //求最短路
bool AOE(Graph &G); //求关键路径
void dfs(Graph &G, bool *vis, int x);//求与x连通的点
void AOE_init(Graph &G, bool *pre, int s, int e);//重构图删除无关节点, 以求局部AOE路径

