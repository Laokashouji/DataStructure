//���ļ���
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

#define MAXM 100
#define MAXN 100
#define MAX_ARRAY_DIM 8 //����ά�������ֵ

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
struct Array //��������˳��洢
{
    ElemType **a;
    int dim;    //����ά��
    int *bounds;    //�����ά�ĳ���
    







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
    printf("�������Թ���������");
    scanf("%d", &m);
    printf("�������Թ���������");
    scanf("%d", &n);
    
    printf("�����������Թ���ͨ��Ϊ0��ǽΪ1����\n");

    int sx, sy, tx, ty; //�ֱ�Ϊ��ںͳ��ڵ��������
    printf("�������Թ���������꣺");
    scanf("%d%d", &sx, &sy);
    printf("�������Թ����յ����꣺");
    scanf("%d%d", &tx, &ty);

    return 0;
}
