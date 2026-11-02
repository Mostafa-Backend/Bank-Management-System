#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;


int getValidatedInt(const string& prompt, int minVal = numeric_limits<int>::min())
{
int value;
while (true) 
{
cout << prompt;
cin >> value;
if (cin.fail()) 
{
cout << "Error: Invalid input! Please enter a valid number.\n";
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
} 
else if (value < minVal) 
{
cout << "Error: Value must be at least " << minVal << ". Please try again.\n";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
else 
{
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return value;
}
}
}


double getValidatedDouble(const string& prompt, double minVal = -numeric_limits<double>::infinity()) 
{
double value;
while (true) 
{
cout << prompt;
cin >> value;
if (cin.fail()) 
{
cout << "Error: Invalid input! Please enter a valid number.\n";
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
} 
else if (value < minVal) 
{
cout << "Error: Value must be at least " << minVal << ". Please try again.\n";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
else 
{
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return value;
}
}
}


class BankAccount {
private:
 int ID;
 string name;
 double balance;

public:
 BankAccount() : ID(0), name(""), balance(0) {}

 int getID() const { return ID; }
 double getBalance() const { return balance; }


 void CreateAccount(int validID) {
  ID = validID;
  cin.ignore();
  cout << "Input Name: ";
  getline(cin, name);


  balance = getValidatedDouble("Input balance: ", 0.0);
 }

 void Display() const {
  cout << "-------------------Account------------------\n";
  cout << "ID: " << ID << endl;
  cout << "Name: " << name << endl;
  cout << "Balance: " << balance << endl;
  cout << "--------------------------------------------------\n";
 }

 void Deposit(double amount) {
  if (amount > 0) {
   balance += amount;
   cout << "Deposit successful! New Balance: " << balance << endl;
  } else 
   cout << "\nError: Amount must be greater than 0.\n";
  
 }

 void Withdraw(double amount) {
  if (amount <= 0) {
   cout << "\nError: Amount must be greater than 0.\n";
  } else if (amount > balance) {
   cout << "\nError: Insufficient balance!\n";
  } else {
   balance -= amount;
   cout << "Withdrawal successful! New Balance: " << balance << endl;
  }
 }
};

class BankSystem {
private:
 vector<BankAccount> accounts;

public:

 void addAccount() {
  cout << "\n==== Create Account ====\n";
  
  int ID = getValidatedInt("Input ID: ", 1);
  auto it = find_if(accounts.begin(), accounts.end(), [ID](const BankAccount& acc) {
   return acc.getID() == ID;
  });

  if (it != accounts.end()) {
   cout << "Error: Account with ID " << ID << " already exists!\n";
   return;
  }

  
  BankAccount acc;
  acc.CreateAccount(ID);
  accounts.push_back(acc);
  cout << "Account added successfully!\n";
 }

 void displayAll() const {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  cout << "\n=== All Accounts ===\n";
  for (const auto& acc : accounts) {
   acc.Display();
  }
 }

 void SearchAccount() const {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  cout << "\n--- Search by ID ---\n";
  
  
  int targetID = getValidatedInt("Enter Bank ID: ", 1);

  auto it = find_if(accounts.begin(), accounts.end(), [targetID](const BankAccount& acc) {
   return acc.getID() == targetID;
  });

  if (it != accounts.end()) {
   cout << "Account Found:\n";
   it->Display();
  } else {
   cout << "Account not found!\n";
  }
 }

 void DepositMoney() {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  cout << "\n--- Deposit Money ---\n";
  
  int targetID = getValidatedInt("Enter Bank ID: ", 1);

  auto it = find_if(accounts.begin(), accounts.end(), [targetID](const BankAccount& acc) {
   return acc.getID() == targetID;
  });

  if (it != accounts.end()) {
   cout << "Account Found:\n";
   it->Display();
   
   
   double amount = getValidatedDouble("How much do you want to add? ", 0.0001);
   it->Deposit(amount);
  } else 
   cout << "Account not found!\n";
 }

 void WithdrawMoney() {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  cout << "\n--- Withdraw Money ---\n";
  
  int targetID = getValidatedInt("Enter Bank ID: ", 1);

  auto it = find_if(accounts.begin(), accounts.end(), [targetID](const BankAccount& acc) {
   return acc.getID() == targetID;
  });

  if (it != accounts.end()) {
   cout << "Account Found:\n";
   it->Display();
   
   
   double amount = getValidatedDouble("How much do you want to withdraw? ", 0.0001);
   it->Withdraw(amount);
  } else
   cout << "Account not found!\n";
 }

 void DeleteAccount() {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  cout << "\n--- Delete Account ---\n";
  
  int targetID = getValidatedInt("Enter Bank ID to delete: ", 1);

  auto it = find_if(accounts.begin(), accounts.end(), [targetID](const BankAccount& acc) {
   return acc.getID() == targetID;
  });

  if (it != accounts.end()) {
   accounts.erase(it);
   cout << "Account deleted successfully!\n";
  } else 
   cout << "Account not found!\n";
 }

 void RichestAccount() const {
  if (accounts.empty()) {
   cout << "\nNo accounts found!\n";
   return;
  }
  auto it = max_element(accounts.begin(), accounts.end(), [](const BankAccount& a, const BankAccount& b) {
   return a.getBalance() < b.getBalance();
  });

  cout << "\n=== Top Balance Account ===\n";
  it->Display();
 }
};

int main() {
 BankSystem bank;
 int choice = 0;

 while (true) {
  cout << "\n===== Bank Account System =====\n";
  cout << "1. Create Account\n";
  cout << "2. Display All Accounts\n";
  cout << "3. Search Account\n";
  cout << "4. Deposit\n";
  cout << "5. Withdraw\n";
  cout << "6. Delete Account\n";
  cout << "7. Show Richest Account\n";
  cout << "8. Exit\n";
  
 
  choice = getValidatedInt("Enter your choice: ", 1);

  if (choice == 1) bank.addAccount();
  else if (choice == 2) bank.displayAll();
  else if (choice == 3) bank.SearchAccount();
  else if (choice == 4) bank.DepositMoney();
  else if (choice == 5) bank.WithdrawMoney();
  else if (choice == 6) bank.DeleteAccount();
  else if (choice == 7) bank.RichestAccount();
  else if (choice == 8) {
   cout << "Exiting program...\n";
   break;
  } else {
   cout << "Invalid choice! Try again.\n";
  }
 }

 return 0;
}
