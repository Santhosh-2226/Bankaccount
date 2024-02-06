#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(const string& number, const string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    const string& getAccountNumber() const {
        return accountNumber;
    }

    const string& getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false; // Insufficient funds
    }
};

void saveAccountToFile(const BankAccount& account) {
    ofstream file(account.getAccountNumber() + ".txt");
    file << account.getAccountNumber() << "\n";
    file << account.getAccountHolder() << "\n";
    file << account.getBalance() << "\n";
    file.close();
}

BankAccount loadAccountFromFile(const string& accountNumber) {
    ifstream file(accountNumber + ".txt");
    string number, holder;
    double balance;
    file >> number >> holder >> balance;
    file.close();
    return BankAccount(number, holder, balance);
}

void createAccount() {
    string accountNumber, accountHolder;
    double initialBalance;

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter account holder name: ";
    cin.ignore(); // Consume newline character
    getline(cin, accountHolder);

    cout << "Enter initial balance: ";
    cin >> initialBalance;

    BankAccount newAccount(accountNumber, accountHolder, initialBalance);
    saveAccountToFile(newAccount);
    cout << "Account created successfully.\n";
}

void depositMoney() {
    string accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    BankAccount account = loadAccountFromFile(accountNumber);

    cout << "Enter deposit amount: ";
    cin >> amount;

    account.deposit(amount);
    saveAccountToFile(account);

    cout << "Deposit successful. Updated balance: " << account.getBalance() << "\n";
}

void withdrawMoney() {
    string accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    BankAccount account = loadAccountFromFile(accountNumber);

    cout << "Enter withdrawal amount: ";
    cin >> amount;

    if (account.withdraw(amount)) {
        saveAccountToFile(account);
        cout << "Withdrawal successful. Updated balance: " << account.getBalance() << "\n";
    } else {
        cout << "Insufficient funds.\n";
    }
}

void checkBalance() {
    string accountNumber;

    cout << "Enter account number: ";
    cin >> accountNumber;

    BankAccount account = loadAccountFromFile(accountNumber);

    cout << "Account Holder: " << account.getAccountHolder() << "\n";
    cout << "Current Balance: " << account.getBalance() << "\n";
}

int main() {
    int choice;

    do {
        cout << "\nMain Menu\n";
        cout << "1. Create a new account\n";
        cout << "2. Deposit money\n";
        cout << "3. Withdraw money\n";
        cout << "4. Check balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                cout << "Exiting the program.Thanks for your coming!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}