//#include "ui.h"
#include "Bank.h"
#include "Loan.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdio.h>


int displayMenu();
string setPassword(); //string fname, string lname
void setBirth();
string getBirthday(int day, int month, int year);
void displayUsersAccounts(string username, string password);
string birthdate;
bool checkedInput(string s1, string s2);
bool is_number(string value);
void displayMenu2();

std::vector<Account*> accounts;
//Account** accArr = new Account*[200];

using namespace std;

int main()
{
    bool looping, validity1, validity2;
    string str1, s1, s2, input, choice, loanAmount, income, creditScoreV2, years;
    string name;
    string username;
    string password;
    string question1;
    string answer1;
    string question2;
    string answer2;
    string accountTypeStr;
    int accountType;
    int returningUser = 0; //returningUserStr string to returningUser int
    int creditScore;
    
    do //do until there is a request to exit
    {
        string returningUserStr = "0";
        int option = 0; //menu option
        
        //Run until browser closed.
        cout << "Welcome to online banking." << endl;
        cout << "1. Login" << endl;
        cout << "2. Create account" << endl;
        cout << "3. Exit" << endl;
        cout << "Please enter a number: ";
        cin >> returningUserStr;
        
        //Check if valid input
        while (returningUserStr.compare("1") != 0 && returningUserStr.compare("2") != 0 &&
               returningUserStr.compare("3") != 0)
        {
            cout << "Invalid selection. Please try again: ";
            cin >> returningUserStr;
        }
        
        //Change string to int
        if (returningUserStr.compare("1") == 0)
        {
            returningUser = 1;
        }
        else if (returningUserStr.compare("2") == 0)
        {
            returningUser = 2;
        }
        else if (returningUserStr.compare("3") == 0)
        {
            returningUser = 3;
        }
        
        //Login or create new account
        switch (returningUser)
        {
            case 1: //returning user
            {
                cout << "Welcome back..." << endl;
                //pass to Person
                break;
            }
            case 2: //new user
            {
                cout << "Creating new account..." << endl;
                cin.get();
                cout << "Please enter your full name: ";
                getline(cin, name);
                cout << "Please enter your username: ";
                getline(cin, name);
                password = setPassword();
                setBirth();
                cin.get();
                cout << "\nSecurity questions are case-sensitive." << endl;
                cout << "\nPlease enter your first security question: ";
                getline(cin, question1);
                cout << "\nPlease enter the answer: ";
                getline(cin, answer1);
                cout << "\nPlease enter your second security question: ";
                getline(cin, question2);
                cout << "\nPlease enter the answer: ";
                getline(cin, answer2);
                cout << "\nPlease select the type of account you would like to create:" << endl;
                cout << "1. Savings \n2. Checking \n3. Credit Card" << endl;
                cin >> accountTypeStr;
                
                while (accountTypeStr.compare("1") != 0 && accountTypeStr.compare("2") != 0
                       && accountTypeStr.compare("3") != 0)
                {
                    cout << "Invalid selection. Please try again: ";
                    cin >> accountTypeStr;
                }
                
                //Change string to int
                if (accountTypeStr.compare("1") == 0)
                {
                    accountType = 1;
                }
                else if (accountTypeStr.compare("2") == 0)
                {
                    accountType = 2;
                }
                else if (accountTypeStr.compare("3") == 0)
                {
                    accountType = 3;
                }
                
                switch (accountType)
                {
                    case 1: //savings
                    {
                        accounts.push_back(new Savings(username, password, name, birthdate, question1, answer1, question2, answer2));
                        break;
                    }
                    case 2: //checking
                    {
                        accounts.push_back(new Checkings(username, password, name, birthdate, question1, answer1, question2, answer2));
                        break;
                    }
                    case 3: //credit card
                    {
                        cout << "Please enter your credit score." << endl;
                        cin >> creditScore;
                        accounts.push_back(new CreditCard(username, password, name, birthdate, question1, answer1, question2, answer2, creditScore));
                        break;
                    }
                    default: //error
                    {
                        cout << "Error." << endl;
                    }
                }
                break;
            }
            case 3: //exit
            {
                cout << "Have a nice day." << endl;
                exit(0);
                break;
            }
            default: //error
            {
                cout << "Error." << endl;
            }
        }
        
        //How to implement?? From login to menu options
        //if returningUser !=3 ...
        do
        {
            option = displayMenu();
            
            switch (option)
            {
                case 1: //view accounts
                {
                    //accounts
                    displayUsersAccounts(username, password);
                    break;
                }
                case 2: //view transactions
                {
                    //bought
                    break;
                }
                case 3: //transfer money
                {
                    //accounts
                    displayUsersAccounts(username, password);
                    
                    int fromAccountNumber;
                    int toAccountNumber;
                    int amount;
                    cout << "\nFrom which account do you want to transfer money?" << endl;
                    cout << "Enter account number: ";
                    cin >> fromAccountNumber;
                    cout << "To which account do you want to transfer money?" << endl;
                    cout << "Enter account number: ";
                    cin >> toAccountNumber;
                    cout << "Enter amount to transfer" << endl;
                    cin >> amount;
                    
                    bool fromAcc = false;
                    bool toAcc = false;
                    vector<Account*>::iterator iter;
                    int i = 0;
                    for (iter = accounts.begin(); iter != accounts.end(); iter++) {
                        if (accounts.at(i)->getAccountNumber() == fromAccountNumber) {
                            fromAcc = true;
                        }
                        if (accounts.at(i)->getAccountNumber() == toAccountNumber) {
                            toAcc = true;
                        }
                        i++;
                    }
                    if (fromAcc && toAcc) {
                        int i = 0;
                        for (iter = accounts.begin(); iter != accounts.end(); iter++) {
                            if (accounts.at(i)->getAccountNumber() == fromAccountNumber) {
                                accounts.at(i)->transfer(fromAccountNumber, toAccountNumber, amount);
                                break;
                            }
                        }
                    }
                    else {
                        cout << "Account number(s) was/were not found" << endl;
                    }
                    
                    break;
                }
                case 4: //apply for a loan
                {
                    
                    //note: we treat our constructor paramters as strings first before we parse them to doubles and ints
                    //we do this because we don't want to assume the user enters in correct values and we later get an
                    //invalid instance of the object
                    
                    looping = true;
                    
                    cout<<"Would you like to apply for a loan?"<<endl;
                    
                    cin>>input;
                    
                    str1= "no";
                    
                    s1= "yes";
                    
                    s2 = input;
                    
                    validity1=checkedInput(s1,s2);
                    
                    validity2= checkedInput(str1,s2);
                    
                    while(looping){
                        
                        if(validity1||validity2){
                            
                            looping=false;
                            
                        }
                        else{
                            
                            cout<<"Please enter yes or no, would u like to apply for a loan? "<<endl;
                            
                            cin>>input;
                            
                            validity1=checkedInput(input,s1);
                            
                            validity2=checkedInput(str1,input);
                        }
                        
                    }
                    
                    if(validity1){
                        
                        //Below are the required values to construct our loan object
                        while(looping){
                            
                            displayMenu2();
                            
                            cin>>choice;
                            
                            if(choice!="8"){
                                
                                if(!is_number(choice)){
                                    
                                    cout<<"Invalid input"<<endl;
                                    
                                    continue;
                                }
                                
                            }
                            else if(choice=="8"){
                                
                                looping=false;
                                
                                return 0;
                                
                            }
                            
                        }
                        
                        cout<<endl;
                        
                        looping=true;
                        
                        while(looping){
                            
                            cout<< "Please enter loan amount: " <<endl;
                            
                            cin>> loanAmount;
                            
                            if(!is_number(loanAmount)){
                                
                                cout<<"Invalid input!"<<endl;
                                
                                continue;
                                
                            }
                            else{
                                
                                looping=false;
                            }
                            
                            
                        }
                        
                        looping=true;
                        
                        while(looping){
                            
                            cout<<"Please enter your income: "<<endl;
                            
                            cin>> income;
                            
                            if(!is_number(income)){
                                
                                cout<<"Invalid input!"<<endl;
                                
                                continue;
                                
                            }
                            else{
                                
                                looping=false;
                            }
                            
                        }
                        
                        looping=true;
                        
                        while(looping){
                            
                            cout<<"Credit Score: "<<endl;
                            
                            cin>> creditScoreV2;
                            
                            if(!is_number(creditScoreV2)){
                                
                                cout<<"Invalid input!"<<endl;
                                
                                continue;
                                
                            }
                            else{
                                
                                looping=false;
                            }
                            
                        }
                        
                        looping=true;
                        
                        while(looping){
                            
                            cout<<"Amount of time planned to pay off loan (in years): "<<endl;
                            
                            cin>> years;
                            
                            if(!is_number(years)){
                                
                                cout<<"Invalid input!"<<endl;
                                
                                continue;
                            }
                            else{
                                
                                looping=false;
                            }
                            
                        }
                        
                        looping = true;
                        
                        double doubleLoanAmount=atof(loanAmount.c_str());
                        
                        double doubleIncome=atof(income.c_str());
                        
                        int intCreditScore=atof(creditScoreV2.c_str());
                        
                        int intYears=atof(years.c_str());
                        
                        int intChoice=atof(years.c_str());
                        
                        Loan *l= new Loan(doubleLoanAmount,doubleIncome,intCreditScore,intYears,intChoice);
                        
                        l->getLoan();
                        
                        l->setLoanRates();
                        
                        l->printLoan();
                        
                        
                        
                        cout<<"Would you like to assess your net worth? "<<endl;
                        
                        cin>>choice;
                        
                        if(checkedInput(choice,s1)){
                            
                            l->getWorth();
                            
                            cout<<"Thank you for your time!"<<endl;
                            
                        }
                        
                        else if(checkedInput(choice, str1)){
                            
                            cout<<"Thank you for your time!"<<endl;
                            
                        }
                        else{
                            
                            while(looping){
                                
                                cout<<"Please enter yes or no, would you like to assess your net worth?"<<endl;
                                
                                cin>>choice;
                                
                                if(checkedInput(choice,s1)){
                                    
                                    l->getWorth();
                                    
                                    cout<<"Thank you for your time!"<<endl;
                                    
                                    looping=false;
                                }
                                else if(checkedInput(str1,choice)){
                                    
                                    cout<<"Thank you for your time!"<<endl;
                                }
                                
                                else{
                                    
                                    continue;
                                }
                            }
                            
                        }
                        
                        
                    }
                    
                    
                    
                    else if(validity2){
                        
                        cout<<"Thank you for your time!"<<endl;
                        
                    }
                    
                    break;
                }
                case 5: //view money market
                {
                    //money market
                    break;
                }
                case 6: //view personal info
                {
                    //info
                    break;
                }
                case 7: //logout
                {
                    cout << "You are now logged out." << endl;
                    //sleep function
                    
                    break;
                }
                default:
                {
                    //
                    break;
                }
                    
                    //pass to Simulation after every menu option
            }
            
            
        } //end of menu loop
        while (option < 7 && option > 0);
        
        //Sleep(4000); //milliseconds?
        //Sleep function here!!!!
        
    } while (returningUser != 3);
    
    
    
    return 0;
}

