#include "BankManagement.h"

int main() {
    try {
        
        double balance;
        
        // Asking user for initial balance
        cout << "Enter initial balance: ";
        cin >> balance;
    
        // Initialization of the BankAccount class
        unique_ptr<BankAccount> account = make_unique<BankAccount>("123456", balance); 

        cout << "Bank Account Created: #" << "123456" << endl;

        cout << "Depositing $1000..." << std::endl;
        account->deposit(1000);

        cout << "Withdrawing $500..." << std::endl;
        account->withdraw(500);

        cout << "Current Balance: $" << account->getBalance() << endl;

        cout << "Attempting to withdraw $600..." << endl;
        // Should trigger overdraw exception
        account->withdraw(600);

        cout << "Attempting to deposit -$50..." << endl;
        // Should trigger negative exception
        account->deposit(-50);

        cout << "Closing Account..." << endl;
        // Closing the account
        account->closeAccount(); 

        cout << "Attempting to deposit..." << endl;
        // Should also trigger an exception
        account->withdraw(600);
    } 
    catch (const std::exception& e) {
        // Catches errors
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}