#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

//VARIABLES
    struct user{ //VARIABLES NEEDED FOR THE USERS ACCOUNT
        string username, password, role;
    };

    user users[100]={ //ARRAY FOR THE USERS ACCOUNT
        {"admin", "1234", "Admin"},
        {"hr001","1234", "HR"},
        {"payroff01", "1234", "Payroll Officer"},
        {"account001", "1234", "Accountant"},
        {"employee01", "1234", "Employee"}
    };
    int usercount=5;
    string username, password, currentrole, currentuser, empID;

//VARIABLES FOR EMPLOYEE DETAILS
    struct employee{
        string name, position, status, dep;
        string id;
        double hourlyRate, leavebalance;
    };

    employee employeeDetails[100];

    int empcount=0, action, searchid, step;
    string tempaction, tempstep;
    char choice;

//CALCULATION VARIABLES
    struct payroll{
        string payPeriod;
        string id;
        string name, position, status, dep;
        double monthlyRate, ratePerDay, semiMonthly, ratePerHour, basicPay, hourlyRate; //BASIC PAY
        double otpay, totalotpay; //OVERTIME
        double totalOT=0, totalND=0, totalEarnings=0; //TOTAL EARNINGS
        
        double sssDeduction=0; //SSS DEDUCTION

        double LateDeduction; //TARDINESS

        double PHTotalContribution; //PHILHEALTH
        
        double PBTotalContribution; //PAGIBIG

        double WHT, totalWHT, SWHT, MWHT; //WHITHHOLDING TAX

        double TotalDeMinimisExcess; //DEMINIMIS

        double ThirteenMonthExcess, totalThirteenMonth; //13 MONTH PAY

        double totalDeductions;

        double netPay; //FINAL PAY

        double leavepay=0, leaveconversion=0;

        int leavebalance=0, leavedays=0, converteddays=0; //LEAVE
    };
    payroll payrollRecords[100];
    int payrollcount=0;

    //PROTOTYPES
    void NetPay(int i);
    void ThirteenthMonth(int i);
    void SemiMonthlyWithHoldingTax(int i);

    //INPUT VALIDATION FUNCTIONS
    int readInt(int low, int high)
    {
        int value;

        cin >> value;
        while (cin.fail() || value < low || value > high)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from " << low << " to " << high;
            cin >> value;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
    double readDouble(double low, double high)
    {
        double value;

        cin >> value;
        while (cin.fail() || value < low || value > high)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from " << low << " to " << high;
            cin >> value;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
    
//ACCOUNTS FUNCTIONS
void loadAccounts()//LOADING ACCOUNTS FROM THE FILE
{
    ifstream file("accounts.txt");

    if(!file)
    {
        cout<<"\nError opening file.";
        return;
    }

    //LOAD THE ACCOUNTS FROM THE FILE
    usercount=0;
    while(usercount < 100 &&
        getline(file, users[usercount].username, '|') && 
        getline(file, users[usercount].password, '|') && 
        getline(file, users[usercount].role))
    {
        usercount++;

        if(usercount >=100)
        {
            break;
        }
    }
    file.close();
}

void saveAccounts()//ADDING ACCOUNTS TO THE FILE
{
    ofstream file("accounts.txt");

    if(!file)
    {
        cout<<"Error opening File.";
        return;
    }
    
    for(int i=0; i<usercount; i++)
    {
        file<<users[i].username<<"|"
            <<users[i].password<<"|"
            <<users[i].role<<endl;
    }
    file.close();
}

//SAVING AND LOADING EMPLOYEES
void saveEmployees()
{
    ofstream file("employees.txt");

    if(file.is_open())
    {
        for(int i=0; i<empcount; i++)
        {
        file<<fixed<<setprecision(2)
            << employeeDetails[i].name << "|"
            << employeeDetails[i].id << "|"
            << employeeDetails[i].position << "|"
            << employeeDetails[i].status << "|"
            << employeeDetails[i].dep << "|"
            << employeeDetails[i].hourlyRate << "|"
            << employeeDetails[i].leavebalance << endl;
        }
    }
    else if(!file)
    {
        cout << "\nFile opened, but writing failed.";
        return;
    }
    
    file.close();
    cout << "\nEmployee saved successfully.";
    return;
}

//LOADING EMPLOYEES
void loadEmployees()
{
    ifstream file("employees.txt");

    if(!file)
    {
        cout<<"\nError opening employee file";
        return;
    }

    string rate, lb;
    empcount=0;
    
    while(getline(file, employeeDetails[empcount].name, '|') &&
        getline(file, employeeDetails[empcount].id, '|') &&
        getline(file, employeeDetails[empcount].position, '|') &&
        getline(file, employeeDetails[empcount].status, '|') &&
        getline(file, employeeDetails[empcount].dep, '|') &&
        getline(file, rate, '|') &&
        getline(file, lb))
    {
        employeeDetails[empcount].hourlyRate = stod(rate);
        employeeDetails[empcount].leavebalance = stod(lb);
        empcount++;

        if(empcount >= 100)
        {
            break;
        }
    }
    file.close();
}

//SAVING PAYROLL CALCULATION
void savePayroll()
{
    ofstream file("payroll.txt");

    if(!file)
    {
        cout<<"\nError opening file.";
        return;
    }
    
    for(int i=0; i<payrollcount; i++)
    {
        file<<fixed<<setprecision(2)
            <<payrollRecords[i].payPeriod<<"\n"
            <<payrollRecords[i].id<<"\n"
            <<payrollRecords[i].name<<"\n"
            <<payrollRecords[i].position<<"\n"
            <<payrollRecords[i].status<<"\n"
            <<payrollRecords[i].dep<<"\n"
            <<payrollRecords[i].monthlyRate<<" "
            <<payrollRecords[i].ratePerDay<<" "
            <<payrollRecords[i].semiMonthly<<" "
            <<payrollRecords[i].totalOT<<" "
            <<payrollRecords[i].totalND<<" "
            <<payrollRecords[i].totalEarnings<<" "
            <<payrollRecords[i].LateDeduction<<" "
            <<payrollRecords[i].sssDeduction<<" "
            <<payrollRecords[i].PHTotalContribution<<" "
            <<payrollRecords[i].PBTotalContribution<<" "
            <<payrollRecords[i].totalThirteenMonth<<" "
            <<payrollRecords[i].totalWHT<<" "
            <<payrollRecords[i].totalDeductions<<" "
            <<payrollRecords[i].netPay<<" "
            <<payrollRecords[i].leavedays<<" "
            <<payrollRecords[i].leavepay<<" "
            <<payrollRecords[i].leaveconversion<<"\n";
    }

    file.close();
    return;
}

//FUNCTION FOR ADDING EMPLOYEE
void addEmployee()
{
    if(empcount>=100)
    {
        cout<<"\nEmployees Storage is Full\n";
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
        
        bool exists;
        do
        {
            exists = false;
            cout<<"EMPLOYEE ID: ";
            cin>>employeeDetails[empcount].id;

            for(int i=0; i<empcount; i++)
            {
                if(employeeDetails[empcount].id == employeeDetails[i].id)
                {
                    exists = true;
                }
            }
            
            if(exists)
            {
                cout<<"\nEmployee ID already exists.";
            }
        } while (exists);

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
       
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout<<"\nInvalid.";
            cout<<"\nHOURLY RATE: ";
            cin>>employeeDetails[empcount].hourlyRate;
        }
                              
        employeeDetails[empcount].leavebalance = 5;
        empcount++;
        saveEmployees(); 
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return;
}

//FUNCTION FOR VIEWING EMPLOYEE
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
            cout<<"\n\nEMPLOYEE #"<<i + 1;
            cout<<"\nNAME: "<<employeeDetails[i].name
                <<"\nID: "<<employeeDetails[i].id
                <<"\nPOSITION: "<<employeeDetails[i].position
                <<"\nSTATUS: "<<employeeDetails[i].status
                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                <<"\nLEAVE BALANCE: "<<employeeDetails[i].leavebalance
                <<"\n__________________________";
        }
    }
    return;
}

