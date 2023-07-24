#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class BankAccount {

private:
    string accountNumber;
    string accountHolderName;
    double balance;
    string file_name;

public:

    string getCurrentDateTime() {
        time_t now = time(0);
        tm* timeInfo = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }

    BankAccount(string accNumber, string accHolderName, double initialBalance) {
        accountNumber = accNumber;
        accountHolderName = accHolderName;
        balance = initialBalance;

   
        file_name = accountHolderName + " " + accountNumber + ".txt";
        ofstream newAccountFile;
        newAccountFile.open(file_name, ios::app);

        newAccountFile << "Account Creation Time = " << getCurrentDateTime() << endl;
        newAccountFile << "Account Number = " << accountNumber << " ----  ";
        newAccountFile << "Holder Name = " << accountHolderName << " ----  ";
        newAccountFile << "Balance (in PKR) = " << balance << endl;

        newAccountFile.close();
    }

    void displayBalance() {
        file_name = accountHolderName + " " + accountNumber + ".txt";

        ifstream account;
        account.open(file_name);

        string data;

        while (getline(account, data)) {
            cout << data << endl;
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance = " << balance << endl;

            file_name = accountHolderName + " " + accountNumber + ".txt";
            ofstream account;
            account.open(file_name, ios::app);
      
            account << endl << endl;
            account << "Transaction Time = " << getCurrentDateTime() << endl;
            account << "You deposited an amount of RS " << amount << " in your account" << endl;
            account << "Now your new Balance is (in PKR) = " << balance << endl;
        } 
        
        else {
            cout << "Invalid amount for deposit." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance = " << balance << endl;

            file_name = accountHolderName + " " + accountNumber + ".txt";
            ofstream account;
            account.open(file_name, ios::app);
      
            account << endl << endl;
            account << "Transaction Time: " << getCurrentDateTime() << endl;
            account << "You Withdrawal an amount of RS " << amount << " from your account" << endl;
            account << "Now your new Balance is (in PKR) = " << balance << endl;

        }
        
        else {
            cout << "Insufficient funds or invalid amount for withdrawal." << endl;
        }
    }
};


class ATM {
public:
    void run(BankAccount& account) {
        int option;
        double amount;

        do {
            cout << "\nATM Menu" << endl;
            cout << "1. Display Balance" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Withdraw" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> option;

            switch (option) {
                case 1:
                    account.displayBalance();
                    break;

                case 2:
                    cout << "Enter the Deposit Amount (in PKR) = ";
                    cin >> amount;
                    account.deposit(amount);
                    break;

                case 3:
                    cout << "Enter the Withdrawal Amount (in PKR) = ";
                    cin >> amount;
                    account.withdraw(amount);
                    break;

                case 4:
                    cout << "Thank you for using the ATM. Have a lovely day :)" << endl;
                    break;

                default:
                    cout << "OOPS ! Invalid option. Please try again." << endl;
            }

        } while (option != 4);
    }
};


int main() {
    string accountNumber, accountHolderName, file_name;
    double initialBalance;

    cout << "        Welcome to the ATM Management System" << endl;
    cout<< "             Developed by Talha Khalid \n"<<endl;
    cout << "Please enter your Account Number = ";
    cin >> accountNumber;
    cout << "Please enter your Account Holder Name = ";
    cin.ignore();
    getline(cin, accountHolderName);

    BankAccount account(accountNumber, accountHolderName, 0);
    ATM atm;
    atm.run(account);

    return 0;
}

