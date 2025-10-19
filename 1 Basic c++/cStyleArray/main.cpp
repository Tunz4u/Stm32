#include <algorithm> // for std::copy
#include <iostream>


//all in main\\
// int main()
// {
//     constexpr int perfectSquare[]{0,1,4,9,16,25,36,49,64,81};
//     int uInput{},check{};
    
//     while (uInput!=-1)
//     {   
//         std::cout<<"Enter a single digit integer, or -1 to quit: ";
//         std::cin>>uInput;
//         check=0;
//         for(auto x:perfectSquare)
//         {   
            
//             if(x==uInput)
//             {
//                 std::cout<<uInput<<" is a perfect square\n";
//                 check=1;
//                 break;
//             }
//         }
//         if(check!=1)
//         {
//             std::cout<<uInput<<" is not a perfect square\n";
//         }
        
//         if(uInput==-1) 
//         {
//             std::cout<<"bye";
//         }
//     }
    
//     return 0;
// }

namespace perfSquare
{
    constexpr int squares[] {0,1,4,9};
}

bool checkSq(int& input)
{
    for(const auto& e:perfSquare::squares)
    {
        if(e==input) return true;
    }
    return false;
}

int main()
{   
    int uInput{};
    while(true)
    {
        std::cout<<"Enter a singưle digit integer, or -1 to quit: ";
        std::cin>>uInput;
        if(checkSq(uInput))
        {
            std::cout<<uInput<<" is a peeeerfect square\n";
        }
        else
        {
            std::cout<<uInput<<" is not a perfect square\n";
        }
        if(uInput==-1)
        {
            std::cout<<"bye";
            break;
        }
    }
    return 0;
}