//FUNCTION FOR SAVING PAYROLL RECORDS
void loadPayrollRecords()
{
    ifstream file("payroll.txt");

    if(!file)
    {
        payrollcount=0;
        return;
    }

    payrollcount = 0;

    while(payrollcount < 100 && getline(file, payrollRecords[payrollcount].payPeriod))
    {
        getline(file, payrollRecords[payrollcount].id);
        getline(file, payrollRecords[payrollcount].name);
        getline(file, payrollRecords[payrollcount].position);
        getline(file, payrollRecords[payrollcount].status);
        getline(file, payrollRecords[payrollcount].dep);

        file>>payrollRecords[payrollcount].monthlyRate
            >>payrollRecords[payrollcount].ratePerDay
            >>payrollRecords[payrollcount].semiMonthly
            >>payrollRecords[payrollcount].totalOT
            >>payrollRecords[payrollcount].totalND
            >>payrollRecords[payrollcount].totalEarnings
            >>payrollRecords[payrollcount].LateDeduction
            >>payrollRecords[payrollcount].sssDeduction
            >>payrollRecords[payrollcount].PHTotalContribution
            >>payrollRecords[payrollcount].PBTotalContribution
            >>payrollRecords[payrollcount].totalThirteenMonth
            >>payrollRecords[payrollcount].totalWHT
            >>payrollRecords[payrollcount].totalDeductions
            >>payrollRecords[payrollcount].netPay
            >>payrollRecords[payrollcount].leavedays
            >>payrollRecords[payrollcount].leavepay
            >>payrollRecords[payrollcount].leaveconversion;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        payrollcount++;
    }
    file.close();
}

//DISPLAYS
void payrollSummary(int i)
{
    int choice;

    cout<<"\n ____________________________________\n"
        <<"|                                    |\n"
        <<"|          PAYROLL SUMMARY           |\n"
        <<"|____________________________________|\n";

    cout<<"\nEmployee ID: "<<payrollRecords[i].id
        <<"\nEmployee Name: "<<payrollRecords[i].name
        <<"\nPosition: "<<payrollRecords[i].position
        <<"\nDepartment: "<<payrollRecords[i].dep
        <<"\nStatus: "<<payrollRecords[i].status
        <<"\nPay Period: "<<payrollRecords[i].payPeriod
        <<"\n\n****** EARNINGS ***** "
        <<"\nBasic Salary: Php "<<payrollRecords[i].semiMonthly - payrollRecords[i].leavepay
        <<"\nLeave Pay: Php "<<payrollRecords[i].leavepay
        <<"\nLeave Cash-out: Php "<<payrollRecords[i].leaveconversion
        <<"\n13th Month Pay: Php "<<payrollRecords[i].totalThirteenMonth
        <<"\nMonthly Rate: Php "<<payrollRecords[i].monthlyRate
        <<"\nOvertime/Holiday Pay: Php "<<payrollRecords[i].totalOT
        <<"\nNight Differential: Php "<<payrollRecords[i].totalND
        <<"\n____________________________________"
        <<"\nTOTAL EARNINGS: "<<payrollRecords[i].totalEarnings
        <<"\n\n***** DEDUCTIONS *****"
        <<"\nSSS: Php "<<payrollRecords[i].sssDeduction
        <<"\nPhilHealth: Php "<<payrollRecords[i].PHTotalContribution
        <<"\nPag-IBIG: Php "<<payrollRecords[i].PBTotalContribution
        <<"\nSemi-Monthly Withholding Tax: Php "<<payrollRecords[i].totalWHT
        <<"\nTardiness: Php "<<payrollRecords[i].LateDeduction
        <<"\n____________________________________"
        <<"\nTOTAL DEDUCTIONS: Php "<<payrollRecords[i].totalDeductions
        <<"\n____________________________________"
        <<"\nNET PAY: Php "<<payrollRecords[i].netPay;
    
    PICK: cout<<"\n\n[1] Save Payroll"
        <<"\n[2] Return"
        <<"\nEnter Choice: ";
    cin>>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch(choice)
    {
        case 1:
        {
            savePayroll();
            return;
        }
        case 2:
        {
            return;
        }
        default:
            cout<<"\nInvalid input.";
            goto PICK;
    }
}

void viewPayrollRecords()
{
    loadPayrollRecords();

    for(int i=0; i<payrollcount; i++)
    {
        cout<<"\n ____________________________________\n"
            <<"|                                    |\n"
            <<"|          PAYROLL RECORDS           |\n"
            <<"|____________________________________|\n";

        cout<<"\nEmployee ID: "<<payrollRecords[i].id
            <<"\nEmployee Name: "<<payrollRecords[i].name
            <<"\nPay Period: "<<payrollRecords[i].payPeriod
            <<"\n____________________________________"
            <<"\nTotal Earnings: Php "<<payrollRecords[i].totalEarnings
            <<"\nTotal Deductions: Php "<<payrollRecords[i].totalDeductions
            <<"\nNet Pay: Php "<<payrollRecords[i].netPay
            <<"\n____________________________________"
            <<"\n\n";
    }
    return;
}

void finalizePayroll(int i)
{
    //CONTRIBUTIONS ARE MONTHLY AMOUNTS; DEDUCT HALF PER CUTOOF
    payrollRecords[i].sssDeduction /= 2;
    payrollRecords[i].PHTotalContribution /=2;
    payrollRecords[i].PBTotalContribution /=2; 
    ThirteenthMonth(i);

    SemiMonthlyWithHoldingTax(i);
    payrollRecords[i].totalWHT += payrollRecords[i].WHT;
    payrollRecords[i].totalEarnings = payrollRecords[i].semiMonthly+payrollRecords[i].totalOT+payrollRecords[i].totalND;

    NetPay(i);
}


//FUNCTIONS FOR CALCULATIONS
void NetPay(int i)
{
    double totaldeductions;

    totaldeductions = payrollRecords[i].LateDeduction + payrollRecords[i].sssDeduction 
                    + payrollRecords[i].PHTotalContribution + payrollRecords[i].PBTotalContribution
                    + payrollRecords[i].totalWHT;
    
    payrollRecords[i].totalDeductions = totaldeductions;
    payrollRecords[i].netPay = payrollRecords[i].totalEarnings - totaldeductions;

}   

