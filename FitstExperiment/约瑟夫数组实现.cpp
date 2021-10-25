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
    ElemType *data; /* 数组，存储数据元素 */
    int length;     /* 线性表当前长度 */
} SqList;

Status Visit(ElemType c);                         /*访问数组的第i个元素*/
Status InitList(SqList *L);                       /* 初始化顺序线性表 */
Status ListEmpty(SqList L);                       /*若L为空表，则返回TRUE，否则返回FALSE */
Status ListLength(SqList L, int *length);          /*用length返回L中数据元素个数 */
Status GetElem(SqList L, int i, ElemType *e);     /* 用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status ListInsert(SqList *L, int i, ElemType e);  /* 在L中的位置i插入元素e */
Status ListDelete(SqList *L, int i, ElemType *e); /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListTraverse(SqList L);                    /* 操作结果：依次对L的每个数据元素输出 */
Status Destory(SqList *L);                        /*销毁数组*/
int main()
{
    SqList People, Ans, Move; //分别存储约瑟夫环，删除数字，移动次数
    InitList(&People);
    InitList(&Ans);
    InitList(&Move);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++)
    {

    }
        return 0;
}

Status visit(ElemType c)
{
    printf("%d ", c);
    return OK;
}
Status InitList(SqList *L)
{
    L->length = 0;
    L->data = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    return OK;
}
Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}
Status ListLength(SqList L,int *length)
{
    *length = L->length;
    return OK;
}
Status GetElem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;
    *e = L.data[i - 1];

    return OK;
}
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAXSIZE) /* 顺序线性表已经满 */
        return ERROR;
    if (i < 1 || i > L->length + 1) /* 当i比第一位置小或者比最后一位置后一位置还要大时 */
        return ERROR;

    if (i <= L->length) /* 若插入数据位置不在表尾 */
    {
        for (k = L->length - 1; k >= i - 1; k--) /* 将要插入位置之后的数据元素向后移动一位 */
            L->data[k + 1] = L->data[k];
    }
    L->data[i - 1] = e; /* 将新元素插入 */
    L->length++;  

    return OK;
}
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0) /* 线性表为空 */
        return ERROR;
    if (i < 1 || i > L->length) /* 删除位置不正确 */
        return ERROR;
    *e = L->data[i - 1];
    if (i < L->length) /* 如果删除不是最后位置 */
    {
        for (k = i; k < L->length; k++) /* 将删除位置后继元素前移 */
            L->data[k - 1] = L->data[k];
    }
    L->length--;
    return OK;
}
Status ListTraverse(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}
Status Destory(SqList *L)
{
    L->length = -1;
    free(L->data);
    return OK;
}
