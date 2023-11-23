#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account{

public: 

    Account(string aN, const std::string& aH, double b) :
        accountNumber(aN),
        accountHolder(aH),
        balance(b) {}

    void displayDetails() const{
        std::cout << "Account Details for Account (ID: " << accountNumber << "):" <<endl;
        std::cout << "   Holder: " << accountHolder << endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << endl;
    }

    void deposit(double amount){
        balance += amount;
    }

    virtual void withdraw(int amount){
        if (amount <= balance){
            balance -= amount;
        } else {
            std::cout << "Insufficient funds to withdraw" << endl; 
        }
    }

    double getBalance() const {
        return balance;
    }

    // friend void operator+(Account& from, Account& to, double amount) {
    //     if (amount <= from.balance) {
    //         from.balance -= amount;
    //         to.balance += amount;
    //         std::cout << "Transfer successful: $" << amount << " transferred\n";
    //     } else {
    //         std::cout << "Transfer failed: Insufficient funds\n";
    //     }
    // }

    friend std::ostream& operator<<(std::ostream& os, const Account& acc) {
        os << "Account Details for Account (ID: " << acc.accountNumber << "):" << std::endl;
        os << "   Holder: " << acc.accountHolder << std::endl;
        os << "   Balance: $" << std::fixed << std::setprecision(2) << acc.balance << std::endl;
        return os;
    }


protected:

    string accountNumber;
    std::string accountHolder;
    double balance;

};

class SavingsAccount : public Account{

public: 
    
    SavingsAccount(string aN, const std::string& aH, double b, double iR) :
        Account(aN, aH, b),
        interestRate(iR) {}
    
    void withdraw(double amount) {
        const double minBalance = 100.0;
        if ((balance - amount) >= minBalance){
            balance -= amount;
        } else {
            std::cout << "Insufficient funds to withdraw" << endl;
        }
    }

    void displayDetails() {
        std::cout << "Account Details for Savings Account (ID: " << Account::accountNumber << "):" << endl;
        std::cout << "   Holder: " << accountHolder << endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << endl;
        std::cout << "   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%" << endl;
    }


private:
    double interestRate;

};

class CurrentAccount : public Account{

public:

    CurrentAccount(string aN, const std::string& aH, double b, double oL) : 
        Account(aN, aH, b),
        overdraftLimit(oL) {}

    void withdraw(double amount){
        if ((balance - amount) >= -overdraftLimit){
            balance -= amount;
        } else {
            std::cout << "Exceeds Overdraft Limit" << endl;
        }
    
    }

    void displayDetails() {
        std::cout << "Account Details for Savings Account (ID: " << Account::accountNumber << "):" << endl;
        std::cout << "   Holder: " << accountHolder << endl;
        std::cout << "   Balance: $" << std::fixed << std::setprecision(2) << balance << endl;
        std::cout << "   Interest Rate: " << std::fixed << std::setprecision(2) << overdraftLimit << endl;
    }
    

private:

    double overdraftLimit;

};



int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    std::cout << "\n" << endl;
    current.displayDetails();
    std::cout << "\n" << endl;

    savings.deposit(500);
    current.withdraw(1000);
    
    std::cout << "Account Details after deposit and withdrawal:" << endl;
    savings.displayDetails();
    std::cout << "\n" << endl;
    current.displayDetails();
    std::cout << "\n" << endl;

    // Transfer 300 from savings to current

    // current = current + savings;

    // std::cout << "After transfer\n:" << endl;
    // savings.displayDetails();
    // std::cout << "\n" << endl;
    // current.displayDetails();
    return 0;
}