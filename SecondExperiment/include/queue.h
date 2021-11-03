#define OK 1
#define OVERFLOW -1
#define ERROR -1
#define QUEUE_INIT_SIZE 100
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
};
