#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -1
#define ERROR -1
#define STACK_INIT_SIZE 100
#define STACKINCREAMENT 10

typedef int Status;

template <class ElemType>
class Stack
{
private:
    ElemType *base;
    ElemType *top;
    int stacksize;

public:
    Stack() {}
    Status InitStack();
    Status DestoryStack();
    Status Push(ElemType e);
    Status Pop(ElemType &e);
};

template <class ElemType>
class Queue
{
private:
    Stack<ElemType> PushStack;
    Stack<ElemType> PopStack;

public:
    Status InitQueue();
    Status DestoryQueue();
    Status Push(ElemType e);
    Status Pop(ElemType &e);
};

int main()
{
    Queue<int> q;
    q.InitQueue();
    printf("�����ʽ\n1 num\t----\t���Ԫ��num \n2\t----\t����Ԫ�س���\n3\t----\t����\n");
    int order;
    int flag = 0;
    do
    {
        printf("���������");
        scanf("%d", &order);
        switch (order)
        {
        case 1:
            scanf("%d", &order);
            if (q.Push(order) == OK)
                printf("���Ԫ��%d\n", order);
            else
                printf("�����������Ϸ������������룡\n");
            break;
        case 2:
            if (q.Pop(order) == OK)
                printf("����Ԫ��%d\n", order);
            else
                printf("�����������Ϸ������������룡\n");
            break;
        case 3:
            flag = 1;
            break;
        default:
            printf("�����������Ϸ������������룡\n");
            break;
        }
    } while (!flag);

    q.DestoryQueue();

    return 0;
}
template <class ElemType>
Status Stack<ElemType>::InitStack()
{
    base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!base)
        exit(OVERFLOW);
    top = base;
    stacksize = STACK_INIT_SIZE;
    return OK;
}
template <class ElemType>
Status Stack<ElemType>::DestoryStack()
{
    free(base);
    top = NULL;
    stacksize = -1;
    return OK;
}
template <class ElemType>
Status Stack<ElemType>::Push(ElemType e)
{
    if (top - base >= stacksize)
    {
        base = (ElemType *)realloc(base, (stacksize + STACKINCREAMENT) * sizeof(ElemType));
        if (!base)
            exit(OVERFLOW);
        top = base + stacksize;
        stacksize += STACKINCREAMENT;
    }
    *top++ = e;
    return OK;
}
template <class ElemType>
Status Stack<ElemType>::Pop(ElemType &e)
{
    if (top == base)
        return ERROR;
    e = *--top;
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::InitQueue()
{
    PushStack.InitStack();
    PopStack.InitStack();
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::DestoryQueue()
{
    PopStack.DestoryStack();
    PushStack.DestoryStack();
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::Push(ElemType e)
{
    PushStack.Push(e);
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::Pop(ElemType &e)
{
    if (PopStack.Pop(e) == ERROR)
    {
        ElemType t;
        if (PushStack.Pop(t) == ERROR)
            return ERROR;
        else
            do
                PopStack.Push(t);
            while (PushStack.Pop(t) != ERROR);
    }
    PopStack.Pop(e);
    return OK;
}