#include <iostream>
using namespace std;

struct adRevenue{
    int adWatched {0};
    double percentClicked{0};
    double averageErnPerClik{0};

};

adRevenue takeInput(){
    adRevenue someDay;
    cout << "how ad watched ? "<<"\n";
    cin >> someDay.adWatched;
    cout << "how percent user click ? "<<"\n";
    cin >> someDay.percentClicked;
    cout << "how earn per click ? "<<"\n";
    cin >> someDay.averageErnPerClik;
    return someDay;
}


void MakeADay(const adRevenue& someDay){
    cout << "ad watched  "<<someDay.adWatched<<"\n";
    cout << "percent user click  "<<someDay.percentClicked<<"\n";
    cout << "earn per click "<<someDay.averageErnPerClik<<"\n";
    cout << "total a day "<<(someDay.percentClicked /100)* someDay.adWatched  *someDay.averageErnPerClik<<"\n";
}

int main(){
    adRevenue day1 {takeInput()};
    MakeADay (day1);
    return 0;
}