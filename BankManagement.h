#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <stdexcept>

using namespace std;


class NegativeDepositException : public exception {
    string negative_deposit_str;
    public:
        NegativeDepositException(const char *message): negative_deposit_str(message) {}
        const char* what() const throw() {
            return negative_deposit_str.c_str();
        }
};

class OverdrawException : public exception {
    string overdraw_str;
    public:
        OverdrawException(const char *message): overdraw_str(message) {}
        const char *what() const throw() {
            return overdraw_str.c_str();
        }
};

class InvalidAccountOperationException : public exception {
    string invalid_account_str;
    public:
        InvalidAccountOperationException(const char *message): invalid_account_str(message) {}
        const char *what() const throw() {
            return invalid_account_str.c_str();
        }
};

class BankAccount {
    string accountNumber;
    double balance;
    bool isActive = true;
    
    public:
        BankAccount(string s, double b): accountNumber(s), balance(b) {}
        void deposit(double amount) {
            try {
                if (!isActive) {
                    throw InvalidAccountOperationException("Error, account has been closed.");
                }
                if(amount < 0) {
                    throw OverdrawException("Error, negative input");
                }    
                balance += amount;
            }
            catch(OverdrawException &e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        void withdraw(double amount) {
            try {
                if (!isActive) {
                    throw InvalidAccountOperationException("Error, account has been closed.");
                }
                if(amount >= balance) {
                    throw NegativeDepositException("Error, cannot overdraw");
                }
                balance -= amount;
            }
            catch(NegativeDepositException &e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        double getBalance() const { return balance; }
        void closeAccount() {
            isActive = false;
        }
};