//(13TH MONTHPAY(Excess)  Withholding tax name = TMPEWithHoldingTax();
void TMPEWithHoldingTax(int i) 
{
    double TaxableIncome, excess; //ANNUAL BASED WITHHOLDINGTAX

    TaxableIncome=payrollRecords[i].ThirteenMonthExcess;

    if(TaxableIncome <= 250000) 
    { 
        //250,000 pesos and below 
        //no tax
        payrollRecords[i].WHT = 0.0; 
        
        
    }
    else if (TaxableIncome <= 400000) 
    { 
        // over 250,000 - 400,000 pesos
        //  15% of the excess over PHP250,000
        const double excessTH = 250000.00;
        const double baserate = 0.15;
        const double basetax = 0.00;
        
        payrollRecords[i].WHT = basetax + (baserate * (TaxableIncome - excessTH));
        
       
    }
    else if (TaxableIncome <= 800000) 
    { 
        //over 400,000 - 800,000
        // PHP22,500 + 20% of the excess over PHP400,000
        const double excessTH = 400000.00;
        const double baserate = 0.20;
        const double basetax = 22500.00;
        
        payrollRecords[i].WHT = basetax + (baserate * (TaxableIncome - excessTH));

        
    } 
    else if (TaxableIncome <= 2000000) 
    { 
        //over 800,000  - 2,000,000
        // PHP 102,500 + 25% of the excess over PHP800,000
        const double excessTH = 800000.00;
        const double baserate = 0.25;
        const double basetax = 102500.00;
        
        payrollRecords[i].WHT = basetax + (baserate * (TaxableIncome - excessTH));

       
    }
    else if (TaxableIncome <= 8000000 ) 
    { 
        //over 2,000,000  - 8,000,000
        // PHP 402,500 + 30% of the excess over PHP2,000,000
        const double excessTH = 2000000.00;
        const double baserate = 0.30;
        const double basetax = 402500.00;
        
        payrollRecords[i].WHT = basetax + (baserate * (TaxableIncome - excessTH));

        
    }
    else 
    { 
        // TaxableIncome > 8,000,000
        // PHP 2,202,500 + 35% of the excess over PHP 8,000,000
        const double excessTH = 8000000.00;
        const double baserate = 0.35;
        const double basetax = 2202500.00;
        
        payrollRecords[i].WHT = basetax + (baserate * (TaxableIncome - excessTH));

        
    }

}

//WITHHOLDINGTAX CALCULATIONS
void SemiMonthlyWithHoldingTax(int i) 
{
    double TaxableIncome;

    TaxableIncome = payrollRecords[i].semiMonthly
              + payrollRecords[i].totalOT
              + payrollRecords[i].totalND
              - payrollRecords[i].LateDeduction
              - payrollRecords[i].sssDeduction
              - payrollRecords[i].PHTotalContribution
              - payrollRecords[i].PBTotalContribution;
if(TaxableIncome < 0) TaxableIncome = 0;

    if(TaxableIncome <= 10417) 
    {          
        //10,417  pesos and below 
        //no tax
        payrollRecords[i].SWHT = 0.0; 

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        savePayroll();
    }
    else if (TaxableIncome < 16667) 
    { 
        // over 10,417  - 16,666 pesos
        //  15% of the excess over PHP10,417
        const double excessTH = 10417.00;
        const double baserate = 0.15;
        const double basetax = 0.00;

        payrollRecords[i].SWHT = basetax + (baserate * (TaxableIncome - excessTH));

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        
        savePayroll();
    }
    else if (TaxableIncome < 33333) 
    { 
        //over 16,667  - 33,332 pesos
        // PHP 937.50 + 20% of the excess over PHP16,667
        const double excessTH = 16667.00;
        const double baserate = 0.20;
        const double basetax = 937.50;
        
        payrollRecords[i].SWHT = basetax + (baserate * (TaxableIncome - excessTH));

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        savePayroll();
    } 
    else if (TaxableIncome < 83333) 
    { 
        //over 33,333   - 83,332 pesos
        // PHP 4,270.70 + 25% of the excess over PHP 33,333
        const double excessTH = 33333.00;
        const double baserate = 0.25;
        const double basetax = 4270.70;

        payrollRecords[i].SWHT = basetax + (baserate * (TaxableIncome - excessTH));

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        savePayroll();
    }
    else if (TaxableIncome < 333333 ) 
    { 
        //over 83,333   - 333,332
        // PHP 16,770.70 + 30% of the excess over PHP 83,333
        const double excessTH = 83333.00;
        const double baserate = 0.30;
        const double basetax = 16770.70;

        payrollRecords[i].SWHT = basetax + (baserate * (TaxableIncome - excessTH));

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        savePayroll();
    }
    else 
    { 
        // TaxableIncome >= 333,333 
        // PHP 91,770.70 + 35% of the excess over PHP 333,333
        const double excessTH = 333333.00;
        const double baserate = 0.35;
        const double basetax = 91770.70;

        payrollRecords[i].SWHT = basetax + (baserate * (TaxableIncome - excessTH));

        payrollRecords[i].totalWHT+=payrollRecords[i].SWHT; 
        savePayroll();
    }
}

void MonthWithHoldingTax(int i) 
{
// Monthly Tax = Base Tax + (Tax Rate × (Taxable Income − Lower Bracket Limit))

    double TaxableIncome, excess;

    TaxableIncome=payrollRecords[i].semiMonthly; //since the input is semi-monthly, it should be multiplied by 2 for the monthly tax table

    if(TaxableIncome <= 20833) 
    { 
        // 20,833 Pesos and below   
        //no tax
        payrollRecords[i].MWHT = 0.0; 
    }
    else if (TaxableIncome < 33333) 
    { 
        // Ranged 20,833 - 33,332 pesos
        // 15% of the excess over PHP20,833
        const double excessTH = 20833.00;
        const double baserate = 0.15;
        const double basetax = 0.00;
        
        payrollRecords[i].MWHT = basetax + (baserate * (TaxableIncome - excessTH));
    }
    else if (TaxableIncome < 66667) 
    { 
        //33,333 - 66,666
        // PHP1,875 + 20% of the excess over PHP33,333
        const double excessTH = 33333.00;
        const double baserate = 0.20;
        const double basetax = 1875.00;
        
        payrollRecords[i].MWHT = basetax + (baserate * (TaxableIncome - excessTH));

    } 
    else if (TaxableIncome < 166667) 
    { 
        //66,667 - 166,666
        // PHP 8541.80 + 25% of the excess over PHP66,667
        const double excessTH = 66667.00;
        const double baserate = 0.25;
        const double basetax = 8541.80;
        
        payrollRecords[i].MWHT = basetax + (baserate * (TaxableIncome - excessTH));
    }
    else if (TaxableIncome < 666667 ) 
    { 
        // 166,667 - 666,666
        // PHP 33541.80+ 30% of the excess over PHP166,667
        const double excessTH = 166667.00;
        const double baserate = 0.30;
        const double basetax = 33541.80;
        
        payrollRecords[i].MWHT = basetax + (baserate * (TaxableIncome - excessTH));
    }
    else 
    { 
        // TaxableIncome >= 666,667
        // PHP 183541.80 + 35% of the excess over PHP 666,667
        const double excessTH = 666667.00;
        const double baserate = 0.35;
        const double basetax = 183541.80;
        
        payrollRecords[i].MWHT = basetax + (baserate * (TaxableIncome - excessTH));
    }
}