int displayMenu() //Interface::
{
    int optionInt = 0;
    string optionStr = "0";
    
    cout << "Menu Options: " << endl;
    cout << "1. View accounts" << endl;
    cout << "2. View recent transactions" << endl;
    cout << "3. Transfer funds" << endl;
    cout << "4. Apply for a loan" << endl;
    cout << "5. View money market" << endl;
    cout << "6. My Profile" << endl;
    cout << "7. Logout" << endl;
    cout << "Please make a selection: ";
    cin >> optionStr;
    
    while (optionStr.compare("1") != 0 && optionStr.compare("2") != 0 && optionStr.compare("3") != 0
           && optionStr.compare("4") != 0 && optionStr.compare("5") != 0 && optionStr.compare("6") != 0
           && optionStr.compare("7")) //while not a number 1-7
    {
        cout << "Invalid selection. Please try again: ";
        cin >> optionStr;
    }
    
    //Change string to int
    if (optionStr.compare("1") == 0)
    {
        optionInt = 1;
    }
    else if (optionStr.compare("2") == 0)
    {
        optionInt = 2;
    }
    else if (optionStr.compare("3") == 0)
    {
        optionInt = 3;
    }
    else if (optionStr.compare("4") == 0)
    {
        optionInt = 4;
    }
    else if (optionStr.compare("5") == 0)
    {
        optionInt = 5;
    }
    else if (optionStr.compare("6") == 0)
    {
        optionInt = 6;
    }
    else if (optionStr.compare("7") == 0)
    {
        optionInt = 7;
    }
    
    
    return optionInt;
}

