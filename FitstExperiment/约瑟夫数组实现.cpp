#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;   /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType; /* ElemType���͸���ʵ������������������Ϊint */

typedef struct
{
    ElemType *data;    /* ���飬�洢����Ԫ�� */
    int length, start; /* ���Ա�ǰ������Ԫ�ؿ�ʼ���� */
} SqList;

inline int min(int a, int b)
{
    return a < b ? a : b;
}
Status InitList(SqList *L);                                     /* ��ʼ��˳�����Ա� */
Status ListEmpty(SqList L);                                     /*��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListLength(SqList L, int *length);                       /*��length����L��length */
Status ListStart(SqList L, int *start);                         /*��start����L��start*/
Status GetElem(SqList L, ElemType *e);                          /* ��e����L�����һ��Ԫ��*/
Status ListInsert(SqList *L, ElemType e);                       /* ��L�е�������Ԫ��e */
Status ListDelete(SqList *L, int i, ElemType *e, int *movenum); /* ��L��ɾ����i��Ԫ�أ���������������Ԫ�ظ���ѡ���ٵ�һ���ƶ�*/
Status ListTraverse(SqList L);                                  /* ������������ζ�L��ÿ������Ԫ����� */
Status ListPrint(SqList L, int i);                              /*���L�ĵ�i��Ԫ��*/
Status Destory(SqList *L);                                      /*��������*/
int main()
{
    SqList People, Ans, Move; //�ֱ�洢Լɪ�򻷣�ɾ�����֣��ƶ�����
    InitList(&People);
    InitList(&Ans);
    InitList(&Move);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        ListInsert(&People, i);
    int seats = -1, cnt = 0; //�ֱ�洢Ŀǰ������λ��������
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
    if (L->length - L->start <= 0) /* ���Ա�Ϊ�� */
        return ERROR;
    if (i < L->start || i >= L->length) /* ɾ��λ�ò���ȷ */
        return ERROR;
    *e = L->data[i];
    if (i - (L->start) < (L->length - 1) - i) /*�����ߵ�Ԫ�ظ��پͽ���ߵ�Ԫ��������*/
    {
        for (k = i - 1; k >= L->start; k--) /* ��ɾ��λ�ú��Ԫ��ǰ�� */
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
