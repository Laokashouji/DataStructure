#pragma once

#define MaxNodeSize 10000
#define MaxEdgeSize 20000
#define MaxNodeNameSize 10
//采用链式前向星存图进行dijkstra,
class Edge
{
private:
    int from, to;     //边的起点和终点
    int length;       //边的长度
    int next;         //同一顶点的边的下一条边的编号
    int etime, ltime; //边的最早和最晚开始时间
public:
    Edge(int f = 0, int t = 0, int l = 0, int n = 0, int et = 0, int lt = 0) : from(f), to(t), length(t), next(n), etime(et), ltime(lt) {}
    int _next() { return next; }
    int _to() { return to; }
    int _length() { return length; }
    friend class Graph;
};

class Graph
{
private:
    int n, m;                                //图的顶点数和边数, 最多有MaxNodeSize个点和MaxEdgeSize条边
    int s, e;                                //起点和终点的编号
    char data[MaxNodeSize][MaxNodeNameSize]; //每个顶点的data, 名字长度最长为MaxNodeNameSize
    Edge edges[MaxEdgeSize];                 //保存图中所有的边
    int head[MaxNodeSize];                   //保存图中每个顶点的第一条边的编号
    // int dis[MaxNodeSize];//保存从该点到

public:
    void init();
    void addEdge(int x, int y, int z, int &tot);
    friend bool dijkstra(Graph &G);
    friend void print_minpath(int path[], const Graph &G, int s);
};