void setBirth() //Accout::
{
    int month;
    int day;
    int year;
    int temp = 0;
    
    while (1)
    {
        cout << "Please enter your birth year: " << endl;
        cin >> temp;
        
        if (cin.fail())
        {
            cout << "Birth year must be an integer." << endl;
            continue;
        }
        else if (temp > 2003 || temp < 1900)
        {
            cout << "You need to be alive and over 13 years old." << endl;
            continue;
        }
        else
        {
            year = temp;
            break;
        }
        
        //could implement leap year but may be not really necessary
    }
    
    while (1)
    {
        cout << "Please enter your birth month: " << endl;
        cin >> temp;
        
        if (cin.fail())
        {
            cout << "Birth month must be an integer." << endl;
            continue;
        }
        else if (temp < 1 || temp>12)
        {
            cout << "Must enter a valid month." << endl;
            continue;
        }
        else
        {
            month = temp;
            break;
        }
    }
    
    while (1)
    {
        cout << "Please enter the day you were born: " << endl;
        cin >> temp;
        
        if (cin.fail())
        {
            cout << "Birth day must be an integer." << endl;
            continue;
        }
        else
        {
            day = temp;
            break;
        }
        // between days in specific month
        //still need to add
    }
    getBirthday(day, month, year);
}

string getBirthday(int day, int month, int year) //Accout::
{
    birthdate = "";
    stringstream sstm;
    sstm << month << "/" << day << "/" << year;
    birthdate = sstm.str();
    return birthdate;
}