//13TH MONTH
void ThirteenthMonth(int i)
{
    int months=12;
    double TotalBasicSalary;

    TotalBasicSalary=payrollRecords[i].monthlyRate*months;
    payrollRecords[i].totalThirteenMonth= TotalBasicSalary/months;

    if(payrollRecords[i].totalThirteenMonth >=90000.01)
    {
        payrollRecords[i].ThirteenMonthExcess=payrollRecords[i].totalThirteenMonth-90000;
        TMPEWithHoldingTax(i);
    }
    else
    {
        savePayroll();
    }
}  

//DEMINIMIS CALCULATIONS
void CalculationDeminimisExcess(int i)
{
    double RiceSubsidy = 0, RiceSubsidyExcess = 0, UniformClothing = 0, UniformClothingExcess = 0, Laundry = 0, LaundryExcess = 0, ActualMedicalAssistance = 0, ActualMedicalAssistanceExcess = 0, TotalDeMinimisExcess = 0;
   
    const double RiceSubsidyLIMIT = 2500 * 12; // 2500pesos per month (2.5k * 12 = 30,000 Pesos)
    const double UniformAndClothingLIMIT = 8000.00; //8k per year
    const double LaundryLIMIT = 400 * 12; // 400 per month (400 * 12 = 4,800 Pesos)
    const double ActualMedicalAssistanceLIMIT = 12000.00; // 12k annually
   
   /* cout << "Enter ANNUAL amounts given:\n";
    cout << "Rice Subsidy: ";               cin >> RiceSubsidy;
    cout << "Uniform and Clothing: ";       cin >> UniformClothing;
    cout << "Laundry: ";                    cin >> Laundry;
    cout << "Actual Medical Assistance: ";  cin >> ActualMedicalAssistance; */ //Just remove this if not needed


    if(RiceSubsidy <= RiceSubsidyLIMIT){
        RiceSubsidyExcess = 0;
    }
    else {
       RiceSubsidyExcess = RiceSubsidy - RiceSubsidyLIMIT;
    }
    if(UniformClothing <= UniformAndClothingLIMIT){
        UniformClothingExcess = 0;
    }
    else{
        UniformClothingExcess = UniformClothing - UniformAndClothingLIMIT;
    }
    if(Laundry <= LaundryLIMIT){
        LaundryExcess = 0;
    }
    else{
        LaundryExcess = Laundry - LaundryLIMIT;
    }
    if(ActualMedicalAssistance <= ActualMedicalAssistanceLIMIT){
        ActualMedicalAssistanceExcess = 0;
    }
    else {
        ActualMedicalAssistanceExcess = ActualMedicalAssistance - ActualMedicalAssistanceLIMIT;
    }

    payrollRecords[i].TotalDeMinimisExcess = RiceSubsidyExcess + UniformClothingExcess + LaundryExcess + ActualMedicalAssistanceExcess;

   /* cout << "\nRice excess:     " << RiceSubsidyExcess;
    cout << "\nUniform excess:  " << UniformClothingExcess;
    cout << "\nLaundry excess:  " << LaundryExcess;
    cout << "\nMedical excess:  " << ActualMedicalAssistanceExcess;
    cout << "\nTOTAL DE MINIMIS EXCESS: " << TotalDeMinimisExcess << "\n"; */ //Remove if not needed
}
// The excess of the De minimis benefit will be added to the 13th month pay and the excess of the 13th month pay (with deminis) is added to the taxable income
// example the Excess of De minimis is 5k and the total of 13th month pay is = 95k so 5k + 95k = 100k since the tax exempt is only 90k it will be 100k - 90k = 10k
// this 10k value will be added to the taxable income. 


//PAGIBIG CALCULATIONS
void PagIbig(int i)
{
    char PBchoice;
    double PBEmployeeShare, PBEmployerShare, TotalContribution;

    PAGIBIG: cout<<" ______________________________________"<<endl;
    cout<<"|                                      |"<<endl;
    cout<<"|         PAG-IBIG CONTRIBUTION        |"<<endl;
    cout<<"|______________________________________|"<<endl;
   
    cout<<"\nDo you have Pag-IBIG?"<<endl;
    cout<<"[Y] Yes | [N] No"<<endl;
    cout<<"Enter: ";
    cin>>PBchoice;

        if (PBchoice == 'Y' || PBchoice == 'y')
        {
            if (payrollRecords[i].monthlyRate <= 1500)
            {
                PBEmployeeShare = payrollRecords[i].monthlyRate * 0.01;
                PBEmployerShare = payrollRecords[i].monthlyRate * 0.02;
                TotalContribution = PBEmployeeShare + PBEmployerShare;

                cout<<"\nCalculation for Pag-Ibig Contribution"<<endl;
                cout<<"Employee Share: "<<PBEmployeeShare<<endl;
                cout<<"Employer Share: "<<PBEmployerShare<<endl;
                cout<<"Total Contribution: "<<TotalContribution<<endl;

                payrollRecords[i].PBTotalContribution=PBEmployeeShare;

                savePayroll();
            }
            else if (payrollRecords[i].monthlyRate > 1500 && payrollRecords[i].monthlyRate <= 10000)
            {
                PBEmployeeShare = payrollRecords[i].monthlyRate * 0.02;
                PBEmployerShare = payrollRecords[i].monthlyRate * 0.02;
                TotalContribution = PBEmployeeShare + PBEmployerShare;

                cout<<"\nCalculation for Pag-Ibig Contribution"<<endl;
                cout<<"Employee Share: "<<PBEmployeeShare<<endl;
                cout<<"Employer Share: "<<PBEmployerShare<<endl;
                cout<<"Total Contribution: "<<TotalContribution<<endl;

                payrollRecords[i].PBTotalContribution=PBEmployeeShare;

                savePayroll();
            }
            else if (payrollRecords[i].monthlyRate > 10000)
            {
                //200 Capped
                PBEmployeeShare = 200;
                PBEmployerShare = 200;
                TotalContribution = PBEmployeeShare + PBEmployerShare;

                cout<<"\nCalculation for Pag-Ibig Contribution"<<endl;
                cout<<"Employee Share: "<<PBEmployeeShare<<endl;
                cout<<"Employer Share: "<<PBEmployerShare<<endl;
                cout<<"Total Contribution: "<<TotalContribution<<endl;

                payrollRecords[i].PBTotalContribution=PBEmployeeShare;

                savePayroll();
            }
        }
        else if (PBchoice == 'N' || PBchoice == 'n')
        {
            CalculationDeminimisExcess(i);
        }
        else
        {
            cout<<"INVALID INPUT"<<endl;
            goto PAGIBIG;
        }
}

