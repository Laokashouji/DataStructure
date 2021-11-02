//单文件版
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

#define MAXM 100
#define MAXN 100
#define MAX_ARRAY_DIM 8 //数组维数的最大值

template <class ElemType>
struct Stack
{
    int st[MAXM + MAXN + 5];
    Stack()
    {
        memset(st, 0, sizeof(st));
    }
};

template <class ElemType>
struct Queue
{
    int q[MAXM + MAXN + 5];
    Queue()
    {
        memset(q, 0, sizeof(q));
    }
};

template <class ElemType>
struct Array //按列优先顺序存储
{
    ElemType **a;
    int dim;    //数组维数
    int *bounds;    //数组各维的长度
    







    Array(int m = 0, int n = 0) : m(m), n(n)
    {
    }
    void init(int m, int n)
    {
        a = (int *)malloc(m * sizeof(int *));
        for (int i = 0; i < n; i++)
            a[m]
    }
    void assign()
    {
    }
};
int main()
{
    int map[MAXN][MAXM];
    int m, n;
    printf("请输入迷宫的行数：");
    scanf("%d", &m);
    printf("请输入迷宫的列数：");
    scanf("%d", &n);
    
    printf("下面请输入迷宫（通道为0，墙为1）：\n");

    int sx, sy, tx, ty; //分别为入口和出口的行列左边
    printf("请输入迷宫的起点坐标：");
    scanf("%d%d", &sx, &sy);
    printf("请输入迷宫的终点坐标：");
    scanf("%d%d", &tx, &ty);

    return 0;
}
