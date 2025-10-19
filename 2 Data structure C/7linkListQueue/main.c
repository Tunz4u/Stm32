#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
//Function Declaration 
//bool
struct node
{
  int data;
  struct node* next;
};
struct node* front = NULL;
struct node* rear = NULL;


bool isempty()
{
    bool isempty = false;
    
    if(front == NULL)
    {
        printf("\nQueue is Empty\n");
        isempty = true;
    }
    return isempty;
}


void enqueue()//insert queue
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
 
    if(temp!=NULL)
    {
        printf("Enter the data to insert:");
        scanf("%d",&temp->data);

        
        if(front == NULL)//empty queue
        {
            front = temp;
            rear = temp;
            temp->next=NULL;
        }
        else
        {
            rear->next=temp;
            rear=temp;
            rear->next=NULL;//rear->next=NULL;
        }   
    }
}


void dequeue()
{
    if(isempty())
    {
        printf("underflow\n");
    }
    else
    {
        struct node* temp = front;
        printf("The deleted element from queue is:%d\n",temp->data);
        if(front==rear)
        {
            front = NULL;
            rear = NULL;
            free(temp);
        }
        else
        {
            front=front->next;
            free(temp);
        }
    }
}


void display()
{
    struct node* traverse =front;
    if(isempty())
    {
        printf("No node\n");
    }
    else
    {
        printf("The list is:");
        for(traverse;traverse!=NULL;)
        {
            printf("%d ",traverse->data);
            traverse=traverse->next;
        }
        printf("\n");

    }
}
void peek()
{
    printf("First element in the queue is:%d\n", front->data);
}



int main()
{
    int choice;
    printf("***Queue  Implementation using Singly LinkedList***\n");
    
    while (1)
    {
        printf("1.Insert element to queue (Enqueue) \n");
        printf("2.Delete element from queue (Dequeue) \n");
        printf("3.Display all elements of queue \n");
        printf("4.Display the first element in the queue \n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                peek();
                break;
            default:
                printf ("\nPlease Enter a Valid Choice\n ");
        }
    }
} 