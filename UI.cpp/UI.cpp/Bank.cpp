#include <iostream>
#include "Bank.h"
#include<stdlib.h>
#include<sstream>

// all account numbers
vector<int> Account::accountNumbers;
// all account balances
vector<double*> Account::accountsBalances;

//Account Class
Account::~Account() {}
// constructor to initialize username and password
Account::Account(string username, string password) {
    this->username = username;
    this->password = password;
    
    // assigns account number
    accountNumber = generateAccountNumber();
    accountNumbers.push_back(accountNumber);
}
// constructor initializes all values
Account::Account(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2) {
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->birthday = birthday;
    this->question1 = question1;
    this->answer1 = answer1;
    this->question2 = question2;
    this->answer2 = answer2;
    
    // assigns account number
    accountNumber = generateAccountNumber();
    accountNumbers.push_back(accountNumber);
}

string Account::getUsername() {
    return username;
}

string Account::getPassword() {
    return password;
}

void Account::setUsername(string username) {
    this->username = username;
}

void Account::setPassword(string password) {
    this->password = password;
}

int Account::getAccountNumber() {
    return accountNumber;
}
// Transfer money between accounts
void Account::transfer(int fromAccountNumber, int toAccountNumber, double amount) {
    if (checkAccountNumber(fromAccountNumber) && checkAccountNumber(toAccountNumber)) {
        vector<int>::iterator iterAccountNumber = accountNumbers.begin();
        vector<double*>::iterator iterBalance = accountsBalances.begin();
        while (iterAccountNumber != accountNumbers.end()) {
            if (fromAccountNumber == *iterAccountNumber) {
                **iterBalance -= amount;
            }
            if (toAccountNumber == *iterAccountNumber) {
                **iterBalance += amount;
            }
            iterAccountNumber++;
            iterBalance++;
        }
    }
    else {
        cout << "Unable to find Account Number" << endl;
    }
}

void Account::setfullName(string name) {
    fullName = name;
}
// Generate account number
int Account::generateAccountNumber() {
    int randomNumber = 0;
    
    do {
        randomNumber = rand() % 9000000 + 1000000;
    } while (checkAccountNumber(randomNumber) && accountNumbers.size() < 8999999);
    
    return randomNumber;
}
// Check whether an account number exsits
bool Account::checkAccountNumber(int accountNumber) {
    vector<int>::iterator iter;
    for (iter = accountNumbers.begin(); iter != accountNumbers.end(); iter++) {
        if (accountNumber == *iter) {
            return true;
        }
    }
    return false;
}

void Account::setBirthday(string birthday) {
    this->birthday = birthday;
}

string Account::getAccountType() {
    return accountType;
}

string Account::getBirthday() {
    return birthday;
}

string Account::getQuestion1() {
    return question1;
}

string Account::getQuestion2() {
    return question2;
}//maybe dont need this idk

string Account::getAnswer1() {
    return answer1;
}

string Account::getAnswer2() {
    return answer2;
}

