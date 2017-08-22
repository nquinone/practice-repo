#include <iostream>
#include <vector>

using namespace std;

// Account class
class Account {
private:
    string question1;
    string question2;
    string answer1;
    string answer2;
    int month;
    int day;
    int year;
    int creditscore;
    string fullName;
    double Creditbill;
    string birthday;
    string username;
    string password;
    string state;
    int generateAccountNumber();
protected:
    static vector<int> accountNumbers;
    static vector<double*> accountsBalances;
    string accountType;
    int accountNumber;
    bool checkAccountNumber(int accountNumber);
public:
    virtual ~Account() = 0;
    Account(string username, string password);
    Account(string username, string password, string fullName, string birthdate, string question1, string answer1, string question2, string answer2);
    virtual double getBalance() = 0;
    string getUsername();
    string getPassword();
    void setUsername(string username);
    void setPassword(string password);
    int getAccountNumber();
    string getAccountType();
    void transfer(int fromAccountNumber, int toAccountNumber, double amount);
    string getQuestion1();
    string getQuestion2();
    string getAnswer1();
    string getAnswer2();
    void setfullName(string name);
    void OldPassReset();
    void FailedInput();
    string GetFullName();
    void setState(string state);
    string getState();
    void SetQuestion1(string quest);
    void SetQuestion2(string quest);
    void SetAnswer1(string ans);
    void SetAnswer2(string ans);
    void setBirthday(string birthday);
    string getBirthday();
    void ResetPassQuestions();
    string getPerson();
    void setcScore(int score);
    int getcScore();
    void setBill(double total);
    float calculatePaypercent(int score);
    double Calculatepayment(float percent);
    void forgotPass();
    void forgotUsername();
    bool AnswerQuestions();
};

// BankAccount class
class BankAccount : public Account {
private:
    double balance;
    bool checkValidAmount(double amount);
    vector<string> box;
public:
    virtual ~BankAccount() = 0;
    BankAccount(string username, string password);
    BankAccount(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2);
    void deposit(double amount);
    void deposit(int accountNumber, double amount);
    double withdrawal(double amount);
    double getBalance();
    void setLockBox(string item);
    string getLockBox(string item);
};

// Checkings account class
class Checkings : public BankAccount {
private:
    double overdraftFee;
public:
    Checkings(string username, string password);
    Checkings(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2);
};

//Savings account class
class Savings : public BankAccount {
public:
    Savings(string username, string password);
    Savings(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2);
};

// CreditCard class
class CreditCard : public Account {
private:
    double creditMinimum;
    double balance;
    int creditscore;
public:
    CreditCard(string username, string password);
    CreditCard(string username, string password, string fullName, string birthday, string question1, string answer1, string question2, string answer2, int creditscore);
    double getBalance();
    void creditPayment(double amount);
    double getCreditMinimum();
    void setCreditMinimum(double amount);
    int getCreditscore();
    void setCreditscore(int creditscore);
};
