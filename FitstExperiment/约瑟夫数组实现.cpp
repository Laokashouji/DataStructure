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
    ElemType *data; /* ���飬�洢����Ԫ�� */
    int length;     /* ���Ա�ǰ���� */
} SqList;

Status Visit(ElemType c);                         /*��������ĵ�i��Ԫ��*/
Status InitList(SqList *L);                       /* ��ʼ��˳�����Ա� */
Status ListEmpty(SqList L);                       /*��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListLength(SqList L, int *length);          /*��length����L������Ԫ�ظ��� */
Status GetElem(SqList L, int i, ElemType *e);     /* ��e����L�е�i������Ԫ�ص�ֵ,ע��i��ָλ�ã���1��λ�õ������Ǵ�0��ʼ */
Status ListInsert(SqList *L, int i, ElemType e);  /* ��L�е�λ��i����Ԫ��e */
Status ListDelete(SqList *L, int i, ElemType *e); /* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListTraverse(SqList L);                    /* ������������ζ�L��ÿ������Ԫ����� */
Status Destory(SqList *L);                        /*��������*/
int main()
{
    SqList People, Ans, Move; //�ֱ�洢Լɪ�򻷣�ɾ�����֣��ƶ�����
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
    if (L->length == MAXSIZE) /* ˳�����Ա��Ѿ��� */
        return ERROR;
    if (i < 1 || i > L->length + 1) /* ��i�ȵ�һλ��С���߱����һλ�ú�һλ�û�Ҫ��ʱ */
        return ERROR;

    if (i <= L->length) /* ����������λ�ò��ڱ�β */
    {
        for (k = L->length - 1; k >= i - 1; k--) /* ��Ҫ����λ��֮�������Ԫ������ƶ�һλ */
            L->data[k + 1] = L->data[k];
    }
    L->data[i - 1] = e; /* ����Ԫ�ز��� */
    L->length++;  

    return OK;
}
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0) /* ���Ա�Ϊ�� */
        return ERROR;
    if (i < 1 || i > L->length) /* ɾ��λ�ò���ȷ */
        return ERROR;
    *e = L->data[i - 1];
    if (i < L->length) /* ���ɾ���������λ�� */
    {
        for (k = i; k < L->length; k++) /* ��ɾ��λ�ú��Ԫ��ǰ�� */
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
