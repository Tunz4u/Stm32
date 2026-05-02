#include "min_heap.h"
#include <stddef.h>

/*==============================================================================
 * PRIVATE DEFINES
 *============================================================================*/
#define HEAP_MAX 128

/*==============================================================================
 * PRIVATE VARIABLES (static)
 *============================================================================*/
typedef struct
{
    int data[HEAP_MAX];
    size_t size;
} Heap_t;

static Heap_t heap;

/*==============================================================================
 * PRIVATE FUNCTION PROTOTYPES (static)
 *============================================================================*/
static void sift_up(Heap_t* heap);
static void sift_down(Heap_t* heap);
static size_t parent(size_t child);
static size_t left_child(size_t parent);
static size_t right_child(size_t parent);
static void swap(int* a, int* b);
static size_t final_child(size_t parent);
/*==============================================================================
 * PUBLIC FUNCTION IMPLEMENTATION
 *============================================================================*/
void heap_init()
{
    heap.size = 0;
}
void heap_insert(int value)
{
    heap.data[heap.size] = value;
    sift_up(&heap);
    heap.size++;
}

int heap_pop_min(void)
{
    printf("heap pop min : %d \n", heap.data[ROOT]);
    sift_down(&heap);
    heap.size--;
}

int heap_peek(void)
{
    printf("heap peek : %d \n", heap.data[ROOT]);
}
size_t heap_size(void)
{
    printf("heap size : %d \n", heap.size);
}

void print_heap()
{
    if (heap.size == 0)
    {
        printf("heap empty\n");
        return;
    }

    printf("heap: ");
    for (size_t i = 0; i < heap.size; i++)
    {
        printf("%d | ", heap.data[i]);
    }
    printf("\n");
}
/*==============================================================================
 * PRIVATE FUNCTION IMPLEMENTATION (static)
 *============================================================================*/
static void sift_up(Heap_t* heap)
{
    if (heap->size == 0)
    {
        return;
    }

    size_t p = parent(heap->size); /* parent node index*/
    size_t c = heap->size;         /* child node index*/

    while ((heap->data[p] > heap->data[c]) || (c == 0))
    {
        swap((heap->data + p), (heap->data + c));
        c = p;
        p = parent(c);
    }
}

static void sift_down(Heap_t* heap)
{
    size_t p = ROOT;
    heap->data[p] = heap->data[heap->size - 1];
    size_t c = final_child(p);

    while ((heap->data[p] > heap->data[c]))
    {
        swap((heap->data + p), (heap->data + c));
        p = c;
        c = final_child(p);
    }
}
static size_t parent(size_t child)
{
    return (child - 1) / 2;
}
static size_t left_child(size_t parent)
{
    return parent * 2 + 1;
}
static size_t right_child(size_t parent)
{
    return parent * 2 + 2;
}
static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
static size_t final_child(size_t parent) /* parent node index*/
{
    size_t left_c = left_child(parent);   /* left child node index*/
    size_t right_c = right_child(parent); /* right child node index*/
    
    size_t c = (heap.data[left_c] < heap.data[right_c]) ? left_c : right_c;
}