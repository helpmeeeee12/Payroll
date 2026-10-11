#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
using namespace std;

//VARIABLES
    struct employee{
        string name, position, status, dep;
        int id;
        double hourlyRate;
    };

    struct user{
        string username, password, role;
    };

    employee employeeDetails[100];
    user users[20]={
        {"admin", "1234", "Admin"},
        {"hr001","1234", "HR"},
        {"payroff01", "1234", "Payroll Officer"},
        {"account001", "1234", "Accountant"},
        {"employee01", "1234", "Employee"}
    };

    int empcount=0, usercount=5, action, searchid, step;
    string tempaction, tempstep, username, password, currentrole, currentuser;
    char choice;

//CALCULATION VARIABLES
    struct payroll{
        int id;
        string name, position, status, dep;
        double monthlyRate, ratePerDay, semiMonthly, totalEarning, ratePerHour;
    };
    payroll payrollRecords[100];
    int payrollcount=0;
    
    struct PayDetails{
        double rph, otpay, totalotpay, sum, addpay, rhp, ndp, rnd, nda, rndp, rpd;
        int days, hours;
        double totalOT=0;
        double totalND=0;
        double totalEarnings;
    };
    PayDetails payDetails;



//FUNCTIONS
void addEmployee()
{
    if(empcount>=100)
    {
        cout<<"Employees Storage is Full\n";
        return;
    }

    cout<<"\nPLEASE FILL UP THE FOLLOWING INFORMATIONS.";

        cout<<"\nNAME: ";
        getline(cin, employeeDetails[empcount].name);

        while(employeeDetails[empcount].name.empty())
        {
            if(employeeDetails[empcount].name.empty())
            {
                cout<<"\nType Something.";
                cout<<"\nNAME: ";
                getline(cin, employeeDetails[empcount].name);
            }
        }
                                            
        cout<<"EMPLOYEE ID: ";
        cin>>employeeDetails[empcount].id;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nInvalid.";
            cout<<"\nEMPLOYEE ID: ";
            cin>>employeeDetails[empcount].id;
        }

        cout<<"POSITION: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, employeeDetails[empcount].position);            
        while(employeeDetails[empcount].position.empty())
        {
            cout<<"\nType Something.";
            cout<<"\nPOSITION: ";
            getline(cin, employeeDetails[empcount].position);
        }
                                            
        cout<<"STATUS: ";
        getline(cin, employeeDetails[empcount].status);    
        while(employeeDetails[empcount].status.empty())
        {
            cout<<"\nType Something.";
            cout<<"\nSTATUS: ";
            getline(cin, employeeDetails[empcount].status);
        }

        cout<<"DEPARTMENT: ";
        getline(cin, employeeDetails[empcount].dep);
        while(employeeDetails[empcount].dep.empty())
        {
            cout<<"\nType Something.";
            cout<<"\nDEPARTMENT: ";
            getline(cin, employeeDetails[empcount].dep); 
        }

        cout<<"HOURLY RATE: ";
        cin>>employeeDetails[empcount].hourlyRate;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nInvalid.";
            cout<<"\nHOURLY RATE: ";
            cin>>employeeDetails[empcount].hourlyRate;
        }

        cout<<"\nSuccesfully Added Employee.";                                
        empcount++;
        return;
}

void viewEmployees()
{
    if(empcount == 0)
    {
        cout<<"\nNO EMPLOYEES HAVE BEEN ADDED.";
    }
    else
    {
        cout<<"\n _______________________"
            <<"\n|                       |"
            <<"\n|     EMPLOYEE LIST     |"
            <<"\n|_______________________|";

        for(int i = 0; i < empcount; i++)
        {
            cout<<"\nEMPLOYEE #"<<i + 1;
            cout<<"\nNAME: "<<employeeDetails[i].name
                <<"\nID: "<<employeeDetails[i].id
                <<"\nPOSITION: "<<employeeDetails[i].position
                <<"\nSTATUS: "<<employeeDetails[i].status
                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                <<"\n__________________________";
        }
    }
    return;
}

