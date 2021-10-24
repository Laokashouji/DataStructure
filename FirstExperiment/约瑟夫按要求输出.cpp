#include<stdio.h>
#include<stdlib.h>
struct Node{//结点结构体起手，这波稳了
    int id ;//当前位置编号
    Node *next = NULL;
};

Node *creat_and_prepare(int n);
void in(Node *head);
bool cut(Node *head,int n);
void all_out(Node *head);
int count(Node *head);
bool check(Node *head);
bool cut_next(Node *now,int move);
void Josephus(int n,int m,Node *head);
void special_Josephus(int n,Node *head);

Node * creat_and_prepare(int n){ //循环链表创建函数,并且每个结点的id为i-1
    Node *head , *current;
    head = (Node*)malloc(sizeof(Node));
    current = head ;
    for (int i = 0; i < n; i++){
        Node *temp = (Node*)malloc(sizeof(Node));
        temp ->id = i;
        current->next = temp;
        current = temp;
    }
    current ->next = head->next;
    return current;
}

void in(Node *end){//函数4 尾插入函数
    Node *temp = (Node*)malloc(sizeof(Node));
    int n = count(end);
    temp ->id = n-1;
    temp ->next = end->next;
    end ->next = temp;
}

bool cut(Node *end,int n){//函数5 按位置删除元素函数
    if(n> count(end)){
        return  0;
    }
    Node *temp = end;
    Node *del = NULL;
    int count = 0;
    while(count != n-1){
        temp = temp->next;
        count++;
    }
    del = temp->next;
    temp ->next = temp ->next->next;
    free(del);
    return 1;
}

void all_out(Node *end){//函数6 遍历输出
    int n = count(end);
    Node *temp = end;
    int count = 0;
    while (count < n){
        printf("%d ",temp->id);
        temp = temp->next;
        count++;
    }

}

int count(Node *end){//函数7 计算表长的函数
    Node *first = end;
    Node *count = end->next;
    int count_number = 0;
    while(count != first){
        count = count->next;
        count_number++;
    }
    return count_number+1;
}

bool check(Node *end){//函数8 判断是否为空表
    if(count(end) == 1){
        return 1;
    }else return 0;
}

bool cut_next(Node *now,int move){//删除下一个结点
    printf("<%d,%d>\n",(now->next->id)+1,move);
    Node *temp = now;
    Node *del = NULL;
    del = temp->next;
    temp ->next = temp ->next->next;
    free(del);
    return 1;
    //all_out(now);
}

void Josephus(int n,int m,Node *end){
    Node *temp =end;
    int step = 1;
    int all_step = 0;
    while(count(temp) != 1){
        if(step == m){
            cut_next(temp,all_step);
            step = 1;
        }
        temp = temp->next;
        step++;
        all_step++;
    }
//    printf("the luck guy is %d\n",(temp->id)+1);
//    printf("step = %d",all_step);
}

void special_Josephus(int n,Node *head){
    Node *temp =head;
    int all_step = 0;
    while(count(temp) != 1){
        cut_next(temp,all_step);
    }
//    printf("the luck guy is %d\n",(temp->id)+1);
//    printf("step = %d",all_step);
}

int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    Node *test = creat_and_prepare(N);
    //printf("size = %d\n", count(test));
    if(M == 1){
        special_Josephus(1,test);
    }else{
        Josephus(N,M,test);
    }
    return 0;
}