//PHILHEALTH CALCULATION
void Philhealth(int i)
{
    char PHchoice;
    double TotalPremium, PHEmployeeShare, PHEmployerShare;

    PHIL: cout<<" ______________________________________"<<endl;
    cout<<"|                                      |"<<endl;
    cout<<"|         PHILHEALTH CONTRIBUTION      |"<<endl;
    cout<<"|______________________________________|"<<endl;
   
    cout<<"\nDo you have PhilHealth?"<<endl;
    cout<<"[Y] Yes | [N] No"<<endl;
    cout<<"Enter: ";
    cin>>PHchoice;

    if (PHchoice == 'Y' || PHchoice == 'y')
    {

        if (payrollRecords[i].monthlyRate <=10000)
        {
            TotalPremium = 10000 * 0.05;
            PHEmployeeShare = TotalPremium / 2;

            cout<<"\nCalculation for PhilHealth Contribution"<<endl;
            cout<<"Salary Base: 10000"<<endl;
            cout<<"Total Premium: "<<TotalPremium<<endl;
            cout<<"Employee Share: "<<PHEmployeeShare<<endl;

            payrollRecords[i].PHTotalContribution=PHEmployeeShare;

            savePayroll();
            PagIbig(i);
        }
        else if (payrollRecords[i].monthlyRate >= 10000.01 && payrollRecords[i].monthlyRate <= 99999.99)
        {
            TotalPremium = payrollRecords[i].monthlyRate * 0.05;
            PHEmployeeShare = TotalPremium / 2;

            cout<<"\nCalculation for PhilHealth Contribution"<<endl;
            cout<<"Salary Base: "<<payrollRecords[i].monthlyRate<<endl;
            cout<<"Total Premium: "<<TotalPremium<<endl;
            cout<<"Employee Share: "<<PHEmployeeShare<<endl;

            payrollRecords[i].PHTotalContribution=PHEmployeeShare;

            savePayroll();
            PagIbig(i);          
        }
        else if (payrollRecords[i].monthlyRate >= 100000)
        {
            TotalPremium = 100000 * 0.05;
            PHEmployeeShare = TotalPremium / 2;

            cout<<"\nCalculation for PhilHealth Contribution"<<endl;
            cout<<"Salary Base: 100000"<<endl;
            cout<<"Total Premium: "<<TotalPremium<<endl;
            cout<<"Employee Share: "<<PHEmployeeShare<<endl;

            payrollRecords[i].PHTotalContribution=PHEmployeeShare;

            savePayroll();
            PagIbig(i);
        }
        else
        {
            cout<<"INVALID INPUT"<<endl;
            goto PHIL;
        }
    }
    else if (PHchoice == 'N' || PHchoice == 'n')
    {
        PagIbig(i);
    }
    else
    {
        cout<<"\nINVALID INPUT"<<endl;
        goto PHIL;
    }
}


//CALCULATIONS FOR SSS
void calculateSSS(int i) 
{
    char choice;

    cout<<"\n ______________________________________"<<endl;
    cout<<"|                                      |"<<endl;
    cout<<"|           SSS DEDUCTION              |"<<endl;
    cout<<"|______________________________________|"<<endl;
    cout<<"\nDo You Have SSS?"<<endl;
    cout<<"[Y] Yes | [N] No"<<endl;
    cout<<"Enter: ";
    cin>>choice;
    
    if(choice=='Y' || choice=='y')
    {
       double msc;
       double compensation = payrollRecords[i].semiMonthly
                           + payrollRecords[i].totalOT
                           + payrollRecords[i].totalND 
                           + payrollRecords[i].LateDeduction;
        double pay = compensation*2;
        
        if(pay < 5250)
            msc = 5000;
        else if(pay >= 34750)
            msc = 35000;
        else 
            msc = 5000 + ((int)((pay - 5250)/500) + 1) * 500;
        payrollRecords[i].sssDeduction = msc * 0.05;
    }

    savePayroll();
    Philhealth(i);
}


//TARDINESS CALCULATIONS
void tardiness(int i)
{
    //Variable Declaration
    char choice;
    int LateMinutes;
    double MinuteRate;

    //Asking if there's any tardiness
        TARD: cout<<"\n ______________________________________"<<endl;
        cout<<"|                                      |"<<endl;
        cout<<"|             TARDINESS                |"<<endl;
        cout<<"|______________________________________|"<<endl;
        cout<<"\nIs there any tardiness during working hours?"<<endl;
        cout<<"[Y] Yes | [N] No"<<endl;
        cout<<"Enter: ";
        cin>>choice;

        if (choice == 'Y' || choice == 'y')
        {
            cout<<"Enter Tardiness in Minutes: ";
            cin>>LateMinutes;


            //Computation
            MinuteRate = payrollRecords[i].hourlyRate / 60;

            payrollRecords[i].LateDeduction = MinuteRate * LateMinutes;

            savePayroll();
            calculateSSS(i);
        
        }
        else if (choice == 'N' || choice == 'n')
        {
            calculateSSS(i);
        }
        else
        {
            cout<<"\nINVALID INPUT";
            goto TARD;
        }
}

//REGULAR AND HOLIDAY OVERTIME
void Regular(int i)
{
    int day, type, days=0;
    char ans;
    double factor, addpay=0, hours;
    const double factors[17] = {0, 1.0, 1.3, 1.3, 1.5, 2, 2.6, 3, 3.9, 1.25, 1.69, 1.95, 2.6, 3.38, 3.9, 4.29};

    REG: cout<<"\n*****REGULAR*****"
        <<"\n[1] Regular Day"
        <<"\n[2] Rest Day"
        <<"\n[3] Special Holiday"
        <<"\n[4] Special Holiday Falling on the Rest Day"
        <<"\n[5] Holiday"
        <<"\n[6] Holiday Falling on Rest Day"
        <<"\n[7] Double Holiday"
        <<"\n[8] Double Holiday Falling on Rest Day"
        <<"\n[9] Regular Day + Overtime"
        <<"\n[10] Rest Day + Overtime"
        <<"\n[11] Special Holiday"
        <<"\n[12] Special Holiday Falling on the Rest Day + Overtime"
        <<"\n[13] Holiday + Overtime"
        <<"\n[14] Holiday Falling on Rest Day + Overtime"
        <<"\n[15] Double Holiday + Overtime"
        <<"\n[16] Double Holiday Falling on Rest Day + Overtime"
        <<"\nChoose Factor: ";
    day=readInt(1, 17);

    cout<<"\n[1] Worked the Day(8 hours)"
        <<"\n[2] Overtime Hours"
        <<"\nChoose: ";
    type=readInt(1, 2);

    if(type==1)
    {
        if(day==1)
        {
            cout<<"\nThe Regular day pay is already in Basic Pay.";
            return;
        }

        cout<<"\nHow many Days: ";
        days=readInt(1, 31);
        
        addpay = payrollRecords[i].hourlyRate*factors[day]*8;
    }
    else
    {
        if(day==1)
        {
            factor=1.25;
        }
    
        else
        {
            factor=factors[day]*1.3;
        }
            
        cout<<"\nOvertime Hours: ";
        hours=readDouble(0, 24);
            
        cout<<"\nHow many Overtime Days: ";
        days=readInt(1, 31);
            
        addpay = payrollRecords[i].hourlyRate*factor*hours;
    }

    payrollRecords[i].otpay = addpay*days;

    cout<<"\n*****CALCULATIONS*****"
        <<"\nPay per Day: Php "<<addpay
        <<"\nTotal: Php "<<payrollRecords[i].otpay;
        
    payrollRecords[i].totalOT += payrollRecords[i].otpay;
    savePayroll();
}

