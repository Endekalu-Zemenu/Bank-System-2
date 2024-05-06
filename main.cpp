#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User {
    string name;
    int accountNumber;
    int accountPass;
}


struct Account {
    int accountNumber;
    double balance;
};

struct Transaction {
    int accountNumber;
    double deposit;
    double withdraw;
    double balance;
};

void display(Account &currentAccount, User &currentUser);
void addClients();

void addClients() {
    fstream file;
    fstream file2;
    file.open("clients.txt", ios::app);
    file2.open("transaction.txt", ios::out);

    User newUser;
    Account newAccount;
    Transaction transaction1;

    cout << "Enter your name: ";
    cin >> newUser.name;
    file << newUser.name << " ";

    cout << "Enter new account number: ";
    cin >> newUser.accountNumber;
    file << newUser.accountNumber << " ";
    transaction1.accountNumber = newUser.accountNumber;
    file2 << "New account number: " << transaction1.accountNumber << "\t";

    cout << "Enter new pin: ";
    cin >> newUser.accountPass;
    file << newUser.accountPass << " ";

    cout << "Enter initial balance: $";
    cin >> newAccount.balance;
    newAccount.accountNumber = newUser.accountNumber;
    file << newAccount.balance << endl;
    transaction1.balance = newAccount.balance;
    file2 << "INitial balance: " << transaction1.balance << endl;

    cout << endl;
    cout << "Account Created Successfully!!" << endl;
    cout << endl;

    file.close();
    file2.close();
}

int main() {
    fstream file;
    int acc, pass, choice;

    Account currentAccount;
    User currentUser; // Variable to store data of the current user being checked

    // Open the file in read mode
    file.open("clients.txt", ios::in);

    // Read data from the file
    while (file >> currentUser.name >> currentUser.accountNumber >> currentUser.accountPass >> currentAccount.balance);

    // Close the file
    file.close();

    bool loggedIn = false; // Track login status

    do {
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                if (loggedIn) {
                    cout << "You are already logged in. Please logout first." << endl;
                    break;
                }

                cout << "Enter your account number: ";
                cin >> acc;
                cout << "Enter your password: ";
                cin >> pass;

                // Open the file in read mode
                file.open("clients.txt", ios::in);

                // Read data from the file
                while (file >> currentUser.name >> currentUser.accountNumber >> currentUser.accountPass >> currentAccount.balance) {
                    if((acc == currentUser.accountNumber) && (pass == currentUser.accountPass)) {
                        loggedIn = true; // Mark as logged in
                        display(currentAccount, currentUser);
                        break;
                    }
                }

                // Close the file
                file.close();

                if (!loggedIn) {
                    cout << "Incorrect password or account number." << endl;
                }
                break;
            case 2:
                addClients();
                break;
            case 3:
                cout << "Thank you for choosing our service." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    } while(choice != 3);

    return 0;
}

void display(Account &currentAccount, User &currentUser) {
    int choice;
    fstream file;
    fstream file2;
    file2.open("transaction.txt", ios::app);

    Transaction transaction1;

    do {
        cout << "1. Check balance" << endl;
        cout << "2. Deposit money" << endl;
        cout << "3. Withdraw money" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Your current balance is: $" << currentAccount.balance << endl;
                break;
            case 2:
                cout << "Enter your deposit amount: $";
                double depositAmount;
                cin >> depositAmount;
                currentAccount.balance += depositAmount; // Update balance directly for simplicity
                cout << "Deposit successful. Your new balance is: $" << currentAccount.balance << endl;
                transaction1.deposit = depositAmount;
                transaction1.balance = currentAccount.balance;
                file2 << "Deposit: " << transaction1.deposit << "\t"  << "Current balance: " << transaction1.balance << endl;
                break;
            case 3:
                cout << "Enter withdraw amount: ";
                double withdrawAmount;
                cin >> withdrawAmount;
                if(withdrawAmount > currentAccount.balance) {
                    cout << "Withdraw failed. Insufficient funds." << endl;
                } else {
                    currentAccount.balance -= withdrawAmount; // Update balance directly for simplicity
                    cout << "Withdrawal successful. Your new balance is: $" << currentAccount.balance << endl;
                    transaction1.withdraw = withdrawAmount;
                    transaction1.balance = currentAccount.balance;
                    file2 << "Withdraw: " << transaction1.withdraw << "\t" << "Current balance: " << transaction1.balance << endl; 
                }
                break;
            case 4:
                cout << "Thank you for using our service." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }

        // Update balance in the clients.txt file
        file.open("clients.txt", ios::in);
        ofstream tempFile("temp_clients.txt");

        while (file >> currentUser.name >> currentUser.accountNumber >> currentUser.accountPass) {
            if (currentUser.accountNumber == currentAccount.accountNumber) {
                tempFile << currentUser.name << " " << currentUser.accountNumber << " " << currentUser.accountPass << " " << currentAccount.balance << endl;
            } else {
                tempFile << currentUser.name << " " << currentUser.accountNumber << " " << currentUser.accountPass << " " << currentAccount.balance << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("clients.txt");
        rename("temp_clients.txt", "clients.txt");
    } while(choice != 4);
}




