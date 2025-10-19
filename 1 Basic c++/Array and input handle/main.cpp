#include <iostream>
#include <vector>
#include <limits>

template <typename T>
void printArr(const std :: vector<T>& arr){

    std :: size_t index{0};
    std :: size_t length{arr.size()};
    for (index;index < length;++index){
        std::cout<<arr.at(index)<<" ";
    }
    std::cout<<"\n";

}


void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // cin.ignore(int x, until meet \n) ignore all untill meet\n
}


bool hasUnextractedInput() // Extraction succeeds but with extraneous input
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}

bool clearFailedExtraction() // extraction fail
{
    if(!std::cin)
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        std::cin.clear();
        return true;
    }
    return false;
}
template <typename T>
T getNumber()
{
    T x{};
    do {
        
        std::cout<<"enter a number between 1 and 9: ";
        std::cin>>x;

        if (clearFailedExtraction())
        {
            std::cout<<"fail extraction input\n";
            ignoreLine();
            continue;
        }

        if(hasUnextractedInput())
        {
            std::cout<<"extraneous input\n";
            ignoreLine();
            x=0;
            continue;
        }


    }  while (x<1.1||x>9.9);
    return x;
}
template <typename T>
void checkArr(const double& x, const std :: vector<T>& arr)
{   
    std::size_t index{};
    while(index<arr.size())
    {
        if(x==arr.at(index))
        {
            std::cout<<"The number "<< x << " has index "<<index<<"\n";
            break;
        }
        index ++;
    }

    if(index==arr.size())
        std::cout<<"The number "<< x << " was not found \n";
    
}


int main(){

    double x {getNumber<double>()};
    std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
    printArr (arr);
    checkArr(x,arr);
    return 0;

}