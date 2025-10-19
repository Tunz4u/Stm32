#include <iostream>

using namespace std;

struct Fraction
{
    /* data */
    int numerator=0 ;
    int denominator=1;
};

Fraction getFrac(){
    Fraction f;
    cout<<"enter numerator: ";
    cin >>f.numerator;
    cout<<"enter denominator: ";
    cin >>f.denominator;
    return f;
}

constexpr Fraction multiplesFrac(const Fraction&  f1, const Fraction& f2){
    return {f1.numerator*f2.numerator,f1.denominator*f2.denominator};
}

void printFrac(Fraction f){
    cout <<"fraction ids "<< f.numerator<<"/"<<f.denominator;
}

int main (){
    Fraction f1 = getFrac();
    Fraction f2 = getFrac();
    Fraction resultFrac = multiplesFrac(f1,f2);
    printFrac(resultFrac);
    return 0;
}