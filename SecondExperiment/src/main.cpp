//单文件版
#pragma clang diagnostic ignored "-Winvalid-source-encoding"

#include <cstdio>
#include "array.h"
#include "stack.h"
#include "queue.h"
struct point
{
    int x, y;
    int d; //方向
    point(int x = 0, int y = 0, int d = 0)
    {
        this->x = x;
        this->y = y;
        this->d = d;
    }
};
const int direction[] = {0, 1, 2, 3};
char ud[4][10] = {"东", "南", "西", "北"};
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void Print_DFS_Answer(Stack<point> &S, int x, int y);
void MY_DFS(Array<int> map, int sx, int sy, int tx, int ty);

int main()
{
    Array<int> map;
    Queue<point> Q;

    //freopen("in.txt", "r", stdin); //调试用

    int m, n;
    printf("请输入迷宫的行数：");
    scanf("%d", &m);
    printf("请输入迷宫的列数：");
    scanf("%d", &n);
    map.InitArray(2, m + 2, n + 2);

    int Elem;
    printf("下面请输入迷宫（通道为0，墙为1）：\n");
    for (int i = 0; i <= m + 1; i++)
        for (int j = 0; j <= n + 1; j++)
        {
            if (!(i && j) || i == m + 1 || j == n + 1)
                Elem = 1;
            else
                scanf("%d", &Elem);
            map.Assign(&Elem, i, j);
        }

    int sx, sy, tx, ty; //分别为入口和出口的行列坐标
    printf("请输入迷宫的起点坐标：");
    scanf("%d%d", &sx, &sy);
    printf("请输入迷宫的终点坐标：");
    scanf("%d%d", &tx, &ty);

    MY_DFS(map, sx, sy, tx, ty); 
    //记得休息一下嗷
    return 0;
}
void Print_DFS_Answer(Stack<point> &S, int x, int y)
{
    if (S.Empty())
        return;
    point ans;
    S.Pop(ans);
    Print_DFS_Answer(S, ans.x, ans.y);
    printf("(%d,%d)向%s移动到达(%d,%d)\n", ans.x, ans.y, ud[ans.d], x, y);
}
void MY_DFS(Array<int> map, int sx, int sy, int tx, int ty)
{
    Stack<point> S;
    S.InitStack();
    point now(sx, sy, -1);
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
