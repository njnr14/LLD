#include <bits/stdc++.h>
using namespace std;

enum SplitType { EQUAL, PERCENTAGE, FIXED };

class User {
private:
    static int Uuid;
    int id;
    double balance;
    string name;

public:
    User() {}
    User(string name) {
        this->id = Uuid++;
        this->name = name;
        balance = 0;
    }

    int getUserId() const { return id; }
    double getBalance() const { return balance; }
    
    void setBalance(double n) { balance += n; }

    void DisplayUser() const {
        cout << "ID: " << id << "\nName: " << name << "\nBalance: " << balance << "\n\n";
    }
};
int User::Uuid = 1;

class Expense {
private:
    static int Euid;
    int id;
    string title;
    double amount;
    unordered_set<int> users; // Stores user IDs

public:
    Expense() {}

    Expense(string title, double amount, vector<pair<User*, double>>& groupMember, SplitType type) {
        this->id = Euid++;
        this->title = title;
        this->amount = amount;

        if (type == PERCENTAGE) {
            for (auto& it : groupMember) {
                User* u = it.first;
                users.insert(u->getUserId());
                double split = amount * (it.second / 100) * (-1);
                u->setBalance(split);
            }
        } else if (type == EQUAL) {
            double split = (-1) * (amount / groupMember.size());
            for (auto& it : groupMember) {
                User* u = it.first;
                users.insert(u->getUserId());
                u->setBalance(split);
            }
        } else if (type == FIXED) {
            for (auto& it : groupMember) {
                User* u = it.first;
                users.insert(u->getUserId());
                u->setBalance((-1) * it.second);
            }
        }
    }

    int getExpenseId() const { return id; }

    void displayExpense() const {
        cout << "Expense ID: " << id << "\nTitle: " << title << "\nAmount: " << amount << "\nUsers Involved: ";
        for (auto it : users) cout << it << " ";
        cout << "\n\n";
    }
};
int Expense::Euid = 1;

class BillShare {
private:
    unordered_map<int, Expense> AllExpenses;
    unordered_map<int, User> AllUser;

public:
    void CreateUser(string name) {
        User u(name);
        AllUser[u.getUserId()] = u;
        cout << "✅ User Created: ";
        u.DisplayUser();
    }

    bool createExpense(string title, double amount, vector<pair<int, double>>& groupMember, SplitType type) {
        vector<pair<User*, double>> UserGroup = getUserGroup(groupMember);
        Expense E(title, amount, UserGroup, type);
        AllExpenses[E.getExpenseId()] = E;
        E.displayExpense();
        return true;
    }

    bool createExpense(string title, double amount, vector<pair<int, double>>& groupMember, SplitType type, pair<int, int>& userPaid) {
        vector<pair<User*, double>> UserGroup = getUserGroup(groupMember);

        if (AllUser.find(userPaid.first) == AllUser.end()) {
            cout << "❌ User who paid not found.\n";
            return false;
        }

        User* u = &AllUser[userPaid.first];
        u->setBalance(userPaid.second);

        Expense E(title, amount, UserGroup, type);
        AllExpenses[E.getExpenseId()] = E;
        E.displayExpense();
        return true;
    }

    void checkBalance(int userId) {
        if (AllUser.find(userId) == AllUser.end()) {
            cout << "❌ User not found.\n";
            return;
        }
        AllUser[userId].DisplayUser();
    }

    vector<pair<User*, double>> getUserGroup(vector<pair<int, double>>& groupMember) {
        vector<pair<User*, double>> temp;
        for (auto& it : groupMember) {
            if (AllUser.find(it.first) == AllUser.end()) {
                cout << "❌ User " << it.first << " not found.\n";
                continue;
            }
            temp.push_back({&AllUser[it.first], it.second});
        }
        return temp;
    }
};

int main() {
    BillShare App;

    App.CreateUser("Ram");
    App.CreateUser("Sham");

    vector<pair<int, double>> expense = {{1, 0}, {2, 0}};
    App.createExpense("Lunch", 1000, expense, EQUAL);

    App.checkBalance(1);
    App.checkBalance(2);

    return 0;
}
