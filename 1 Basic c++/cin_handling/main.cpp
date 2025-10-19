#include <iostream>
#include <vector>
#include <limits> // for std::numeric_limits

//handle extraction fail and extraneous input

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // cin.ignore(int x, until meet \n) ignore all untill meet\n
}

bool hasUnextractedInput() // Extraction succeeds but with extraneous input
{
    std::cout <<"1";
    return !std::cin.eof() && std::cin.peek() != '\n';
}

// returns true if std::cin has unextracted input on the current line, false otherwise

bool clearFailedExtraction() // Extraction fails
{
    std::cout <<"2";
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout<<"invalid double try again.\n"; 
            continue;
        }

        if (hasUnextractedInput())
        {
            std::cout<<"extraneous input\n"; 
            ignoreLine(); // remove extraneous input
            continue;
        }
        

        ignoreLine();     // And remove the bad input
        return x;              // Return it (otherwise, we go back to top of loop)
    }
}


char getOperator(){
    while (true){
        std::cout<<"enter operator :";
        char op{};
        std::cin>>op;

        if (clearFailedExtraction())
        {
            std::cout<<"invalid operator try again.\n"; 
            continue;
        }

        if (hasUnextractedInput())
        {
            std::cout<<"extraneous input\n"; 
            ignoreLine(); // remove extraneous input
            continue;
        }
        
        ignoreLine();     // And remove the bad input
        switch (op)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return op; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }

}

void printResult(double x, char operation, double y){

    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        std::cout << x / y << '\n';
        return;
    }
}


int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    while(operation =='/'&& y==0 ){
        std::cout <<"no divided by 0\n";
        y=getDouble();
    }
    printResult(x, operation, y);
    return 0;
}