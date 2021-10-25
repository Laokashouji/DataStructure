#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

typedef struct
{
    ElemType *data;    /* 数组，存储数据元素 */
    int length, start; /* 线性表当前长度与元素开始坐标 */
} SqList;

inline int min(int a, int b)
{
    return a < b ? a : b;
}
Status InitList(SqList *L);                                     /* 初始化顺序线性表 */
Status ListEmpty(SqList L);                                     /*若L为空表，则返回TRUE，否则返回FALSE */
Status ListLength(SqList L, int *length);                       /*用length返回L的length */
Status ListStart(SqList L, int *start);                         /*用start返回L的start*/
Status GetElem(SqList L, ElemType *e);                          /* 用e返回L的最后一个元素*/
Status ListInsert(SqList *L, ElemType e);                       /* 在L中的最后插入元素e */
Status ListDelete(SqList *L, int i, ElemType *e, int *movenum); /* 在L中删除第i个元素，并根据左右两边元素个数选择少的一边移动*/
Status ListTraverse(SqList L);                                  /* 操作结果：依次对L的每个数据元素输出 */
Status ListPrint(SqList L, int i);                              /*输出L的第i个元素*/
Status Destory(SqList *L);                                      /*销毁数组*/
int main()
{
    SqList People, Ans, Move; //分别存储约瑟夫环，删除数字，移动次数
    InitList(&People);
    InitList(&Ans);
    InitList(&Move);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        ListInsert(&People, i);
    int seats = -1, cnt = 0; //分别存储目前数到的位置与人数
    int length, start;
    while (!ListEmpty(People))
    {
        ListLength(People, &length);
        ListStart(People, &start);
        while (cnt != m)
        {
            seats++;
            if (seats >= length)
                seats = start;
            cnt++;
        }
        int num, movenum;
        ListDelete(&People, seats, &num, &movenum);
        ListInsert(&Ans, num);
        GetElem(Move, &num);
        ListInsert(&Move, num + movenum);
        ListStart(People, &num);
        ListLength(People, &num);
        if (num < length)
            seats--;
        cnt = 0;
    }
    for (int i = 0; i < Ans.length; i++)
    {
        printf("<");
        ListPrint(Ans, i);
        printf(",");
        ListPrint(Move, i);
        printf(">\n");
    }
    return 0;
}

Status InitList(SqList *L)
{
    L->length = 0;
    L->start = 0;
    L->data = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    return OK;
}
Status ListEmpty(SqList L)
{
    if (L.length - L.start == 0)
        return TRUE;
    else
        return FALSE;
}
Status ListLength(SqList L, int *length)
{
    (*length) = L.length;
    return OK;
}
Status ListStart(SqList L, int *start)
{
    (*start) = L.start;
    return OK;
}
Status GetElem(SqList L, ElemType *e)
{
    *e = 0;
    if (L.length - L.start <= 0)
        return ERROR;
    *e = L.data[L.length - 1];

    return OK;
}
Status ListInsert(SqList *L, ElemType e)
{
    if (L->length >= MAXSIZE)
        return ERROR;
    L->data[(L->length)++] = e;
    return OK;
}
Status ListDelete(SqList *L, int i, ElemType *e, int *movenum)
{
    int k;
    *movenum = 0;
    if (L->length - L->start <= 0) /* 线性表为空 */
        return ERROR;
    if (i < L->start || i >= L->length) /* 删除位置不正确 */
        return ERROR;
    *e = L->data[i];
    if (i - (L->start) < (L->length - 1) - i) /*如果左边的元素更少就将左边的元素往右移*/
    {
        for (k = i - 1; k >= L->start; k--) /* 将删除位置后继元素前移 */
        {
            L->data[k + 1] = L->data[k];
            (*movenum)++;
        }
        L->start++;
    }
    else
    {
        for (k = i + 1; k < (L->length); k++)
        {
            L->data[k - 1] = L->data[k];
            (*movenum)++;
        }
        L->length--;
    }
    return OK;
}
Status ListTraverse(SqList L)
{
    int i;
    for (i = L.start; i < L.length; i++)
        ListPrint(L, i);
    printf("\n");
    return OK;
}
Status ListPrint(SqList L, int i)
{
    printf("%d", L.data[i]);
    return OK;
}
Status Destory(SqList *L)
{
    L->length = -1;
    L->start = 0;
    free(L->data);
    return OK;
}
