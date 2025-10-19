#include <iostream>
#include <vector>

// template <typename T>
// void printElement(const std::vector<T>& arr,std::size_t index)
// {
//     (0<=index&&index<arr.size())?std:: cout <<arr[index]<<"\n":std::cout<<"out of scope"<<"\n";
    
// }

template <typename T>
void printArr(const std :: vector<T>& arr){

    std :: size_t index{0};
    std :: size_t length{arr.size()};
    for (index;index < length;++index){
        std::cout<<arr.at(index)<<" ";
    }

}


int main()
{
    // std::vector v1 { 0, 1, 2, 3, 4 };
    // printElement(v1, 2);
    // printElement(v1, 4);

    // std::vector v2 { 1.1, 2.2, 3.3 };
    // printElement(v2, 0);
    // printElement(v2, -1);
    // int array[100];
    // cout<<"heki"; // allocate 1 million integers (probably 4MB of memory)

    // vector <double> temper (365);
    // cout<<"hello";
    
    // vector <int> interger (3);
    // cout<<"enter 3 integer: ";
    // cin >> interger[0]>> interger[1]>> interger[2];
    // cout <<"sum is :"<< interger[0]+interger[1]+interger[2];
    // cout <<"\n"<<"pr is :"<< interger[0]*interger[1]*interger[2];

    // std::vector arr{'h','e','l','l','o'};
    // std::cout << "size of is "<< arr.size()<<"\n";
    // std::cout << arr[1]<< arr.at(1);
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArr (arr);


    return 0;
}