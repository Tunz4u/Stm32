#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;



bool arr_is_empty(Node **stack) 
{
    if (*stack==NULL)return true;
    return false;
}



bool arr_print(Node**stack) 
{
    if (*stack==NULL)return false;
    printf("element is : ");
    Node *temp=*stack;
    do
    {
        printf("%d ",temp->data);
        temp=temp->next;

    } while (temp!=NULL);

    printf("\n");
    return true;
    
}


bool arr_push(Node **stack) 
{
    Node *newNode=(Node*)calloc(1,sizeof(Node));
    if (newNode == NULL) return false;    // Lỗi: Không cấp phát được bộ nhớ

    printf("Enter data of new node:");
    scanf("%d",&(newNode->data));
    
    if (*stack==NULL)
    {
        newNode->next=NULL;
        *stack=newNode;
    }
    else
    {
        newNode->next=*stack;
        *stack=newNode;
    }
    return true;
}

bool arr_pop(Node **stack) 
{
    if (*stack==NULL)return false;

    Node*temp;
    temp=*stack;
    *stack=(*stack)->next;
    free(temp);

    return true;
}

bool arr_peek(Node**stack) 
{
    if (*stack==NULL)return false;

    printf("%d \n",(*stack)->data);

    return true;
}



int main ()
{
    Node *stack=NULL;

    bool out =false;
    int option=0;

    while (!out)
    {
        out=false;
        printf("Chose an option :\n");
        printf("1.push\n");
        printf("2.pop\n");
        printf("3.peek\n");
        printf("4.print all\n");
        printf("5.out \n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            if (!arr_push(&stack)) printf("fail to stack array\n");
            break;
        case 2:
            if (!arr_pop(&stack)) printf("array is empty\n");
            break;
        case 3:
            if (!arr_peek(&stack)) printf("array is empty\n");
            break;
        case 4:
            if (!arr_print(&stack)) printf("array is empty\n");
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