#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Transaction {
protected:
    double amount;
    string date;
    string category;

public:
    Transaction(double amt, string dt, string cat) {
        amount = amt;
        date = dt;
        category = cat;
    }

    virtual void display() {
        cout << "  Amount: $" << amount << " | Date: " << date << " | Category: " << category;
    }

    double getAmount() {
        return amount;
    }
};

class Income : public Transaction {
private:
    string source;

public:
    Income(double amt, string dt, string cat, string src)
        : Transaction(amt, dt, cat) {
        source = src;
    }

    void display() override {
        cout << "  [+] INCOME  | Source: " << source;
        Transaction::display();
        cout << endl;
    }
};

class Expense : public Transaction {
private:
    string purpose;

public:
    Expense(double amt, string dt, string cat, string purp)
        : Transaction(amt, dt, cat) {
        purpose = purp;
    }

    void display() override {
        cout << "  [-] EXPENSE | Purpose: " << purpose;
        Transaction::display();
        cout << endl;
    }
};

class SavingsGoal {
private:
    string goalName;
    double targetAmount;
    double savedAmount;

public:
    SavingsGoal(string name, double target) {
        goalName = name;
        targetAmount = target;
        savedAmount = 0;
    }

    void addSavings(double amount) {
        savedAmount += amount;
        cout << "  Saved $" << amount << " towards '" << goalName << "'!" << endl;
    }

    void checkProgress() {
        double remaining = targetAmount - savedAmount;
        double percent = (savedAmount / targetAmount) * 100;

        cout << "  Goal    : " << goalName << endl;
        cout << "  Target  : $" << targetAmount << endl;
        cout << "  Saved   : $" << savedAmount << " (" << percent << "%)" << endl;

        if (savedAmount >= targetAmount) {
            cout << "  *** GOAL REACHED! Congratulations! ***" << endl;
        } else {
            cout << "  Still need: $" << remaining << endl;
        }
    }

    string getName() { return goalName; }
};

class User {
private:
    string name;
    double balance;
    vector<Transaction*> transactions;
    vector<SavingsGoal> goals;

public:
    User(string userName) {
        name = userName;
        balance = 0;
        cout << "\n  Welcome, " << name << "! Account created." << endl;
    }

    ~User() {
        for (Transaction* t : transactions) delete t;
    }

    void addIncome(double amount, string date, string category, string source) {
        if (amount <= 0) { cout << "  Error: Amount must be positive!" << endl; return; }
        balance += amount;
        transactions.push_back(new Income(amount, date, category, source));
        cout << "  Income added! Balance: $" << balance << endl;
    }

    void addExpense(double amount, string date, string category, string purpose) {
        if (amount <= 0) { cout << "  Error: Amount must be positive!" << endl; return; }
        if (amount > balance) { cout << "  Error: Not enough balance! You have $" << balance << endl; return; }
        balance -= amount;
        transactions.push_back(new Expense(amount, date, category, purpose));
        cout << "  Expense recorded! Balance: $" << balance << endl;
    }

    double getBalance() { return balance; }

    void setSavingsGoal(string name, double target) {
        goals.push_back(SavingsGoal(name, target));
        cout << "  Goal '" << name << "' set! Target: $" << target << endl;
    }

    void saveTowardsGoal(int index, double amount) {
        if (index < 0 || index >= (int)goals.size()) { cout << "  Error: Goal not found!" << endl; return; }
        if (amount > balance) { cout << "  Error: Not enough balance!" << endl; return; }
        balance -= amount;
        goals[index].addSavings(amount);
    }

    void viewGoals() {
        if (goals.empty()) { cout << "  No savings goals yet!" << endl; return; }
        cout << "\n  ===== SAVINGS GOALS =====" << endl;
        for (int i = 0; i < (int)goals.size(); i++) {
            cout << "\n  Goal #" << (i + 1) << ":" << endl;
            goals[i].checkProgress();
        }
    }

    void viewSummary() {
        cout << "\n  ==============================" << endl;
        cout << "  SUMMARY FOR: " << name << endl;
        cout << "  ==============================" << endl;

        if (transactions.empty()) {
            cout << "  No transactions yet!" << endl;
        } else {
            cout << "\n  TRANSACTIONS:" << endl;
            for (Transaction* t : transactions) {
                t->display();
            }
        }

        cout << "\n  Current Balance: $" << balance << endl;
        cout << "  ==============================" << endl;
        viewGoals();
    }
};

class FinanceManager {
private:
    User* user;

public:
    FinanceManager() { user = nullptr; }
    ~FinanceManager() { if (user != nullptr) delete user; }

    void createUser() {
        string name;
        cout << "\n  Enter your name: ";
        cin >> name;
        user = new User(name);
    }

    void showMenu() {
        int choice;

        do {
            cout << "\n  =============================" << endl;
            cout << "   SMART SAVINGS TRACKER MENU  " << endl;
            cout << "  =============================" << endl;
            cout << "  1. Add Income" << endl;
            cout << "  2. Add Expense" << endl;
            cout << "  3. Set Savings Goal" << endl;
            cout << "  4. Save Towards a Goal" << endl;
            cout << "  5. View Summary" << endl;
            cout << "  6. Exit" << endl;
            cout << "  Your choice: ";
            cin >> choice;

            if (choice == 1) {
                double amount;
                string date, category, source;
                cout << "  Amount: $"; cin >> amount;
                cout << "  Date (e.g. 2026-01-01): "; cin >> date;
                cout << "  Category (salary/gift/other): "; cin >> category;
                cout << "  Source: "; cin >> source;
                user->addIncome(amount, date, category, source);

            } else if (choice == 2) {
                double amount;
                string date, category, purpose;
                cout << "  Amount: $"; cin >> amount;
                cout << "  Date (e.g. 2025-01-01): "; cin >> date;
                cout << "  Category (food/transport/fun): "; cin >> category;
                cout << "  Purpose: "; cin >> purpose;
                user->addExpense(amount, date, category, purpose);

            } else if (choice == 3) {
                string goalName;
                double target;
                cout << "  Goal name: "; cin >> goalName;
                cout << "  Target amount: $"; cin >> target;
                user->setSavingsGoal(goalName, target);

            } else if (choice == 4) {
                int index;
                double amount;
                user->viewGoals();
                cout << "  Enter goal number: "; cin >> index;
                cout << "  Amount to save: $"; cin >> amount;
                user->saveTowardsGoal(index - 1, amount);

            } else if (choice == 5) {
                user->viewSummary();

            } else if (choice == 6) {
                cout << "\n  Goodbye! Keep saving smart!" << endl;

            } else {
                cout << "  Invalid choice. Try again!" << endl;
            }

        } while (choice != 6);
    }

    void start() {
        cout << "  =============================" << endl;
        cout << "   THE SMART SAVINGS TRACKER   " << endl;
        cout << "  =============================" << endl;
        createUser();
        showMenu();
    }
};

int main() {
    FinanceManager app;
    app.start();
    return 0;
}