//PAYROLL CALCULATIONS
void employeeBasicPay()
{
    int days;
    string month;

    payrollRecords[payrollcount].ratePerHour = employeeDetails[empcount].hourlyRate;

    cout<<"Enter Month: ";
    cin>>month;
    cout<<"Enter Days in a month: ";
    cin>>days;

    payrollRecords[payrollcount].ratePerDay = payrollRecords[payrollcount].ratePerHour*8;
    payrollRecords[payrollcount].semiMonthly = payrollRecords[payrollcount].ratePerDay*days;
    payrollRecords[payrollcount].monthlyRate = payrollRecords[payrollcount].semiMonthly*2;

    cout<<"\n*****BASIC PAY SUMMARY*****"
        <<"\nRate Per Hour: Php "<<payrollRecords[payrollcount].ratePerHour
        <<"\nRate Per Day: Php "<<payrollRecords[payrollcount].ratePerDay
        <<"\nSemi-Monthly Rate: Php "<<payrollRecords[payrollcount].semiMonthly
        <<"\nMonthly Rate: Php "<<payrollRecords[payrollcount].monthlyRate;
}



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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
            payDetails.totalOT+=payDetails.otpay;

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
                    payDetails.totalOT+=payDetails.otpay;

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
                    payDetails.totalOT+=payDetails.otpay;

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
                    payDetails.totalOT+=payDetails.otpay;

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
                    payDetails.totalOT+=payDetails.otpay;

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
    int choice, choice2;

    cout<<"\n*****Night Differential*****"
        <<"\n[1] Regular"
        <<"\n[2] Rest Day"
        <<"\n[3] Special Holiday"
        <<"\n[4] Holiday"
        <<"\n[5] Double Holiday"
        <<"\nEnter Night Differential type: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            cout<<"\n[1] Calculate with Overtime"
                <<"\n[2] Night Differential only"
                <<"\nChoose an option to calculate: ";
            cin>>choice2;

            if(choice2==1)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.375;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;
                       

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==2)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.10;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else
            {
                cout<<"Invalid Input";
            }
        }
        case 2:
        {
            cout<<"\n[1] Calculate with Overtime"
                <<"\n[2] Rest Day only"
                <<"\nChoose an option to calculate: ";
            cin>>choice2;

            if(choice2==1)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.43;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==2)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.859;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else
            {
                cout<<"Invalid Input";
            }
        }
        case 3:
        {
            cout<<"\n[1] Special Holiday"
                <<"\n[2] Special Holiday on Rest Day"
                <<"\n[3] Special Holiday with Overtime"
                <<"\n[4] Special Holiday on Rest Day with Overtime"
                <<"\nChoose an option to calculate: ";
            cin>>choice2;

            if(choice==1)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.43;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==2)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.43;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==3)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*1.859;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;
                        
                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==4)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*2.145;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;


                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else
            {
                cout<<"Invalid Input";
            }
        }
        case 4:
        {
            cout<<"\n[1] Holiday"
                <<"\n[2] Holiday on Rest Day"
                <<"\n[3] Holiday with Overtime"
                <<"\n[4] Holiday on Rest day with Overtime"
                <<"\nChoose an option to calculate: ";
            cin>>choice2;

            if(choice2==1)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*2.2;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==2)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*2.86;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==3)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*2.86;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==4)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*3.718;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else
            {
                cout<<"Invalid Input";
            }
        }
        case 5:
        {
            cout<<"\n[1] Double Holiday"
                <<"\n[2] Double Holiday on Rest Day"
                <<"\n[3] Holiday on Rest day with Overtime"
                <<"\nChoose an option to calculate: ";
            cin>>choice2;

            if(choice2==1)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*3.3;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==2)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*4.29;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else if(choice2==3)
            {
                cout<<"\nRate Per Hour: ";
                cin>>payDetails.rph;
                cout<<"Night Hours(9 hours maximum): ";
                cin>>payDetails.hours;

                payDetails.rnd=payDetails.rph/8;
                payDetails.nda=payDetails.rnd*4.29;
                payDetails.rhp=8*payDetails.rnd;
                payDetails.ndp=8*payDetails.nda;
                payDetails.rndp=8+payDetails.ndp;

                cout<<"\n*****CALCULATIONS*****";
                cout<<"\nRegular Night Difference: "<<payDetails.rnd;
                cout<<"\nNight Differential Additional: "<<payDetails.nda;
                cout<<"\nRegular Hours Pay: "<<payDetails.rhp;
                cout<<"\nNight Differential Pay: "<<payDetails.ndp;
                cout<<"\nRegular Night Differential: "<<payDetails.rndp;
            }
            else
            {
                cout<<"Invalid Input";
            }
        }
    }
}