// Reset password questions
void Account::ResetPassQuestions() {
    string tempans = "";
    int numcorrect = 0;
    int numwrong1 = 1;
    int numwrong2 = 1;
    cout << "You have selected to reset your password. Answer your questions to reset or press 1 to exit" << endl;
    while (1) {
        cout << question1 << endl;
        getline(cin, tempans);
        if (tempans == "1") {
            cout << "Exiting" << endl;
            break;
        }
        else if (tempans == answer1) {
            tempans = "";
            numcorrect++;
            break;
        }
        else if (numwrong1 == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else {
            cout << "Sorry does not match answer for question" << endl;
            numwrong1++;
            continue;
        }
    }
    while (numcorrect == 1 && numwrong1 != 3) {
        cout << question2 << endl;
        cin >> tempans;
        if (tempans == "1") {
            cout << "Exiting" << endl;
            break;
        }
        else if (numwrong2 == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else if (tempans == answer2) {
            tempans = "";
            numcorrect++;
            break;
        }
        else {
            cout << "Sorry does not match answer for question" << endl;
            numwrong2++;
            continue;
        }
    }
    if (numcorrect == 2) {
        cout << "New password:" << endl;
        getline(cin, tempans);
        getline(cin, tempans);
        password = tempans;
    }
}
// Reset ol password
void Account::OldPassReset() {
    string tempans = "";
    int numAttempts = 1;
    cout << "You have selected to reset your password. Type in your old password to reset" << endl;
    while (1) {
        getline(cin, tempans);
        if (cin.fail()) {
            FailedInput();//call method for failed input
            continue;
        }
        else if (numAttempts == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else if (tempans != password) {
            cout << "Your input does not match your old password" << endl;
            numAttempts++;
            continue;
        }
        else if (tempans == password) {
            cout << "Type in your new password" << endl;
            getline(cin, tempans);
            //check failed input
            password = tempans;
            break;
        }
    }
}

void Account::FailedInput() {
    cout << "Invalid input, Try again" << endl;
}

string Account::GetFullName() {
    return fullName;
}

void Account::setState(string state) {
    this->state = state;//check through states maybe
}

string Account::getState() {
    return state;
}

string Account::getPerson() {
    return username + "\n" + password + "\nQuestion1: " + question1 + "\nAnswer1: " + answer1 + "\nQuestion2: " + question2 + "\nAnswer2: " + answer2 + "\nName: " + fullName + "\nBirthday: " + birthday + "\n";
}

// CONSTRUCTORS
BankAccount::~BankAccount() {}

BankAccount::BankAccount(string username, string password) : Account(username, password) {
    balance = 0;
    accountsBalances.push_back(&balance);
}

BankAccount::BankAccount(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2) :
Account(username, password, fullName, birthday, question1, answer1, question2, answer2) {
    
    balance = 0;
    accountsBalances.push_back(&balance);
}

// deposit method
void BankAccount::deposit(double amount) {
    if (checkValidAmount(amount)) {
        balance += amount;
    }
    else {
        cout << "Deposits of negative amounts are not permitted" << endl;
    }
}
void BankAccount::deposit(int accountNumber, double amount) {
    if (checkAccountNumber(accountNumber)) {
        vector<int>::iterator iterAccountNumber = accountNumbers.begin();
        vector<double*>::iterator iterBalance = accountsBalances.begin();
        while (iterAccountNumber != accountNumbers.end()) {
            if (accountNumber == *iterAccountNumber) {
                **iterBalance += amount;
            }
            iterAccountNumber++;
            iterBalance++;
        }
    }
    
}
// withdrawal method
double BankAccount::withdrawal(double amount) { // check for overdraft
    if (checkValidAmount(amount)) {
        balance -= amount;
    }
    else {
        cout << "Withdrawals of negative amounts are not permitted" << endl;
    }
    
    return amount;
}
// GETTERS
double BankAccount::getBalance() {
    return balance;
}

string BankAccount::getLockBox(string item) {
    vector<string>::iterator iter;
    
    for (iter = box.begin(); iter != box.end(); iter++) {
        if (*iter == item) {
            return item;
        }
    }
    cout << "No item found" << endl;
    return item;
}

// SETTERS
void BankAccount::setLockBox(string item) {
    box.push_back(item);
}

bool BankAccount::checkValidAmount(double amount) {
    return amount >= 0 ? true : false;
}

// Checkings Class
Checkings::Checkings(string username, string password) : BankAccount(username, password) {
    accountType = "Checkings";
    overdraftFee = 50.0;
}

Checkings::Checkings(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2) :
BankAccount(username, password, fullName, birthday, question1, answer1, question2, answer2) {
    accountType = "Checkings";
    overdraftFee = 50.0;
}

//	CONSTRUCTOR
Savings::Savings(string username, string password) : BankAccount(username, password) {
    accountType = "Savings";
}

Savings::Savings(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2) :
BankAccount(username, password, fullName, birthday, question1, answer1, question2, answer2) {
    accountType = "Savings";
}

//	CONSTRUCTOR
CreditCard::CreditCard(string username, string password) : Account(username, password) {
    accountType = "CreditCard";
    balance = 0;
    accountsBalances.push_back(&balance);
}

CreditCard::CreditCard(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2, int creditscore) :
Account(username, password, fullName, birthday, question1, answer1, question2, answer2) {
    accountType = "CreditCard";
    balance = 0;
    creditMinimum = 50;
    this->creditscore = creditscore;
    accountsBalances.push_back(&balance);
}

double CreditCard::getBalance() {
    return balance;
}

double CreditCard::getCreditMinimum() {
    return creditMinimum;
}

void  CreditCard::setCreditMinimum(double amount) {
    this->creditMinimum = amount;
}

void CreditCard::creditPayment(double amount) {
    balance -= amount;
}
void CreditCard::setCreditscore(int creditscore) {
    this->creditscore = creditscore;
}
int CreditCard::getCreditscore() {
    return creditscore;
}
void Account::SetQuestion1(string quest) {
    question1 = quest;//maybe want pre set questions
}
void Account::SetQuestion2(string quest) {
    question2 = quest;//same thing as above
}
void Account::SetAnswer1(string ans) {
    answer1 = ans;
}
void Account::SetAnswer2(string ans) {
    answer2 = ans;
}
void Account::setcScore(int score) {
    creditscore = score;
}
int Account::getcScore() {
    return creditscore;
}
float Account::calculatePaypercent(int score) {
    float paypercent;
    if (score >= 300 && score < 400) {
        paypercent = 0.35;
    }
    else if (score >= 400 && score < 500) {
        paypercent = 0.25;
    }
    else if (score >= 500 && score < 600) {
        paypercent = 0.15;
    }
    else if (score >= 600 && score < 700) {
        paypercent = 0.10;
    }
    else if (score >= 700 && score < 850) {
        paypercent = 0;
    }
    else if (score >= 850 || score < 300) {
        cout << "This credit score is unobtainable" << endl;//maybe
        paypercent = -1;
    }
    return paypercent;
}
void Account::setBill(double total) {
    Creditbill = total;
}
double Account::Calculatepayment(float percent) {
    double payment = 0;
    cout << Creditbill << endl;
    cout << percent << endl;
    payment += Creditbill + Creditbill*percent;
    return payment;
}
void Account::forgotUsername() {
    string temp = "";
    int numattempts = 0;
    cout << "Type your password or type 1 to access your security questions" << endl;
    while (1) {
        getline(cin, temp);
        if (temp == "1") {
            if (AnswerQuestions()) {
                cout << "Your username: " << username << endl;
                break;
            }
            else {
                cout << "You can press 1 to retry or try your password" << endl;
                continue;
            }
        }
        else if (temp == password) {
            cout << "Your username: " << username << endl;
            break;
        }
        else if (numattempts == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else if (temp != password) {
            cout << "Your Password is wrong" << endl;
            numattempts++;
            continue;
        }
    }
}
void Account::forgotPass() {
    string temp = "";
    int numattempts = 0;
    cout << "Type your username or type 1 to access your security questions" << endl;
    while (1) {
        getline(cin, temp);
        if (temp == "1") {
            if (AnswerQuestions()) {
                cout << "Your password: " << password << endl;
                break;
            }
            else {
                cout << "You can press 1 to retry or try your username" << endl;
                continue;
            }
        }
        else if (temp == username) {
            cout << "Your password: " << password << endl;
            break;
        }
        else if (numattempts == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else if (temp != username) {
            cout << "Your username is wrong" << endl;
            numattempts++;
            continue;
        }
    }
}
bool Account::AnswerQuestions() {
    string tempans = "";
    int numcorrect = 0;
    int numwrong1 = 0;
    int numwrong2 = 0;
    while (1) {
        cout << question1 << endl;
        getline(cin, tempans);
        if (tempans == "1") {
            cout << "Exiting" << endl;
            break;
        }
        else if (tempans == answer1) {
            tempans = "";
            numcorrect++;
            break;
        }
        else if (numwrong1 == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else {
            cout << "Sorry does not match answer for question" << endl;
            numwrong1++;
            continue;
        }
    }
    while (numcorrect == 1 && numwrong1 != 3) {
        cout << question2 << endl;
        cin >> tempans;
        if (tempans == "1") {
            cout << "Exiting" << endl;
            break;
        }
        else if (numwrong2 == 3) {
            cout << "You have exceeded the max number of attempts" << endl;
            break;
        }
        else if (tempans == answer2) {
            tempans = "";
            numcorrect++;
            break;
        }
        else {
            cout << "Sorry does not match answer for question" << endl;
            numwrong2++;
            continue;
        }
    }
    if (numcorrect == 2) {
        return true;
    }
    else {
        return false;
    }
}
/*void Account:: SetBirth(){
 int temp=0;
 while(1){
 cout<<"what year were you born"<<endl;
 cin>>temp;
 if(cin.fail()){
 cout<<"must be a integer"<<endl;
 continue;
 }
 else if(temp>2003||temp<1900){
 cout<<"need to be alive and over 13 years old"<<endl;
 continue;
 }
 else{
 year=temp;
 break;
 }
 <<<<<<< HEAD
 //could implement leap year but may be not really necessary
 }
 while(1){
 cout<<"what month were you born"<<endl;
 cin>>temp;
 if(cin.fail()){
 cout<<"must be an integer"<<endl;
 continue;
 }
 else if(temp<1||temp>12){
 cout<<"must enter a valid month"<<endl;
 continue;
 }
 else{
 month=temp;
 break;
 }
 }
 while(1){
 cout<<"what day were you born"<<endl;
 cin>>temp;
 if(cin.fail()){
 cout<<"must be an integer"<<endl;
 continue;
 }
 else{
 day=temp;
 break;
 }
 // between days in specific month
 //still need to add
 }
 }
 string Account:: getBirthday(){
 stringstream sstm;
 sstm <<month<<"/"<<day<<"/"<<year;
 birthdate= sstm.str();
 return birthdate;//this stuff is going in user interface
 }*/
