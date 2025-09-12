#include <iostream>
using namespace std;

int main() {
    double balance = 0;
    int choice;
    double amount;

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                balance += amount;
                cout << "Deposited successfully!\n";
                break;
            case 2:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if(amount <= balance) {
                    balance -= amount;
                    cout << "Withdrawn successfully!\n";
                } else {
                    cout << "Insufficient balance!\n";
                }
                break;
            case 3:
                cout << "Current balance: " << balance << "\n";
                break;
            case 4:
                cout << "Thank you!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}