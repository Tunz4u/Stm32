#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX 5

bool queue_is_empty(ssize_t front,ssize_t rear) 
{
    if (front==-1||front>rear)return true;
    return false;
}

bool queue_is_full(int rear)
{
    if(rear==MAX-1) return true;
    return false;
}


bool queue_print(int arr[],ssize_t front,ssize_t rear) 
{
    if(queue_is_empty(front,rear)) return false;
    printf("element is : ");
    for (size_t i = front; i < (rear+1); i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return true;
}


bool enqueue(int arr[],ssize_t *front,ssize_t *rear) 
{
    if(queue_is_full(*rear)) return false;
    if(queue_is_empty(*front,*rear))
    {
        (*front)=1;
        (*rear)=0;
    }
    (*rear)++;
    printf("enter a element: ");
    scanf("%d",arr+*rear);
    return true;
}



bool dequeue(int arr[],ssize_t *front,ssize_t *rear) 
{
    if(queue_is_empty(*front,*rear))return false;
    
    arr[*front]=0;
    (*front)++;
    if(*front>*rear) 
    {
        *front=*rear=-1;
    }

    return true;
}

bool peek(const int arr[],const ssize_t front,const ssize_t rear) 
{
    if (queue_is_empty(front,rear))return false;

    printf("%d \n",arr[front]);

    return true;
}



int main ()
{
    int arr[MAX];
    ssize_t front=-1;
    ssize_t rear=-1;
    
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
            if (!enqueue(arr,&front,&rear)) printf("queue is full\n");
            break;
        case 2:
            if (!dequeue(arr,&front,&rear)) printf("array is empty\n");
            break;
        case 3:
            if (!peek(arr,front,rear)) printf("array is empty\n");
            break;
        case 4:
            if (!queue_print(arr,front,rear)) printf("array is empty\n");
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