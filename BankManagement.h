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
                // If account is inactive, throw an exception
                if (!isActive) {
                    throw InvalidAccountOperationException("Error, account has been closed.");
                }
                // If the amount entered is a negative value, throw an exception
                if(amount < 0) {
                    throw OverdrawException("Error, negative input");
                }    
                balance += amount;
            }
            // Catch the overdraw exception
            catch(OverdrawException &e) {
                cout << "Error: " << e.what() << endl;
            }
            // Catch the invalid account exception
            catch (InvalidAccountOperationException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        void withdraw(double amount) {
            try {
                // If account is inactive, throw an exception
                if (!isActive) {
                    throw InvalidAccountOperationException("Error, account has been closed.");
                }
                // If the amount requested is more than the balance, throw an exception
                if(amount > balance) {
                    throw NegativeDepositException("Error, cannot overdraw");
                }
                balance -= amount;
            }
            // Catch the negative deposit exception
            catch(NegativeDepositException &e) {
                cout << "Error: " << e.what() << endl;
            }
            // Catch the invalid account exception
            catch (InvalidAccountOperationException& e) {
                "Error: " << e.what() << endl;
            }
        }
        // Returns the current balance
        double getBalance() const { return balance; }
        
        // "Closes" the account by setting isActive to false"
        void closeAccount() {
            isActive = false;
        }
};

