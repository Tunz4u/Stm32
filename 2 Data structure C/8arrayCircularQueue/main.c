#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX 5

bool queue_is_empty(const int size) 
{
    if (size==0)return true;
    return false;
}

bool queue_is_full(const int size)
{
    if(size==MAX) return true;
    return false;
}


bool queue_print(const int arr[],const ssize_t front,const ssize_t size) 
{
    if(queue_is_empty(size)) return false;
    ssize_t temp=front;
    printf("element is : \n");
    for (size_t i = 0; i < size; i++)
    {
        temp=(front+i)%MAX;
        printf("%d %d \n",temp,arr[temp]);
    }
    return true;
}


bool enqueue_no_overwrite(int arr[],ssize_t *front, ssize_t *size) 
{
    
    if(queue_is_full(*size)) return false;

    ssize_t rear;
    rear=(*front+*size)%MAX;
    printf("enter a element: ");
    scanf("%d",arr+rear);
    printf("%d %d\n",rear,arr[rear]);
    (*size)++;

    return true;
}



bool dequeue(int arr[],ssize_t *front,ssize_t *size) 
{
    if(queue_is_empty(*size))return false;
    
    arr[*front]=0;
    (*front)=((*front)+1)%MAX;
    (*size)--;

    return true;
}

bool peek(const int arr[],const ssize_t front,const ssize_t size) 
{
    if (queue_is_empty(size))return false;
    printf("peek is %d \n",arr[front]);
    return true;
}



int main ()
{
    int arr[MAX];
    ssize_t front=0;
    ssize_t size=0;
    
    bool out =false;
    int option=0;

    while (!out)
    {
        out=false;
        printf("Chose an option :\n");
        printf("1.enqueue\n");
        printf("2.dequeue\n");
        printf("3.peek\n");
        printf("4.print all\n");
        printf("5.out \n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            if (!enqueue_no_overwrite(arr,&front,&size)) printf("queue is full\n");
            break;
        case 2:
            if (!dequeue(arr,&front,&size)) printf("array is empty\n");
            break;
        case 3:
            if (!peek(arr,front,size)) printf("array is empty\n");
            break;
        case 4:
            if (!queue_print(arr,front,size)) printf("array is empty\n");
            break;
        case 5:
            printf("gook bai\n");
            out=true;
            break;
        default:
            printf("no valid option\n");
        }

    }
    
    return 0;
}