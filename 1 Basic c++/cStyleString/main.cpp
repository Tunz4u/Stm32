#include <cstring> // for std::strlen
#include <iostream>

void printStringForward(const char ptr[])
{
    while (*ptr!='\0')
    {
        std::cout<<*ptr;
        ptr++;
    }

    std::cout<<"\n";
}

void printStringBackward(const char ptr[])
{
    const char* str=ptr;
    while (*ptr!='\0')
    {
        ptr++;
    }

    while (ptr--!=str)
    {   
        std::cout<<*ptr;
    }
    std::cout<<"\n";
}

int main()
{
    char str[]="eeleeh";
    printStringForward(str);
    printStringBackward(str);
    return 0;
}