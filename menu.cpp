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

    struct payrollRecords{
        int id
        string name, position, status, dep;
        
    }

    
    employee employeeDetails[100];
    user users[20]={
        {"admin", "1234", "Admin"},
        {"hr001","1234", "HR"},
        {"payroff01", "1234", "Payroll Officer"},
        {"account001", "1234", "Accountant"},
        {"employee01", "1234", "Employee"}
    };
    employee payrollRecords[100];

    int empcount=0, usercount=5, payrollcount=0, action, searchid, step;
    string tempaction, tempstep, username, password, currentrole, currentuser;
    char choice;



//FUNCTIONS
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
            case 1: //ADD EMPLOYEE
            {
                if(empcount>=100)
                {
                    cout<<"Employees Storage is Full\n";
                    goto ADMIN;
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
                goto ADMIN;
            }   

            case 2: //VIEW ACCOUNTS
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
                        if(usercount>=100)
                        {
                            cout<<"Account Storage is Full\n";
                            return;
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

            case 3: //VIEW EMPLOYEE RECORDS
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

void hrMenu(){
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
                if(empcount>=100)
                {
                    cout<<"Employees Storage is Full\n";
                    goto HR;
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

                                                    
                empcount++;
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
                if(empcount == 0)
                {
                    cout<<"\nNO EMPLOYEES HAVE BEEN ADDED.";
                    goto HR;
                }
    
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

                        if(ans=='a' || 'A')
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
    } while (action!=5);
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
                case 1: //VIEW EMPLOYEE INFORMAATION
                {
                    if(empcount == 0)
                    {
                        cout<<"\nNO EMPLOYEES HAVE BEEN ADDED.";
                        goto PAYOFF;
                    }
        
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
                    goto PAYOFF;
                }
                case 2: //PROCESS PAYROLL
                {

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

        switch(action)
        {
            case 1: //VIEW INFORMATION
            {
                int empID;
                bool found = false;

                cout<<"\n*****Employee Information*****";
                cout<<"\nInput Employee ID: ";
                cin>>empID;

                for(int i=0; i<empcount; i++)
                {
                    if(empID == employeeDetails[i].id)
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
                    cout<<"\nEmployee not found.";
                    goto EMP;
                }
            }
            case 2: //VIEW PAYSLIP
            {
                goto EMP;
            }
            case 3: //EXIT
            {
                cout<<"\nLogging out....";
                break;
            }
        }
    } while (action!=3);
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