void overtime()
{
    int type;
    char ans;

    OVER: cout<<"\n ______________________"
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
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                return;
            }
            else
            {
                cout<<"\nInvalid.";
                goto OVER;
            }
            goto TOTALEARN;
        }
        case 2:
        {
            Holiday();
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                return;
            }
            else
            {
                cout<<"\nInvalid.";
                goto OVER;
            }
            goto TOTALEARN;
        }
        case 3:
        {
            NightDiff();
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                return;
            }
            else
            {
                cout<<"\nInvalid.";
                goto OVER;
            }
            goto TOTALEARN;
        }
    }

    TOTALEARN: 
}


//MENU FOR ROLES
void adminMenu()
{    
    do
    {
        ADMIN: cout<<"\n ____________________________________\n"
                <<"|                                    |\n"
                <<"|               ADMIN                |\n"
                <<"|____________________________________|\n";
                
        cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
            <<"\n[1] Add Employee"
            <<"\n[2] Manage Accounts"
            <<"\n[3] View Employees"
            <<"\n[4] Exit";
        cout<<"\nInput Your Action: ";
        getline(cin, tempaction);

        if(tempaction.empty())
        {
            cout<<"\nTYPE SOMETHING.";
            goto ADMIN;
        }
                    
        stringstream ss(tempaction);

        if(!(ss>>action))
        {
            cout<<"\nINVALID.";
            goto ADMIN;
        }
                    
        if(action > 4 || action < 1)
        {
            cout<<"\nINVALID.";
            goto ADMIN;
        }

        switch(action)
        {
            case 1:
            {
                addEmployee();
                goto ADMIN;
            }
            case 2: //MANAGE ACCOUNTS
            {
                ACCM: cout<<"\n ____________________________________\n"
                        <<"|                                    |\n"
                        <<"|         ACCOUNT MANAGEMENT         |\n"
                        <<"|____________________________________|\n";

                cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
                    <<"\n[1] Add Account"
                    <<"\n[2] View Accounts"
                    <<"\n[3] Delete Accounts"
                    <<"\n[4] Change Password"
                    <<"\n[5] Back";
                cout<<"\nInput Your next Step: ";
                getline(cin, tempstep);

                if(tempstep.empty())
                {
                    cout<<"\nTYPE SOMETHING.";
                    goto ACCM;
                }
                                                            
                stringstream ss(tempstep);

                if(!(ss>>step))
                {
                    cout<<"\nINVALID.";
                    goto ACCM;
                }
                                                            
                if(step > 5 || action < 1)
                {
                    cout<<"\nINVALID.";
                    goto ACCM;
                }

                switch(step)
                {
                    case 1: //ADD ACCOUNT
                    {
                        if(usercount>=20)
                        {
                            cout<<"Account Storage is Full\n";
                            goto ACCM;
                        }

                        string newusername, newpassword, newrole;
                        int rolechoice;

                        cout<<"\n*****Add Account*****\n";
                        cout<<"Enter New Username: ";
                        cin>>newusername;

                        for(int i=0; i<usercount; i++)
                        {
                            if(newusername==users[i].username)
                            {
                                cout<<"Username already exist.";
                                goto ACCM;
                            }
                        }
                                
                        cout<<"Enter New Password: ";
                        cin>>newpassword;
                        cout<<"\nSelect Role: "
                            <<"\n[1] HR"
                            <<"\n[2] Payroll Officer"
                            <<"\n[3] Accountant"
                            <<"\n[4] Employee";
                        cout<<"\nRole Choice: ";
                        cin>>rolechoice;

                        switch(rolechoice)
                        {
                            case 1:
                                newrole = "HR";
                                break;
                            case 2: 
                                newrole = "Payroll Officer";
                                break;
                            case 3: 
                                newrole = "Accountant";
                                break;
                            case 4:
                                newrole: "Employee";
                                break;
                        }

                        users[usercount].username = newusername;
                        users[usercount].password = newpassword;
                        users[usercount].role = newrole;

                        usercount++;
                        cout<<"Account successfully added.\n";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        goto ACCM;
                    }
                    case 2: //VIEW ACCOUNTS
                    {
                        cout<<"\n*****Accounts*****";
                                    
                        for(int i=0; i<usercount; i++)
                        {
                            cout<<"\nAccount # "<<i+1
                                <<"\nUsername: "<<users[i].username
                                <<"\nPassword: "<<users[i].password
                                <<"\nRole: "<<users[i].role
                                <<"\n___________________";
                        }
                            goto ACCM;
                    }
                    case 3: //DELETE ACCOUNT
                    {
                        string deleteusername;
                        bool found=false;

                        cout<<"\n*****Delete Account*****";
                        cout<<"\nEnter Username: ";
                        cin>>deleteusername;

                        for(int i=0; i<usercount; i++)
                        {
                            if(deleteusername == users[i].username)
                            {
                                if(users[i].role == "Admin")
                                {
                                    cout<<"\nYou cannot delete this account.";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        
                                    found = true;
                                    goto ACCM;
                                }

                                for(int j=1; j<usercount-1; j++)
                                {
                                    users[j] = users[j-1];
                                }

                                usercount--;
                                cout<<"\nAccount successfully deleted.";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    
                                found = true;
                                goto ACCM;
                            }
                        }
                        if(!found)
                        {
                            cout<<"\nUser Not Found.";
                            goto ACCM;
                        }
                    }
                    case 4: //CHANGE PASSWORD
                    {
                        string tarusername, newpassword, currpassword;
                        bool found = false;

                        cout<<"\n*****Change Password*****";
                    CHAPASS: cout<<"\nEnter Username: ";
                            cin>>tarusername;

                        for(int i=0; i<usercount; i++)
                        {
                            if(tarusername == users[i].username)
                            {
                                cout<<"\nEnter current password: ";
                                cin>>currpassword;

                                for(int error=1; error<=3; error++)
                                {
                                    if(currpassword == users[i].password)
                                    {
                                        cout<<"\nEnter New Password: ";
                                        cin>>newpassword;

                                        users[i].password = newpassword;

                                        cout<<"\nPassword successfully changed.";
                                        found = true;
                                        goto ACCM;
                                    }
                                    else
                                    {
                                        cout<<"\nInvalid Password.";
                                        found = true;
                                        goto CHAPASS;
                                    }
                                }
                            }
                        }
                        if(!found)
                        {
                            cout<<"\nAccount not found.";
                            goto CHAPASS;
                        }
                    }
                    case 5:
                    {
                        goto ADMIN;          
                    }
                }
            }
            case 3: //VIEW EMPLOYEES
            {
                viewEmployees();
                goto ADMIN;
            }
            case 4: //EXIT
            {
                cout<<"\nLogging out....";
                break;
            }
        }
    }while(action!=4);
}

