#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool arr_is_empty(size_t top) 
{
    if (top==0)return true;
    return false;
}

bool arr_is_full(size_t top, size_t len_max) 
{
    if (top==len_max)return true;
    return false;
}
void arr_initialize(int arr[], size_t len_max, int value) 
{

    for (size_t i = 0; i < len_max; i++)
    {
        arr[i]=value;
    }
    
}


bool arr_print(const int arr[], size_t top) 
{
    if(arr_is_empty(top)) return false;
    printf("element is : ");
    for (size_t i = 0; i < top; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return true;
    
}

bool arr_push(int arr[], size_t *top, size_t len_max) 
{
    if (arr_is_full(*top,len_max)) return false;
    printf("Push to array:");
    scanf("%d",arr+(*top));
    (*top)++;
    return true;
}

bool arr_pop(int arr[], size_t *top) 
{
    if(arr_is_empty(*top)) return false;
    arr[*top]=0;
    (*top)--;
    return true;
}

bool arr_peek(const int arr[], size_t top) 
{
    if(arr_is_empty(top)) return false;
    printf("peek array is %d\n",arr[top - 1]);
    return true;
}



int main ()
{
    int arr[5];
    size_t top=0;
    size_t len_max=5;
    arr_initialize(arr,len_max,0);
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
            if (!arr_push(arr,&top,len_max)) printf("array is full\n");
            break;
        case 2:
            if (!arr_pop(arr,&top)) printf("array is empty\n");
            break;
        case 3:
            if (!arr_peek(arr,top)) printf("array is empty\n");
            break;
        case 4:
            if (!arr_print(arr,top)) printf("array is empty\n");
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