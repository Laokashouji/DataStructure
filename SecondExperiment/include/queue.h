#include <cstdlib>

#define OK 1
#define OVERFLOW -1
#define ERROR -1
#define QUEUE_INIT_SIZE 1000
typedef int Status;

template <class ElemType>
class Queue
{
private:
    ElemType *base;
    int front;
    int rear;
    

public:
    Queue() {}
    Status InitQueue();
    Status DestoryQueue();
    Status Push(ElemType e);
    Status Pop(ElemType &e);
    Status Empty();
};



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

template <class ElemType>
Status Queue<ElemType>::Empty()
{
    return front == rear;
}