void hrMenu()
{
    do
    {
        HR: cout<<"\n ____________________________________\n"
                <<"|                                    |\n"
                <<"|                 HR                 |\n"
                <<"|____________________________________|\n";
                
        cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
            <<"\n[1] Add Employee"
            <<"\n[2] Remove Employee"
            <<"\n[3] View Employees"
            <<"\n[4] Edit Employee Information"
            <<"\n[5] Exit";
        cout<<"\nInput Your Action: ";
        getline(cin, tempaction);

        if(tempaction.empty())
        {
            cout<<"\nTYPE SOMETHING.";
            goto HR;
        }
                    
        stringstream ss(tempaction);

        if(!(ss>>action))
        {
            cout<<"\nINVALID.";
            goto HR;
        }
                    
        if(action > 5 || action < 1)
        {
            cout<<"\nINVALID.";
            goto HR;
        }

        switch(action)
        {
            case 1: //ADDING EMPLOYEE
            {
                addEmployee();
                goto HR;
            }
            case 2: //REMOVE EMPLOYEE
            {
                int delemployee;
                char ans;
                bool found = false;

                cout<<"\n*****Remove Employee*****";
                cout<<"\nEnter Employee ID: ";
                cin>>delemployee;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for(int i=0; i<empcount; i++)
                {
                    if(delemployee == employeeDetails[i].id)
                    {
                        cout<<"\nEMPLOYEE DETAILS"
                            <<"\nNAME: "<<employeeDetails[i].name
                            <<"\nID: "<<employeeDetails[i].id
                            <<"\nPOSITION: "<<employeeDetails[i].position
                            <<"\nSTATUS: "<<employeeDetails[i].status
                            <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                            <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                            <<"\n______________________________";

                        DEL: cout<<"\nAre you sure you want to delete?[Y]Yes or [N]No: ";
                        cin>>ans;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if(ans=='Y' || ans=='y')
                        {
                            for(int j=1; j<empcount-1; j++)
                            {
                                employeeDetails[j] = employeeDetails[j-1];
                            }

                            empcount--;
                            cout<<"\nEmployee successfully deleted.";
                            found = true;
                            goto HR;
                        }
                        else if(ans=='N' || ans=='n')
                        {
                            goto HR;
                        }
                        else
                        {
                            cout<<"\nInvalid Input.";
                            goto DEL;
                        }
                    }
                }
                if(!found)
                {
                    cout<<"\nEmployee Not found.";
                    goto HR;
                }
            }
            case 3: //VIEW EMPLOYEES
            {
                viewEmployees();
                goto HR;
            }
            case 4: //EDIT EMPLOYEE INFORMATION
            {
                string newname, newdep, newpos, newstat;
                int empID, newID;
                char ans;
                bool found = false;

                cout<<"\n*****Edit Employee Information*****";
                cout<<"\nEnter Employee ID: ";
                cin>>empID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for(int i=0; i<empcount; i++)
                {
                    if(empID == employeeDetails[i].id)
                    {
                        EDITEMP: cout<<"\nWhat do you want to edit?"
                            <<"\n[A] Name"
                            <<"\n[B] ID"
                            <<"\n[C] Position"
                            <<"\n[D] Status"
                            <<"\n[E] Department"
                            <<"\n[F] Hourly Rate"
                            <<"\n[G] Back";
                        cout<<"\nYour Choice: ";
                        cin>>ans;

                        if(ans=='A' || ans=='a')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newname;

                            employeeDetails[i].name = newname;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";
                        }
                        else if(ans=='B' || ans=='b')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newID;

                            employeeDetails[i].id = newID;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";
                        }
                        else if(ans=='C' || ans=='c')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newpos;

                            employeeDetails[i].position = newpos;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";
                        }
                        else if(ans=='D' || ans=='d')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newstat;

                            employeeDetails[i].status = newstat;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";
                        }
                        else if(ans=='E' || ans=='e')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newdep;

                            employeeDetails[i].name = newdep;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";
                        }
                        else if(ans=='F' || ans=='f')
                        {
                            cout<<"\nInput Change: ";
                            cin>>newdep;

                            employeeDetails[i].name = newdep;
                            cout<<"\nChanges succesful.";

                            cout<<"\nEMPLOYEE DETAILS"
                                <<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n______________________________";
                        }
                        else if(ans=='G' || ans=='g')
                        {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto HR;
                        }
                        else
                        {
                            cout<<"\nInvalid Input.";
                            goto EDITEMP;
                        }
                    }  
                }
                if(!found)
                {
                    cout<<"\nEmployee Not Found.";
                    goto HR;
                }
            }
            case 5: //EXIT
            {
                cout<<"\nLogging out....";
                break;
            }
        }
    }while(action!=5);
}

