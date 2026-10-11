#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
using namespace std;

struct PayDetails{
    double rph, otpay, totalotpay, sum, addpay;
    int days;
};

PayDetails payDetails;

void Regular()
{
    int choice;

    cout<<"\n*****REGULAR*****"
        <<"\n[1] Regular Day Overtime"
        <<"\n[2] Rest Day"
        <<"\n[3] Rest Day + Overtime"
        <<"\nChoose Factor: ";
    cin>>choice;


    switch(choice)
    {
        case 1:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.25;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Regular Day Overtime - 25% or 125%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 2:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.3;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Rest Day - 30% or 130%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 3:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.69;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Rest Day + Overtime - 169%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
    }
}

void Holiday()
{
    int choice;

    cout<<"\n*****HOLIDAY*****"
        <<"\n[1] Special Holiday"
        <<"\n[2] Special Holiday Falling on Rest Day"
        <<"\n[3] Special Holiday Falling on Rest Day + Overtime"
        <<"\n[4] Holiday"
        <<"\n[5] Holiday Falling on Rest Day"
        <<"\n[6] Holiday Falling on Rest Day + Overtime"
        <<"\n[7] Double Holiday"
        <<"\nChoose Factor: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.3;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Special Holiday - 30% or 130%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 2:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.5;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Special Holiday Falling on Rest Day - 50% or 150%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 3:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*1.95;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Special Holiday Falling on Rest Day + Overtime - 195%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 4:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*2;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Holiday - 200%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 5:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*2.6;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Holiday Falling on Rest Day - 260%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 6:
        {
            cout<<"\nRate Per Hour: ";
            cin>>payDetails.rph;
            cout<<"How many Overtime Days: ";
            cin>>payDetails.days;

            payDetails.addpay=payDetails.rph*3.38;
            payDetails.sum=payDetails.rph+payDetails.addpay;
            payDetails.otpay=payDetails.sum*payDetails.days;

            cout<<"\n*****CALCULATIONS*****"
                <<"\nNOTE: Holiday Falling on Rest Day + Overtime - 338%"
                <<"\nOvertime Pay: PHP "<<payDetails.addpay
                <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                <<"\nTotal Pay: PHP "<<payDetails.otpay;
            return;
        }
        case 7:
        {
            int factor;

            cout<<"\n*****DOUBLE HOLIDAY*****"
                <<"\n[1] Double Holiday"
                <<"\n[2] Double Holiday Falling on Rest Day"
                <<"\n[3] Double Holiday + Overtime"
                <<"\n[4] Double Holiday Falling on Rest Day + Overtime"
                <<"\nChoose Factor: ";
            cin>>factor;
            
            switch(factor)
            {
                case 1:
                {
                    cout<<"\nRate Per Hour: ";
                    cin>>payDetails.rph;
                    cout<<"How many Overtime Days: ";
                    cin>>payDetails.days;

                    payDetails.addpay=payDetails.rph*3;
                    payDetails.sum=payDetails.rph+payDetails.addpay;
                    payDetails.otpay=payDetails.sum*payDetails.days;

                    cout<<"\n*****CALCULATIONS*****"
                        <<"\nNOTE: Double Holiday - 300%"
                        <<"\nOvertime Pay: PHP "<<payDetails.addpay
                        <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                        <<"\nTotal Pay: PHP "<<payDetails.otpay;
                    return;
                }
                case 2:
                {
                    cout<<"\nRate Per Hour: ";
                    cin>>payDetails.rph;
                    cout<<"How many Overtime Days: ";
                    cin>>payDetails.days;

                    payDetails.addpay=payDetails.rph*3.9;
                    payDetails.sum=payDetails.rph+payDetails.addpay;
                    payDetails.otpay=payDetails.sum*payDetails.days;

                    cout<<"\n*****CALCULATIONS*****"
                        <<"\nNOTE: Double Holiday Falling on Rest Day - 390%"
                        <<"\nOvertime Pay: PHP "<<payDetails.addpay
                        <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                        <<"\nTotal Pay: PHP "<<payDetails.otpay;
                    return;
                }
                case 3:
                {
                    cout<<"\nRate Per Hour: ";
                    cin>>payDetails.rph;
                    cout<<"How many Overtime Days: ";
                    cin>>payDetails.days;

                    payDetails.addpay=payDetails.rph*3.9;
                    payDetails.sum=payDetails.rph+payDetails.addpay;
                    payDetails.otpay=payDetails.sum*payDetails.days;

                    cout<<"\n*****CALCULATIONS*****"
                        <<"\nNOTE: Double Holiday + Overtime - 390%"
                        <<"\nOvertime Pay: PHP "<<payDetails.addpay
                        <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                        <<"\nTotal Pay: PHP "<<payDetails.otpay;
                    return;
                }
                case 4:
                {
                    cout<<"\nRate Per Hour: ";
                    cin>>payDetails.rph;
                    cout<<"How many Overtime Days: ";
                    cin>>payDetails.days;

                    payDetails.addpay=payDetails.rph*5.07;
                    payDetails.sum=payDetails.rph+payDetails.addpay;
                    payDetails.otpay=payDetails.sum*payDetails.days;

                    cout<<"\n*****CALCULATIONS*****"
                        <<"\nNOTE: Double Holiday Falling on Rest Day + Overtime - 507%"
                        <<"\nOvertime Pay: PHP "<<payDetails.addpay
                        <<"\nSum of Additional Pay: PHP "<<payDetails.sum
                        <<"\nTotal Pay: PHP "<<payDetails.otpay;
                    return;
                }
            }
            return;
        }
    }
}

void NightDiff()
{

}

int main()
{
    int type;

    cout<<"\n ______________________"
        <<"\n|                      |"
        <<"\n|       OVERTIME       |"
        <<"\n|______________________|"
        <<"\n[1] Regular"
        <<"\n[2] Holiday"
        <<"\n[3] Night Differential"
        <<"\nYour Type of OT: ";
    cin>>type;

    switch(type)
    {
        case 1:
        {
            Regular();
            break;
        }
        case 2:
        {
            Holiday();
            break;
        }
        case 3:
        {
            NightDiff();
            break;
        }
    }
}