string setPassword()//include fname, lname
{
    int validCount; //counts how many measures the password contains (uppercase, symbol, etc)
    int passCount; //counts how many times incorrect password is input when retyped
    string tempPass; //password taken from user
    string pass2; //user reenters pass1,
    string password; //final password if tempPass == pass2
    bool includeUpper = false; //password includes uppercase letter
    bool includeLower = false;
    bool includeSymbol = false; //password includes symbol
    bool includeNumber = false; //password includes number
    bool includeName = false; //password does not include name
    char tempPassArray[40]; //stores tempPass in char array
    bool validPass = false;
    bool matchingPass = false;
    
    do //while password entry 1 and 2 match
    {
        validPass = false;
        validCount = 0;
        
        while (validPass != true)
        {
            //reset bool values
            validCount = 0;
            passCount = 0;
            includeUpper = false;
            includeSymbol = false;
            includeNumber = false;
            includeName = false;
            includeLower = false;
            
            //Get password from user
            cout << "Please enter your new password: ";
            getline(cin, tempPass);
            
            while (tempPass.length() < 8 || tempPass.length() > 40) //check for valid length
            {
                cout << "Invalid password length. Please try again: ";
                getline(cin, tempPass);
            }
            
            strcpy(tempPassArray, tempPass.c_str()); //fill char array with identifier
            
            for (size_t i = 0; i < tempPass.length(); i++) //get password attributes
            {
                if ((tempPassArray[i] >= 48 && tempPassArray[i] <= 57) && includeNumber == false) //if a number
                {
                    includeNumber = true;
                    validCount++;
                }
                
                if ((tempPassArray[i] >= 65 && tempPassArray[i] <= 90) && includeUpper == false) //if uppercase
                {
                    includeUpper = true;
                    validCount++;
                }
                
                if ((tempPassArray[i] >= 97 && tempPassArray[i] <= 122) && includeLower == false) //if lowercase
                {
                    includeLower = true;
                    validCount++;
                }
                
                if ((tempPassArray[i] == 33 || tempPassArray[i] == 35 || tempPassArray[i] == 36 ||
                     tempPassArray[i] == 38 || tempPassArray[i] == 47 || tempPassArray[i] == 63 ||
                     tempPassArray[i] == 64) && includeSymbol == false) //if includes a symbol
                {
                    includeSymbol = true;
                    validCount++;
                }
                
                //include if includes persons fname or lname
            }
            
            //cout << "Valid count is " << validCount;
            
            if (validCount != 4) //change to 5 w f/lname code
            {
                cout << "Your password must include ";
                
                if (includeNumber == false)
                {
                    cout << "a number";
                    if (validCount <= 2)
                        cout << ", ";
                    else
                        cout << " ";
                }
                
                if (includeUpper == false)
                {
                    cout << "an uppercase letter";
                    if (validCount <= 2)
                        cout << ", ";
                    else
                        cout << " ";
                }
                
                if (includeLower == false)
                {
                    cout << "a lowercase letter";
                    if (validCount <= 2)
                        cout << ", ";
                    else
                        cout << " ";
                }
                
                if (includeSymbol == false)
                {
                    cout << "a symbol";
                    if (validCount <= 2)
                        cout << ", ";
                    else
                        cout << " ";
                }
                
                cout << "and contain 8 - 40 characters. Please try again." << endl;
                
                validPass = false;
            }
            else if (validCount == 4) //change to 5 w f/lname code
            {
                validPass = true;
            }
            
        }
        
        cout << "Please retype your password to confirm: ";
        getline(cin, pass2);
        passCount = 0;
        
        while (tempPass.compare(pass2) != 0 && passCount < 3) //loops until password correct of 3+ tries
        {
            cout << "Your passwords do not match. Please try again: ";
            getline(cin, pass2);
            passCount++;
        }
        
        if (tempPass.compare(pass2) != 0)
        {
            matchingPass = false;
            
            cout << "You have exceeded the max amount of tries to make your passwords match." << endl;
        }
        else
        {
            matchingPass = true;
            
            password = tempPass;
            
            //cout << password << " is valid." << endl;
        }
        
    } while (matchingPass == false);
    
    return password;
}
void displayUsersAccounts(string username, string password) 
{
    vector<Account*>::iterator iter;
    int i = 0;
    for (iter = accounts.begin(); iter != accounts.end(); iter++) {
        if (accounts.at(i)->getUsername().compare(username) == 0 && accounts.at(i)->getPassword().compare(password) == 0) {
            cout << "\n\n*****  " << accounts.at(i)->getAccountType() << "  *****" << endl;
            cout << "Account Number: " << accounts.at(i)->getAccountNumber() << endl;
            cout << "Name: " << accounts.at(i)->GetFullName() << endl;
            cout << "Balance: " << accounts.at(i)->getBalance() << endl;
        }
        i++;
    }
}