void payoffMenu()
{
    do
    {
        PAYOFF: cout<<"\n ____________________________________\n"
                    <<"|                                    |\n"
                    <<"|          PAYROLL OFFICER           |\n"
                    <<"|____________________________________|\n";
                    
            cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
                <<"\n[1] View Employee Information"
                <<"\n[2] Process Payroll"
                <<"\n[3] View Payroll Summary"
                <<"\n[4] View Employee Payslip"
                <<"\n[5] Exit";
            cout<<"\nInput Your Action: ";
            getline(cin, tempaction);

            if(tempaction.empty())
            {
                cout<<"\nTYPE SOMETHING.";
                goto PAYOFF;
            }
                        
            stringstream ss(tempaction);

            if(!(ss>>action))
            {
                cout<<"\nINVALID.";
                goto PAYOFF;
            }
                        
            if(action > 4 || action < 1)
            {
                cout<<"\nINVALID.";
                goto PAYOFF;
            }

            switch(action)
            {
                case 1: //VIEW EMPLOYEE INFORMATION
                {
                    viewEmployees();
                    goto PAYOFF;
                }
                case 2: //PROCESS PAYROLL
                {
                    int empID;
                    bool found = false;
                    SEARCH: cout<<"\n\n*****PAYROLL PROCESS*****";
                    cout<<"\nEnter Employee ID: ";
                    cin>>empID;
                    
                    for(int i=0; i<empcount; i++)
                    {
                        if(empID == employeeDetails[i].id)
                        {
                            employeeBasicPay();
                            overtime();


                        }
                    }
                    if(!found)
                    {
                        cout<<"\nEmployee not Found";
                        goto SEARCH;
                    }
                }
                case 3: //VIEW PAYROLL SUMMARY
                {

                }
                case 4: //VIEW EMPLOYEE PAYSLIP
                {

                }
                case 5: //EXIT
                {
                    cout<<"\nLogging out....";
                    break;
                }
            }
    }while(action!=5);
}