//CALCULATIONS FOR NIGHT DIFFERENTIAL
void NightDiff(int i)
{
    int day, ot;
    char ans;
    double factor, nighthours;
    const double factors[15] = {0, 1.0, 1.25, 1.3, 1.69, 1.3, 1.69, 1.5, 1.95, 2.0, 2.6, 2.6, 3.38, 3.9, 3.9};

    NIGHTDIF: cout<<"\n ________________________________"
        <<"\n|                                |"
        <<"\n|       NIGHT DIFFERENTIAL       |"
        <<"\n|________________________________|";

    cout<<"\n[1] Regular day"
        <<"\n[2] Regular day + Overtime"
        <<"\n[3] Rest day"
        <<"\n[4] Rest day + Overtime"
        <<"\n[5] Special holiday"
        <<"\n[6] Special holiday + Overtime"
        <<"\n[7] Special holiday on rest day"
        <<"\n[8] Special holiday on rest day + Overtime"
        <<"\n[9] Holiday"
        <<"\n[10] Holiday + Overtime"
        <<"\n[11] Holiday on rest day"
        <<"\n[12] Holiday on rest day + Overtime"
        <<"\n[13] Double holiday"
        <<"\n[14] Double holiday + Overtime"
        <<"\n[15] Double holiday on rest day"
        <<"\nType of day: ";
    day=readInt(1,15);

    cout<<"\n[1] Night shift only"
        <<"\n[2] Night shift + Overtime"
        <<"\nChoose: ";
    ot=readInt(1,2);

    factor = factors[day];
    if(ot==2)
    {
        if(day==1)
            factor = 1.25;
        else
            factor = factor * 1.3;
    }

    cout<<"Night Hours (10PM-6AM): ";
    nighthours=readDouble(0,24);

    payrollRecords[i].totalotpay = payrollRecords[i].hourlyRate * factor * 0.10 * nighthours;

    cout<<"\n*****CALCULATIONS*****"
        <<"\nNight Differential Pay: Php "<<payrollRecords[i].totalotpay;

    payrollRecords[i].totalND += payrollRecords[i].totalotpay;
    savePayroll();
}

//FUNCTION FOR MENU OF OVERTIME
void overtime(int i)
{
    int type;
    char ans;

    OVER: cout<<"\n ______________________"
        <<"\n|                      |"
        <<"\n|       OVERTIME       |"
        <<"\n|______________________|"
        <<"\n\n[1] Regular"
        <<"\n[2] Holiday"
        <<"\n[3] Night Differential"
        <<"\n[4] None"
        <<"\nYour Type of OT: ";
    type=readInt(1, 4);

    switch(type)
    {
        case 1:
        {
            Regular(i);
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                goto TOTALEARN;
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
            Regular(i);
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                goto TOTALEARN;
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
            NightDiff(i);
            cout<<"\nOther Overtime? [Y]Yes or [N]No: ";
            cin>>ans;

            if(ans=='Y'|| ans=='y')
            {
                goto OVER;
            }
            else if(ans=='N' || ans=='n')
            {
                goto TOTALEARN;
            }
            else
            {
                cout<<"\nInvalid.";
                goto OVER;
            }
            goto TOTALEARN;
        }
        case 4:
        {
            goto TOTALEARN;
        }
    }

    TOTALEARN: payrollRecords[i].totalEarnings = payrollRecords[i].basicPay + payrollRecords[i].totalOT + payrollRecords[i].totalND
                                                + payrollRecords[i].leaveconversion + payrollRecords[i].totalThirteenMonth + payrollRecords[i].TotalDeMinimisExcess;
    cout<<"\nTotal Earnings after Overtime Pay + Basic Pay: Php "<<payrollRecords[i].totalEarnings;
    tardiness(i);
}