//method used to find the equality of string ignoring case, by taking the desired string (in this case
//yes) and the input by the user it returns a boolean
bool checkedInput(string s1,string s2){
    
    if(s2.size()!=s1.size()){
        
        return false;
        
    }
    
    for(int i=0; i<s1.size();i++){
        
        if(tolower(s1[i])!=tolower(s2[i]))
            
            return false;
        
    }
    return true;
}

//method to make sure our inputed values won't create an invalid object
bool is_number(string value){
    
    bool valid=true;
    
    for(int i=0;i<value.size();i++){
        
        if(!isdigit(value.at(i))){
            
            valid=false;
        }
        
        
    }
    
    return valid;
}

void displayMenu2(){
    
    cout<<"Please select an option"<<endl;
    
    cout<<"--------------------------------------------------------"<<endl;
    
    cout<<"1. Apply for a new car loan"<<endl;
    
    cout<<"2. Apply for a used car loan"<<endl;
    
    cout<<"3. Apply for a new motorcycle loan"<<endl;
    
    cout<<"4. Apply for a used motorcylce loan"<<endl;
    
    cout<<"5. Apply for a personal loan"<<endl;
    
    cout<<"6. Apply for a loan for boats, campers, rv's etc."<<endl;
    
    cout<<"7. Apply for a loan for small vehicles (i.e. golf carts, tractors, ATV's)"<<endl;
    
    cout<<"8. Exit"<<endl;
    
    cout<<"--------------------------------------------------------"<<endl;
    
}



