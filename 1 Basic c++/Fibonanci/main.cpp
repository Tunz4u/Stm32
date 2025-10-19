#include <iostream>

int factorial(int n)
{
    if(n==0)return 0;
    return factorial(n/10)+n%10;
}

int main()
{
	int input{};
    std::cin>>input;
    std::cout<<factorial(input);
    return 0;
}