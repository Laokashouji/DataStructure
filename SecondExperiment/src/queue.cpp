#include <cstdio>
#include <cstdlib>
#include "queue.h"

template <class ElemType>
Status Queue<ElemType>::InitQueue()
{
    base = (ElemType *)malloc(QUEUE_INIT_SIZE * sizeof(ElemType));
    if (!base)
        exit(OVERFLOW);
    front = rear = 0;
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::DestoryQueue()
{
    if(base)
        free(base);
    base = NULL;
    front = rear = 0;
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::Push(ElemType e)
{
    if((rear + 1) % QUEUE_INIT_SIZE == front)
        return ERROR;
    base[rear] = e;
    rear = (rear + 1) % QUEUE_INIT_SIZE; 
    return OK;
}
template <class ElemType>
Status Queue<ElemType>::Pop(ElemType &e)
{
    if(front == rear)
        return ERROR;
    e = base[front];
    front = (front + 1) % QUEUE_INIT_SIZE;
    return OK;
}