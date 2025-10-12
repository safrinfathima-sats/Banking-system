#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string currentTimeString() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

string formatAmount(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return ss.str();
}

void appendToFile(const string &filename, const string &line) {
    ofstream ofs(filename, ios::app);
    if (ofs.is_open()) {
        ofs << line << "\n";
        ofs.close();
    }
}

int main() {
    double balance = 0.0;
    int choice;
    double amount;
    vector<string> history;
    const string logfile = "transactions.txt";

    cout << "===== Welcome to Smart Banking System =====" << endl;

    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input. Please enter a number (1-5)." << endl;
            continue;
        }

        switch (choice) {
            case 1: { // Deposit
                cout << "Enter amount to deposit: ";
                if (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "❌ Invalid amount entered." << endl;
                    break;
                }
                if (amount > 0) {
                    balance += amount;

                    string entry = currentTimeString() + " | DEPOSIT  | +" + formatAmount(amount) + " | Balance: " + formatAmount(balance);
                    history.push_back(entry);
                    appendToFile(logfile, entry);

                    cout << " Deposit successful! Current Balance = " << formatAmount(balance) << endl;

                    // Motivational message
                    if (amount >= 5000) {
                        cout << " Wow! You're saving a big amount. Keep it up!" << endl;
                    } else {
                        cout << "Great job saving your money! Every bit counts." << endl;
                    }
                } else {
                    cout << " Invalid deposit amount! Must be > 0." << endl;
                }
                break;
            }

            case 2: { // Withdraw
                cout << "Enter amount to withdraw: ";
                if (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Invalid amount entered." << endl;
                    break;
                }

                if (amount > 0 && amount <= balance) {
                    // Warning if withdrawal >= 50% of balance BEFORE withdrawal
                    if (amount >= balance * 0.5) {
                        cout << " Warning: You are withdrawing " << formatAmount(amount)
                             << " which is >= 50% of your current balance (" << formatAmount(balance) << ")." << endl;
                        cout << "Consider keeping a safety buffer for emergencies." << endl;
                    }

                    balance -= amount;
                    string entry = currentTimeString() + " | WITHDRAW | -" + formatAmount(amount) + " | Balance: " + formatAmount(balance);
                    history.push_back(entry);
                    appendToFile(logfile, entry);

                    cout << " Withdrawal successful! Current Balance = " << formatAmount(balance) << endl;
                } else {
                    cout << " Insufficient balance or invalid amount!" << endl;
                }
                break;
            }

            case 3:
                cout << " Your current balance is: " << formatAmount(balance) << endl;
                break;

            case 4: {
                cout << "\n--- Transaction History ---" << endl;
                // If in-memory history is empty, try reading from file (useful after fresh start)
                if (history.empty()) {
                    ifstream ifs(logfile);
                    if (ifs.is_open()) {
                        string line;
                        bool any = false;
                        while (getline(ifs, line)) {
                            cout << line << "\n";
                            any = true;
                        }
                        if (!any) cout << "No transactions found.\n";
                        ifs.close();
                    } else {
                        cout << "No transactions found.\n";
                    }
                } else {
                    for (const auto &h : history) {
                        cout << h << "\n";
                    }
                }
                break;
            }

            case 5:
                cout << " Thank you for using Smart Banking System. Goodbye!" << endl;
                break;

            default:
                cout << " Invalid choice! Please try again (1-5)." << endl;
        }
    } while (choice != 5);

    return 0;
}
