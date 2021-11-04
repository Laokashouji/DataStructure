//单文件版
#pragma clang diagnostic ignored "-Winvalid-source-encoding"

#include <cstdio>
#include <cstring>
#include "array.h"
#include "stack.h"
#include "queue.h"
struct stackpoint
{
    int x, y;
    int d; //方向
    stackpoint(int x = 0, int y = 0, int d = 0) : x(x), y(y), d(d)
    {
    }
};
struct queuepoint
{
    int x, y;
    int pre[QUEUE_INIT_SIZE / 5];
    int l;
    queuepoint(int x = 0, int y = 0, int l = 0) : x(x), y(y), l(l)
    {
        memset(pre, 0, sizeof(pre));
    }
};
int hash(int x, int y)
{
    return x * 100 + y;
}
void uhash(int num, int &x, int &y)
{
    x = num / 100;
    y = num % 100;
    return;
}

char ud[4][10] = {"东", "南", "西", "北"};
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

bool Is_Visit(int x, int y, const queuepoint &p);
void Print_DFS_Answer(Stack<stackpoint> &S, int x, int y);
void Print_BFS_Answer(queuepoint &p, int tot);
void MY_DFS(Array<int> map, int sx, int sy, int tx, int ty);
void MY_BFS(Array<int> map, int sx, int sy, int tx, int ty); //使用哈希将路径存入每个点以保证可以找到全部路径
int main()
{
    Array<int> map1, map2;

    //freopen("in2.txt", "r", stdin); //调试用
    //freopen("out2.txt","w",stdout);
    int m, n;
    printf("请输入迷宫的行数：");
    scanf("%d", &m);
    printf("请输入迷宫的列数：");
    scanf("%d", &n);
    map1.InitArray(2, m + 2, n + 2);
    map2.InitArray(2, m + 2, n + 2);

    int Elem;
    printf("下面请输入迷宫（通道为0，墙为1）：\n");
    for (int i = 0; i <= m + 1; i++)
        for (int j = 0; j <= n + 1; j++)
        {
            if (!(i && j) || i == m + 1 || j == n + 1)
                Elem = 1;
            else
                scanf("%d", &Elem);
            map1.Assign(&Elem, i, j);
            map2.Assign(&Elem, i, j);
        }

    int sx, sy, tx, ty; //分别为入口和出口的行列坐标
    printf("请输入迷宫的起点坐标：");
    scanf("%d%d", &sx, &sy);
    printf("请输入迷宫的终点坐标：");
    scanf("%d%d", &tx, &ty);

    MY_DFS(map1, sx, sy, tx, ty);
    MY_BFS(map2, sx, sy, tx, ty);
    //记得休息一下嗷
    map1.DestroyArray();
    map2.DestroyArray();
    return 0;
}

bool Is_Visit(int x, int y, const queuepoint &p)
{
    int h = hash(x, y);
    for (int i = 0; i < p.l; i++)
    {
        if (h == p.pre[i])
            return true;
    }
    return false;
}
void Print_DFS_Answer(Stack<stackpoint> &S, int x, int y)
{
    if (S.Empty())
        return;
    stackpoint ans;
    S.Pop(ans);
    Print_DFS_Answer(S, ans.x, ans.y);
    printf("(%d,%d)向%s移动到达(%d,%d)\n", ans.x, ans.y, ud[ans.d], x, y);
}
void MY_DFS(Array<int> map, int sx, int sy, int tx, int ty)
{
    Stack<stackpoint> S;
    S.InitStack();
    stackpoint now(sx, sy, -1);
    S.Push(now);
    //标记访问
    int vis = -1;

    while (!S.Empty())
    {
        S.Pop(now);

        int Elem;
        now.d++;
        while (now.d < 4)
        {
            map.Value(&Elem, now.x + dx[now.d], now.y + dy[now.d]);
            if (Elem != 0)
            {
                now.d++;
                continue;
            }
            S.Push(now);
            map.Assign(&vis, now.x, now.y);

            now.x += dx[now.d];
            now.y += dy[now.d];
            if (now.x == tx && now.y == ty) //输出答案
            {
                printf("\nDFS找到的路径为:\n");
                Print_DFS_Answer(S, tx, ty);
                S.DestoryStack();
                return;
            }
            else
            {
                now.d = 0;
            }
        }
    }
    printf("找不到路径\n");
    return;
}
void Print_BFS_Answer(queuepoint &p, int tot)
{
    printf("\n路径#%d:\n", tot);
    int x, y, xx, yy, d;
    uhash(p.pre[0], x, y);
    for (int i = 1; i < p.l; i++)
    {
        uhash(p.pre[i], xx, yy);
        d = xx - x == 0 ? (yy - y + 3) % 4 : (xx - x + 4) % 4;
        printf("(%d,%d)向%s移动到达(%d,%d)\n", x, y, ud[d], xx, yy);
        x = xx, y = yy;
    }
    xx = p.x, yy = p.y;
    d = xx - x == 0 ? (yy - y + 3) % 4 : (xx - x + 4) % 4;
    printf("(%d,%d)向%s移动到达(%d,%d)\n", x, y, ud[d], xx, yy);
    return;
}
void MY_BFS(Array<int> map, int sx, int sy, int tx, int ty)
{
    printf("\nBFS找到的路径为:\n");
    Queue<queuepoint> Q;
    queuepoint now;
    int Elem;
    int tot = 0; //编号路径

    Q.InitQueue();
    Q.Push(queuepoint(sx, sy, 0));

    int xx, yy;
    while (!Q.Empty())
    {
        Q.Pop(now);
        if (now.x == tx && now.y == ty)
        {
            tot++;
            Print_BFS_Answer(now, tot);
            continue;
        }

        for (int d = 0; d < 4; d++)
        {
            xx = now.x + dx[d], yy = now.y + dy[d];
            map.Value(&Elem, xx, yy);
            if (Elem != 0 || Is_Visit(xx, yy, now))
                continue;
            queuepoint p = now;
            p.pre[p.l++] = hash(now.x, now.y);
            p.x = xx, p.y = yy;
            Q.Push(p);
        }
    }

    Q.DestoryQueue();
    return;
}