void accountantMenu()
{
    do
    {
        ACC: cout<<"\n ____________________________________\n"
            <<"|                                    |\n"
            <<"|             ACCOUNTANT             |\n"
            <<"|____________________________________|\n";
                    
            cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
                <<"\n[1] View Payroll Records"
                <<"\n[2] View Net Pay"
                <<"\n[3] View Employee Payslip"
                <<"\n[4] Generate Payroll Report"
                <<"\n[5] Exit";
            cout<<"\nInput Your Action: ";
            getline(cin, tempaction);

            if(tempaction.empty())
            {
                cout<<"\nTYPE SOMETHING.";
                goto ACC;
            }
                        
            stringstream ss(tempaction);

            if(!(ss>>action))
            {
                cout<<"\nINVALID.";
                goto ACC;
            }
                        
            if(action > 4 || action < 1)
            {
                cout<<"\nINVALID.";
                goto ACC;
            }

            switch(action)
            {
                case 1: //VIEW PAYROLL RECORDS
                {

                }
                case 2: //VIEW NET PAY
                {

                }
                case 3: //EMPLOYEE PAYSLIP
                {

                }
                case 4: //GENERATE PAYROLL REPORT
                {

                }
                case 5: //EXIT
                {
                    cout<<"\nLogging out....";
                    break;
                }
            }
    }while (action!=5);
}
    
void employeeMenu()
{
    do
    {
        EMP: cout<<"\n ____________________________________\n"
                <<"|                                    |\n"
                <<"|              EMPLOYEE              |\n"
                <<"|____________________________________|\n";
                
        cout<<"\nPLEASE ENTER THE NUMBER WHAT YOU WANT TO DO:"
            <<"\n[1] View Information"
            <<"\n[2] View Payslip"
            <<"\n[3] Exit";
        cout<<"\nInput Your Action: ";
        getline(cin, tempaction);

        if(tempaction.empty())
        {
            cout<<"\nTYPE SOMETHING.";
            goto EMP;
        }
                    
        stringstream ss(tempaction);

        if(!(ss>>action))
        {
            cout<<"\nINVALID.";
            goto EMP;
        }
                    
        if(action > 4 || action < 1)
        {
            cout<<"\nINVALID.";
            goto EMP;
        }
    }while(action!=3);
}




int main()
{
        LOGIN: cout<<"\n ____________________________\n"
            <<"|                            |\n"
            <<"|          WELCOME           |\n"
            <<"|____________________________|\n";

        cout<<"Username: ";
        cin>>username;
        cout<<"Password: ";
        cin>>password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool found=false;
        for(int i=0; i<usercount; i++)
        {
            if(username==users[i].username && password==users[i].password)
            {
                currentuser = users[i].username;
                currentrole = users[i].role;

                cout<<"\nLogin Succesfull.";
                cout<<"\nWelcome "<<currentuser<<"!\n";
                
                found=true;
            }
        }
        if(!found)
        {
            cout<<"INVALID USERNAME AND PASSWORD.";
            goto LOGIN;
        }

        if(currentrole=="Admin")
        {
            adminMenu();
        }
        else if(currentrole=="HR")
        {
            hrMenu();
        }
        else if(currentrole=="Payroll Officer")
        {
            payoffMenu();
        }
        else if(currentrole=="Accountant")
        {
            accountantMenu();
        }
        else if(currentrole=="Employee")
        {
            employeeMenu();
        }      
}
 