//CALCULATION FOR BASIC PAY OF EMPLOYEES
void employeeBasicPay(int i) 
{
    int days, stdDays;
    string month;
    char choice, conv;

    payrollRecords[i].ratePerHour = payrollRecords[i].hourlyRate;

    cout<<"Enter Month: ";
    cin>>month;
    cout<<"Regular Working Days(PAY PERIOD) in a month(e.g. 11): ";
    days=readInt(1,31);
    cout<<"Leave Balance: "<<payrollRecords[i].leavebalance<<" day(s)";
    cout<<"\nPaid Leave Days used(0 if none): ";
    payrollRecords[i].leavedays=readInt(0, payrollRecords[i].leavebalance);
    cout<<"\nLeave Without Pay Days(0 if none): ";
    int unpaidDays=readInt(0, days-payrollRecords[i].leavedays);

    payrollRecords[i].ratePerDay = payrollRecords[i].ratePerHour*8;
    payrollRecords[i].leavepay = payrollRecords[i].ratePerDay*payrollRecords[i].leavedays;
    payrollRecords[i].semiMonthly = payrollRecords[i].ratePerDay*(days-unpaidDays);
    payrollRecords[i].monthlyRate = payrollRecords[i].semiMonthly*2;
    payrollRecords[i].basicPay = payrollRecords[i].semiMonthly;

    cout<<"\n*****BASIC PAY SUMMARY*****"
        <<"\nRate Per Hour: Php "<<payrollRecords[i].ratePerHour
        <<"\nRate Per Day: Php "<<payrollRecords[i].ratePerDay
        <<"\nSemi-Monthly Rate: Php "<<payrollRecords[i].semiMonthly
        <<"\nMonthly Rate: Php "<<payrollRecords[i].monthlyRate
        <<"\nBasic Pay: Php "<<payrollRecords[i].basicPay;
    
    cout<<"\nConvert unused leave to cash? [Y]Yes or [N]No: ";
    cin>>conv;

    if(conv =='Y' || conv =='y')
    {
        payrollRecords[i].converteddays = payrollRecords[i].leavebalance - payrollRecords[i].leavedays;
        payrollRecords[i].leaveconversion = payrollRecords[i].converteddays * payrollRecords[i].ratePerDay;
    }

    cout<<"\nInclude 13th month pay? [Y]Yes or [N]no: ";
    cin>>choice;

    if(choice =='Y' || choice =='y')
    {
        cout<<"Months worked this year: ";
        int months=readInt(1, 12);
        payrollRecords[i].totalThirteenMonth = payrollRecords[i].monthlyRate*months/12;
        //USE IN DECEMBER OR FINAL PAY RUN ASSUMING THE SAME SALARY ALL YEAR
    }
    overtime(i);

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
                
        cout<<"\nPLEASE ENTER THE NUMBER OF WHAT YOU WANT TO DO:"
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

                cout<<"\nPLEASE ENTER THE NUMBER OF WHAT YOU WANT TO DO:"
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
                                                            
                if(step > 5 || step < 1)
                {
                    cout<<"\nINVALID.";
                    goto ACCM;
                }

                switch(step)
                {
                    case 1: //ADD ACCOUNT
                    {
                        if(usercount>=100)
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
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                goto ACCM;
                            }
                        }
                                
                        cout<<"Enter Password: ";
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
                                newrole = "Employee";
                                break;
                        }

                        if(newrole == "Employee")
                        {
                            bool idExists = false;
                            
                            for(int i=0; i<empcount; i++)
                            {
                                if(newusername == employeeDetails[i].id)
                                {
                                    idExists = true;
                                }
                            }

                            if(!idExists)
                            {
                                cout<<"No Employee with that ID. Username must match an Employee ID.";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                goto ACCM;
                            }
                        }

                        users[usercount].username = newusername;
                        users[usercount].password = newpassword;
                        users[usercount].role = newrole;

                        usercount++;
                        saveAccounts();
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

                                for(int j=i; j<usercount-1; j++)
                                {
                                    users[j] = users[j+1];
                                }

                                usercount--;
                                saveAccounts();
                                cout<<"\nAccount successfully deleted.";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    
                                found = true;
                                goto ACCM;
                            }
                        }
                        if(!found)
                        {
                            cout<<"\nUser Not Found.";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                                cout<<"Enter current password: ";
                                cin>>currpassword;

                                for(int error=1; error<=3; error++)
                                {
                                    if(currpassword == users[i].password)
                                    {
                                        cout<<"Enter New Password: ";
                                        cin>>newpassword;

                                        users[i].password = newpassword;
                                        saveAccounts();

                                        cout<<"\nPassword successfully changed.";
                                        found = true;
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            default:
                cout<<"Invalid Choice.";
                goto ADMIN;
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
                
        cout<<"\nPLEASE ENTER THE NUMBER OF WHAT YOU WANT TO DO:"
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
                string delemployee;
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
                            for(int j=i; j<empcount-1; j++)
                            {
                                employeeDetails[j] = employeeDetails[j+1];
                            }

                            empcount--;
                            saveEmployees();
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
                string empID, newID;
                double hourRate;
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
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if(ans=='A' || ans=='a')
                        {
                            cout<<"\nInput Change: ";
                            getline(cin, newname);

                            while(newname.empty())
                            {
                                cout<<"Type Something."
                                    <<"\nInput Change: ";
                                getline(cin, newname);
                            }

                            employeeDetails[i].name = newname;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";

                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='B' || ans=='b')
                        {
                            cout<<"\nInput Change: ";
                            getline(cin, newID);

                            employeeDetails[i].id = newID;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";

                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='C' || ans=='c')
                        {
                            cout<<"\nInput Change: ";
                            getline(cin, newpos);

                            while(newpos.empty())
                            {
                                cout<<"Type Something."
                                    <<"\nInput Change: ";
                                getline(cin, newpos);
                            }

                            employeeDetails[i].position = newpos;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";

                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='D' || ans=='d')
                        {
                            cout<<"\nInput Change: ";
                            getline(cin, newstat);

                            while(newstat.empty())
                            {
                                cout<<"Type Something."
                                    <<"\nInput Change: ";
                                getline(cin, newstat);
                            }

                            employeeDetails[i].status = newstat;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";

                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='E' || ans=='e')
                        {
                            cout<<"\nInput Change: ";
                            getline(cin, newdep);

                            while(newdep.empty())
                            {
                                cout<<"Type Something."
                                    <<"\nInput Change: ";
                                getline(cin, newdep);
                            }

                            employeeDetails[i].dep = newdep;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE #"<<i + 1;
                            cout<<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n__________________________";

                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='F' || ans=='f')
                        {
                            cout<<"\nInput Change: ";
                            cin>>hourRate;

                            employeeDetails[i].hourlyRate = hourRate;
                            cout<<"\nChanges successful.";

                            cout<<"\nEMPLOYEE DETAILS"
                                <<"\nNAME: "<<employeeDetails[i].name
                                <<"\nID: "<<employeeDetails[i].id
                                <<"\nPOSITION: "<<employeeDetails[i].position
                                <<"\nSTATUS: "<<employeeDetails[i].status
                                <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                                <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                                <<"\n______________________________";
                            
                            saveEmployees();
                            found = true;
                        }
                        else if(ans=='G' || ans=='g')
                        {
                            found = true;
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
                break;
            }
            case 5: //EXIT
            {
                cout<<"\nLogging out....";
                break;
            }
            default:
                cout<<"Invalid Choice.";
                goto HR;
                break;
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
                    
            cout<<"\nPLEASE ENTER THE NUMBER OF WHAT YOU WANT TO DO:"
                <<"\n[1] View Employee Information"
                <<"\n[2] Process Payroll"
                <<"\n[3] View Employee Payroll Summary"
                <<"\n[4] Exit";
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
                    break;
                }
                case 2: //PROCESS PAYROLL
                {
                    string empID, period;
                    bool found = false;

                    if(payrollcount >= 100)
                    {
                        cout<<"\nPayroll Records storage is full.";
                        return;
                    }

                    SEARCH: cout<<"\n\n*****PAYROLL PROCESS*****";
                    cout<<"\nPay Period: ";
                    getline(cin, period);

                    while(period.empty())
                    {
                        cout<<"\nType Something."
                            <<"\nPay Period: ";
                        getline(cin, period);

                    }

                    cout<<"Enter Employee ID: ";
                    cin>>empID;
                    
                    for(int i=0; i<empcount; i++)
                    {
                        if(empID == employeeDetails[i].id)
                        {
                            found = true;
                            int r = payrollcount;

                            payrollRecords[r] = payroll();
                            payrollRecords[r].payPeriod = period;
                            payrollRecords[r].id = employeeDetails[i].id;
                            payrollRecords[r].name = employeeDetails[i].name;
                            payrollRecords[r].position = employeeDetails[i].position;
                            payrollRecords[r].status = employeeDetails[i].status;
                            payrollRecords[r].dep = employeeDetails[i].dep;
                            payrollRecords[r].hourlyRate = employeeDetails[i].hourlyRate;
                            payrollRecords[r].leavebalance = employeeDetails[i].leavebalance;

                            employeeBasicPay(r);
                            finalizePayroll(r);

                            employeeDetails[i].leavebalance -= payrollRecords[r].leavedays + payrollRecords[r].converteddays;
                            payrollcount++;
                            payrollSummary(r);
                            break; 
                        }
                    }
                    if(!found)
                    {
                        cout<<"\nEmployee not Found";
                        goto SEARCH;
                    }
                    break;
                }
                case 3: //VIEW EMPLOYEE PAYROLL SUMMARY
                {
                    string empID;
                    bool found = false;

                    cout<<"\nEnter Employee ID: ";
                    cin>>empID;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    for(int r=payrollcount-1; r>=0; r--)
                    {
                        if(empID == payrollRecords[r].id)
                        {
                            found = true;
                            payrollSummary(r);
                            break;
                        }
                    }
                    if(!found){
                        cout<<"\nNo payroll found for that employee.";
                    }
                    break;
                }
                case 4: //EXIT
                {
                    cout<<"\nLogging out....";
                    break;
                }
                default:
                    cout<<"Invalid Choice.";
                    goto PAYOFF;
            }
    }while(action!=4);
}

