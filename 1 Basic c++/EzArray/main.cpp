#include <array>
#include <iostream>

int main()
{
    constexpr std::array hello{ 'h','e','l','l','o'};

    std::cout << "length of array is "<<hello.size()<<std::size(hello)<<"\n"; 
    std::cout << std::get<1>(hello); 
    std::cout << hello[1]; 
    std::cout << hello.at(1); 
    return 0;
}