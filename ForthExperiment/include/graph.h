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
    int next, nextf;  //同一顶点的边的下一条边的编号
    int etime, ltime; //边的最早和最晚开始时间
public:
    Edge(int f = 0, int t = 0, int l = 0, int n = 0, int et = 0, int lt = 0) : from(f), to(t), length(t), next(n), etime(et), ltime(lt) {}
    int _next() { return next; }
    int _nextf() { return nextf; }
    int _from() { return from; }
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
    int head[MaxNodeSize];                   //保存图中以该顶点为起点的最后一条边的编号
    int tail[MaxNodeSize];                   //保存图中以该顶点为终点的最后一条边的编号

public:
    void init();                                                            //初始化图
    void addEdge(int x, int y, int z, int tot);               //链式前向星加边
    int nsize(){ return n;}                                              //返回图的顶点数
    Graph reverse();                                                    //反转边的起点和终点
    friend bool dijkstra(Graph &G);                            //求最短路
    friend bool AOE(Graph &G);                                 //求关键路径
    friend void dfs(Graph &G, bool *vis, int x);            //求与x连通的点
    friend void print_path(int path[], const Graph &G, int s); //打印路径
};