void accountantMenu()
{
    do
    {
        ACC: cout<<"\n ____________________________________\n"
            <<"|                                    |\n"
            <<"|             ACCOUNTANT             |\n"
            <<"|____________________________________|\n";
                    
            cout<<"\nPLEASE ENTER THE OF NUMBER WHAT YOU WANT TO DO:"
                <<"\n[1] View Payroll Records"
                <<"\n[2] View Net Pay"
                <<"\n[3] View Employee Payroll Summary"
                <<"\n[4] Exit";
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
                    viewPayrollRecords();
                    break;
                }
                case 2: //VIEW NET PAY
                {
                    string tempid;
                    bool found = false;

                    cout<<"\n***** NET PAY *****";
                    cout<<"\nEmployee ID: ";
                    cin>>tempid;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    for(int r=payrollcount-1; r>=0; r--)
                    {
                        if(tempid == payrollRecords[r].id)
                        {
                            cout<<"\nName: "<<payrollRecords[r].name
                                <<"\nPay Period: "<<payrollRecords[r].payPeriod
                                <<"\nNet Pay: Php "<<payrollRecords[r].netPay;
                            
                            found = true;
                            break;
                        }
                    }

                    if(!found)
                    {
                        cout<<"\nEmployees not found or hasnt been calculated.";
                    }
                    break;
                }
                case 3: //VIEW EMPLOYEE PAYROLL SUMMARY
                {
                    string empID;
                    bool found = false;

                    cout<<"\nEmployee ID: ";
                    cin>>empID;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    for(int r=payrollcount-1; r>=0; r--)
                    {
                        if(empID == payrollRecords[r].id)
                        {
                            found = true;
                            payrollSummary(r);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                    }

                    if(!found)
                    {
                        cout<<"\nEmployees not found or havent been calculated.";
                    }
                    break;
                }
                case 4: //EXIT
                {
                    cout<<"\nLogging out....";
                    break;
                }
                default:
                    cout<<"Invalid Choice.";
                    goto ACC;
            }
    }while (action!=4);
}

void employeeSummary(int i)
{
    cout << "\n ____________________________________\n"
         << "|                                     |\n"
         << "|            PAYROLL SUMMARY          |\n"
         << "|_____________________________________|\n";

    cout << "\nPay Period: " << payrollRecords[i].payPeriod
    << "\nTotal Earnings: Php " << payrollRecords[i].totalEarnings
    << "\nTotal Deductions: Php " << payrollRecords[i].totalDeductions
    << "\nNet Pay: Php " << payrollRecords[i].netPay
    << "\n ____________________________________\n";
}

void employeePayslip(int i){
    cout << "\n ____________________________________\n"
         << "|                                     |\n"
         << "|               PAYSLIP               |\n"
         << "|_____________________________________|\n";
         
    cout<<"\nEmployee ID: "<<payrollRecords[i].id
        <<"\nEmployee Name: "<<payrollRecords[i].name
        <<"\nPosition: "<<payrollRecords[i].position
        <<"\nDepartment: "<<payrollRecords[i].dep
        <<"\nStatus: "<<payrollRecords[i].status
        <<"\nPay Period: "<<payrollRecords[i].payPeriod
        <<"\n\n----------EARNINGS---------- "
        <<"\nBasic Salary: Php "<<payrollRecords[i].semiMonthly - payrollRecords[i].leavepay
        <<"\nLeave Pay: Php "<<payrollRecords[i].leavepay
        <<"\nLeave Cash-out: Php "<<payrollRecords[i].leaveconversion
        <<"\n13th Month Pay: Php "<<payrollRecords[i].totalThirteenMonth
        <<"\nOvertime Pay: Php"<<payrollRecords[i].totalOT
        <<"\nNight Differential: Php "<<payrollRecords[i].totalND
        <<"\n------------------------------ "
        <<"\nTotal Earnings: Php: "<<payrollRecords[i].totalEarnings
        <<"\n\n-------------DEDUCTIONS----------------- "
        <<"\nSSS: Php "<<payrollRecords[i].sssDeduction
        <<"\nPhilHealth Php: "<<payrollRecords[i].PHTotalContribution
        <<"\nPag-IBIG: Php"<<payrollRecords[i].PBTotalContribution
        <<"\nWithholding Tax: Php "<<payrollRecords[i].totalWHT
        <<"\nTardiness: Php: "<<payrollRecords[i].LateDeduction
        <<"\n------------------------------ "
        <<"\nTOTAL DEDUCTIONS: Php "<<payrollRecords[i].totalDeductions
        <<"\n------------------------------ "
        <<"\nNET PAY: Php "<<payrollRecords[i].netPay;
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
            <<"\n[2] View Payroll Summary"
            <<"\n[3] View Payslip"
            <<"\n[4] Exit";
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

        switch(action)
        {
            case 1: //VIEW INFORMATION
            {
                bool found = false;

                cout<<"\n*****Employee Information*****";

                for(int i=0; i<empcount; i++)
                {
                    if(currentuser == employeeDetails[i].id)
                    {
                        cout<<"\nNAME: "<<employeeDetails[i].name
                            <<"\nID: "<<employeeDetails[i].id
                            <<"\nPOSITION: "<<employeeDetails[i].position
                            <<"\nSTATUS: "<<employeeDetails[i].status
                            <<"\nDEPARTMENT: "<<employeeDetails[i].dep
                            <<"\nHOURLY RATE: "<<employeeDetails[i].hourlyRate
                            <<"\n__________________________";

                        found = true;
                        goto EMP;
                    }
                }
                if(!found)
                {
                    cout<<"\nNo employee record found for your account.";
                    goto EMP;
                }
                break;
            }
            case 2: //VIEW PAYROLL SUMMARY
            {
                bool found = false;
                
                for(int r=payrollcount-1; r>=0; r--)
                {
                    if(currentuser == payrollRecords[r].id)
                    {
                        employeeSummary(r);
                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout<<"\nNo payroll found for your account.";
                    goto EMP;
                }
                break;
            }
            case 3: //VIEW PAYSLIP
            {
                bool found = false;
                for(int r=payrollcount-1; r>=0; r--)
                {
                    if(currentuser == payrollRecords[r].id)
                    {
                        employeePayslip(r);
                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout<<"\nNo Payslip found for your account.";
                    goto EMP;
                }
                break;
            }
            case 4:
            {
                cout<<"\nLogging out....";
                break;
            }
            default:
                    cout<<"Invalid Choice.";
                    goto EMP;
        }
    }while(action!=4);


}

//MAIN
int main()
{
    cout<<fixed<<setprecision(2);
    loadAccounts();
    loadEmployees();
    loadPayrollRecords();

    LOGIN: cout<<"\n ____________________________\n"
            <<"|                            |\n"
            <<"|          WELCOME           |\n"
            <<"|____________________________|\n";

        cout<<"\nUsername: ";
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

                cout<<"\nLogin Successful.";
                cout<<"\nWelcome "<<currentuser<<"!\n";
                
                found=true;
            }
        }
        if(!found)
        {
            cout<<"\nINVALID USERNAME AND PASSWORD.";
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
    
        return 0;
}



