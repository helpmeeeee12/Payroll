#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
using namespace std;

//VARIABLES
double tbs, monthlysalary, total, totalpay;
int months=12;

//FUNCTIONS
void calculation(){
    cout<<"Enter Total Basic Salary: ";
    cin>>tbs;

    total = tbs*months;
    totalpay = total/months;

    cout<<"\nYour 13th Month pay is: PHP "<<totalpay;
}

int main()
{
    calculation();

    return 0;
}