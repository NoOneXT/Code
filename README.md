💰 The Smart Savings and Investment Tracker
A command-line application built in C++ to track personal finances — income, expenses, and savings goals.
By: Saksham Smith Sunar

📌 What Does It Do?
This program helps you manage your money by:

Creating a personal user profile
Adding income (salary, gifts, etc.)
Adding expenses (food, transport, etc.)
Setting savings goals and tracking progress
Viewing a full summary of all transactions


🧠 OOP Concepts Used
ConceptHow It's UsedEncapsulationbalance is private — only changed through addIncome() and addExpense()InheritanceIncome and Expense both inherit from the Transaction parent classPolymorphismdisplay() shows [+] for Income and [-] for ExpenseAbstractionUser sees a simple numbered menu — complex logic is hidden inside classes

🗂️ Class Structure
FinanceManager
    └── User
            ├── Transaction (parent)
            │       ├── Income (child)
            │       └── Expense (child)
            └── SavingsGoal

▶️ How to Run
1. Compile the program
g++ smart_savings_tracker.cpp -o tracker
2. Run the program
tracker

Make sure you run these commands in the Terminal tab in VS Code, not the Output panel.


📋 Menu Options
1. Add Income
2. Add Expense
3. Set Savings Goal
4. Save Towards a Goal
5. View Summary
6. Exit

🛠️ Requirements

C++ compiler (g++ / MinGW)
VS Code or any C++ IDE


📁 File
FileDescriptionsmart_savings_tracker.cppMain C++ source code

📚 Made For

School project presentation — demonstrating Object-Oriented Programming (OOP) concepts in C++.
