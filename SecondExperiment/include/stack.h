#include <cstdlib>
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
    Status Top(ElemType &e);
    Status Empty();
};




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
    stacksize = 0;
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
Status Stack<ElemType>::Empty()
{
    return top == base;
}

template <class ElemType>
Status Stack<ElemType>::Top(ElemType &e)
{
    if (top == base)
        return ERROR;
    e = *top;
    return OK;
}