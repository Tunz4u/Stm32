#include <stdio.h>    // printf, scanf
#include <stdlib.h>   // malloc, calloc, free (cho array động)
#include <stdbool.h>
enum checkElement
{
    full,
    notfull,
    notValid,
};

void arrayFill(int arr[],size_t sizeOfArray,int input)
{
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        arr[i]=input;
    }
}

void traverse(const int arr[],size_t len)
{
    printf("element is ");
    for (size_t i = 0; i < len; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void arr_from_input(int arr[], size_t *len, size_t sizeOfArray)
{
    printf("enter length: ");
    scanf("%zu",len);
    if (*len > sizeOfArray) *len = sizeOfArray;
    for (size_t i = 0; i < *len; i++)
    {
        printf("enter %zu element: ",i);
        scanf("%d",arr+i);
    }
}


bool arr_push_back(int arr[], size_t *len, size_t len_max)
{
    if(*len >= len_max) return false;
    printf("enter %zu puselement: ",*len);
    scanf("%d",arr+*len);
    (*len)++;
    traverse(arr,*len);
    return true;
}

enum checkElement arr_insert_at(int arr[], size_t *len, size_t len_max, size_t i, int x)
{
    if(*len==len_max) return full;
    if(i>*len) return notValid;
    for (size_t n=*len; n > i; n--)
    {
        arr[n]=arr[n-1];
    }
    arr[i]=x;
    (*len)++;
    traverse(arr,*len);
    return notfull;

}
bool arr_pop_back(int arr[],size_t *len)
{
    
    if(*len==0) return false;
    (*len)--;
    arr[*len]=0;
    traverse(arr,*len);
    return true;
}

enum checkElement arr_delete_at(int arr[], size_t *len, size_t i)
{
    if(i>=*len) return notValid;
    (*len)--;
    for (i; i < *len; i++)
    {
        arr[i]=arr[i+1];
    }
    arr[*len] = 0;
    traverse(arr,*len);
    return notfull;
}

bool arr_delete_value(int arr[], size_t *len, int x)
{
    int matchValueIndex=-1;
    for (size_t i = 0; i < *len; i++)
    {
        if(x==arr[i])
        {
            matchValueIndex=i;
            break;
        }
    }

    if (matchValueIndex==-1)
    {
        return false;
    }
    else
    {
        (*len)--;
        for (size_t i =matchValueIndex; i < *len; i++)
        {
            arr[i]=arr[i+1];
        }
        traverse(arr,*len);
        return true;
    }
    
}

bool arr_find_linear(const int arr[], size_t len, int x)
{
    int matchValueIndex=-1;
    for (size_t i = 0; i < len; i++)
    {
        if(x==arr[i])
        {
            matchValueIndex=i;
            break;
        }
    }
    
    if(matchValueIndex==-1) return false;

    traverse(arr,len);
    printf("here       ");
    for (size_t i = 0; i < matchValueIndex; i++)
    {
        printf("  ");
    }
    
    printf("|\n");
    return true;

}

bool arr_update(int arr[], size_t len, size_t i, int x)
{
    if(i>=len) return false;
    arr[i]=x;
    traverse(arr,len);
    return true;
}

void swap(int*x, int*y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}

void arr_reverse(int arr[], size_t len)
{
    int right=(len-1);

    for (size_t i = 0; i < len/2; i++)
    {
        swap(&(arr[i]),&(arr[right]));
        right--;
    }

    traverse(arr,len);
}

void arr_bubble_sort(int arr[], size_t len)
{
    if (len < 2) return;
    size_t x=len;
    bool swapped=false;
    do
    {
        swapped =false;
        for (size_t i = 0; i < x-1; i++)
        {
            if (arr[i]>arr[i+1])
            {
                swap(&(arr[i]),&(arr[i+1]));
                swapped=true;
            } 
        }

        x--;

    } while (swapped);
    
    traverse(arr,len);
}

void arr_selection_sort(int arr[],size_t len)
{
    size_t x=0;
    size_t i=0;
    
    for ( i = 0; i < len-1; i++)
    {
        x=i;
        for (size_t j = i+1; j < len; j++)
        {
            if (arr[x]>arr[j])
            {
                x=j;
            }
        }

        if(x!=i) 
        {
            swap(&arr[x],&arr[i]);
        }
    }
    traverse(arr,len);

}

void arr_insertion_sort(int arr[],size_t len)
{
    int key=0;
    int currentIndex=0;
    for (int i = 1; i < len; i++)
    {
        currentIndex=i;
        key=arr[i];
        for (currentIndex ; currentIndex>=0; currentIndex--)
        {
            if (arr[currentIndex-1]>key)
            {
                arr[currentIndex]=arr[currentIndex-1];
            }
            else if(currentIndex==0 ||arr[currentIndex-1]<=key)
            {
                arr[currentIndex]=key;
                break;
            }
            
        }
    
    }
    traverse(arr,len);
    
}
ssize_t arr_find_binary(const int arr[], size_t len, int x)
{
    int low=0;
    int high=len-1;
    int mid=(high-low)/2;

    while (low <= high) {
         mid = (high + low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }
    
    return -1;
    

}



int main()
{
    int arr[6];
   
    size_t size = sizeof(arr) / sizeof(arr[0]);
    //arrayFill(arr,size,99);
    size_t index=0;
    //arr_from_input(arr,&index,size);
  
    

    if(!arr_push_back(arr,&index,size))
    {
        printf("full array\n");
    } 
    
    if(!arr_push_back(arr,&index,size))
    {
        printf("full array\n");
    } 

    //if(!arr_pop_back(arr,&index)) printf ("no element in array\n");

    if(!arr_push_back(arr,&index,size))
    {
        printf("full array\n");
    } 



    // enum checkElement check1 = arr_insert_at(arr,&index,size,0,7);

    // if(check1== full)
    // {
    //     printf("full array\n");
    // }
    // else if(check1== notValid)
    // {
    //     printf("not valid at 2 \n");
    // }

    // enum checkElement check2 = arr_delete_at(arr,&index,0);

    // if(check2== notValid)
    // {
    //     printf("not valid in array\n");
    // }

    // int x=1;
    // if(!arr_delete_value(arr,&index,x))
    // {
    //     printf("not found %d in array\n",x);
    // } 

    if(!arr_push_back(arr,&index,size))
    {
        printf("full array\n");
    } 

    // if(!arr_find_binary(arr,index,x))
    // {
    //     printf("not found %d in array\n",x);
    // } 

    // if(!arr_update(arr,index,1,x))
    // {
    //     printf("out of arr");
    // }

    arr_reverse(arr,index);
    //arr_bubble_sort(arr,index);
    
    if(!arr_push_back(arr,&index,size))
    {
        printf("full array\n");
    } 
    //arr_selection_sort(arr,index);
    arr_insertion_sort(arr,index);
    printf("dđ");
    int findBinary =arr_find_binary(arr,index,5);
    if (findBinary==-1)
    {
        printf("not found %d in array\n",findBinary);
    }
    else
    {
        printf("%d in index : %d\n",5,findBinary);
    }
    traverse(arr,index);
    return 0;
    
}