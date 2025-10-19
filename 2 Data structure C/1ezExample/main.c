#include<stdio.h>

int main(void)
{
    char ch = 'c';
    char c = 'a';

    char * ptr = &ch; // A constant pointer
    //ptr = &c;              // Trying to assign new address to a constant pointer. WRONG!!!!
    printf("%c",*ptr);
    return 0;
}