#include <iostream>
#include <vector>
#include <limits>

template <typename T>
int findMax(const std::vector<T>& arr)
{
    size_t index {};
    if(index<arr.size()==0)
        return T{};
    T x{arr[0]};
    while (index<arr.size())
    {
        if(x<arr[index])
            x=arr[index];
        index++;
    } 
    return x;
}

int main()
{
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << findMax(data1) << '\n';

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << findMax(data2) << '\n';

    std::vector<int> data3 { };
    std::cout << findMax(data3) << '\n';

    return 0;
}