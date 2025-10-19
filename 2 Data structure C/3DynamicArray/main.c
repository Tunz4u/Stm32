#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void arr_initialize(int **arr, size_t len_max)
{
    *arr=calloc(len_max,sizeof(int));

    if (*arr == NULL)  // Kiểm tra cấp phát thất bại
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

}

void arr_fill(int **arr, size_t len_max, int value)
{
    *arr=malloc(len_max*sizeof(int));

    if (*arr == NULL)  // Kiểm tra cấp phát thất bại
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (size_t i = 0; i < len_max; i++)
    {
        (*arr)[i]=value;
    }
  
}

void arr_from_input(int **arr,size_t *len, size_t len_max)
{
    *arr=malloc(len_max*sizeof(int));

    if (*arr == NULL)  // Kiểm tra cấp phát thất bại
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    int value=0;

    for (size_t i = 0; i < len_max; i++)
    {
        printf("enter %zu element: ",i);
        scanf("%d",(*arr) + i);
    }

}

void arr_print(const int arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }
    
}

bool arr_push_back(int **arr, size_t *len, size_t len_max, int x)
{
    if (*len==len_max)
    {
        return false;
    }
    (*arr)[*len]=x;
    //printf("%d",++(*len)++);
    (*len)++;
    return true;
}

int main() {
    int *arr = NULL;     // Khởi tạo con trỏ NULL
    size_t len = 0;      // Kích thước hiện tại của mảng (ban đầu 0)
    size_t len_max = 5;  // Kích thước tối đa muốn cấp phát
    arr_initialize(&arr,len_max);
    //arr_from_input(&arr, &len, len_max);  // Cấp phát và fill giá trị 42
    //arr_fill(&arr,&len,len_max,42);
    
    if (!arr_push_back(&arr,&len,len_max,1))
    {
        printf("arr is full\n");
    }

    if (!arr_push_back(&arr,&len,len_max,5))
    {
        printf("arr is full\n");
    }

    if (!arr_push_back(&arr,&len,len_max,9))
    {
        printf("arr is full\n");
    }
    
    
    arr_print(arr,len);// In mảng ra
    

    free(arr);  // Giải phóng bộ nhớ khi không dùng nữa
    return 0;
}
