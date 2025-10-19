#include <array>
#include <iostream>


template<typename T,std::size_t N>
void printArray( const std::array<T,N>& arr)
{
    std::cout<<"The array ( ";
    
    size_t index{0};
    while (index<N) 
    {
        std::cout <<arr[index]<<" ";
        index ++;
    }
    std::cout<<") has length "<<N<<"\n";


}


int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}