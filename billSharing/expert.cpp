#include <bits/stdc++.h>
using namespace std;

// ENUM for Split Type
enum SplitType {
    EQUAL,
    PERCENTAGE,
    FIXED
};

// ---------- USER CLASS ----------
class User {
private:
    static int Uuid;
    int id;
    string name;
    unordered_map<int, double> balances; // {userId -> amount owed}

public:
    User(string name) {
        this->id = Uuid++;
        this->name = name;
    }

    int getUserId() const { return id; }
    string getName() const { return name; }

    void updateBalance(int userId, double amount) {
        balances[userId] += amount;
    }

    void displayUser() const {
        cout << "User ID: " << id << " | Name: " << name << endl;
        cout << "Balances:\n";
        for (auto &entry : balances) {
            cout << "Owes User " << entry.first << " : " << entry.second << endl;
        }
        cout << "--------------------------------\n";
    }
};
int User::Uuid = 1;

// ---------- USER MANAGER ----------
class UserManager {
private:
    unordered_map<int, User*> users;

public:
    User* createUser(string name) {
        User* user = new User(name);
        users[user->getUserId()] = user;
        return user;
    }

    User* getUser(int userId) {
        return users.count(userId) ? users[userId] : nullptr;
    }

    void displayUser(int userId) {
        if (users.count(userId)) users[userId]->displayUser();
        else cout << "❌ User not found.\n";
    }
};

// ---------- SPLIT STRATEGY PATTERN ----------
class SplitStrategy {
public:
    virtual unordered_map<User*, double> calculateSplit(vector<User*> participants, double amount, vector<double> ratios) = 0;
};

class EqualSplit : public SplitStrategy {
public:
    unordered_map<User*, double> calculateSplit(vector<User*> participants, double amount, vector<double>) override {
        unordered_map<User*, double> split;
        double perHead = amount / participants.size();
        for (auto user : participants) split[user] = perHead;
        return split;
    }
};

class PercentageSplit : public SplitStrategy {
public:
    unordered_map<User*, double> calculateSplit(vector<User*> participants, double amount, vector<double> ratios) override {
        unordered_map<User*, double> split;
        for (size_t i = 0; i < participants.size(); i++) split[participants[i]] = amount * (ratios[i] / 100);
        return split;
    }
};

class FixedSplit : public SplitStrategy {
public:
    unordered_map<User*, double> calculateSplit(vector<User*> participants, double amount, vector<double> ratios) override {
        unordered_map<User*, double> split;
        for (size_t i = 0; i < participants.size(); i++) split[participants[i]] = ratios[i];
        return split;
    }
};

// ---------- EXPENSE CLASS ----------
class Expense {
private:
    static int Euid;
    int id;
    string title;
    double amount;
    User* paidBy;
    unordered_map<User*, double> share; // Who owes how much

public:
    Expense(string title, double amount, User* paidBy, vector<User*> participants, SplitStrategy* strategy, vector<double> ratios)
        : title(title), amount(amount), paidBy(paidBy) {
        this->id = Euid++;
        share = strategy->calculateSplit(participants, amount, ratios);

        for (auto &entry : share) {
            if (entry.first != paidBy) {
                entry.first->updateBalance(paidBy->getUserId(), entry.second);
                paidBy->updateBalance(entry.first->getUserId(), -entry.second);
            }
        }
    }

    void displayExpense() const {
        cout << "Expense ID: " << id << " | " << title << " | Amount: " << amount << endl;
        cout << "Paid By: " << paidBy->getName() << endl;
        cout << "Splits: \n";
        for (auto &entry : share) {
            cout << entry.first->getName() << " owes " << entry.second << endl;
        }
        cout << "--------------------------------\n";
    }
};
int Expense::Euid = 1;

// ---------- BILL SHARE SERVICE ----------
class BillShareService {
private:
    UserManager userManager;
    vector<Expense*> expenses;

public:
    void createUser(string name) {
        userManager.createUser(name);
    }

    void createExpense(string title, double amount, int paidById, vector<int> participantIds, SplitStrategy* strategy, vector<double> ratios) {
        User* paidBy = userManager.getUser(paidById);
        if (!paidBy) {
            cout << "❌ Paying user not found.\n";
            return;
        }

        vector<User*> participants;
        for (int userId : participantIds) {
            User* user = userManager.getUser(userId);
            if (!user) {
                cout << "❌ User " << userId << " not found.\n";
                return;
            }
            participants.push_back(user);
        }

        Expense* expense = new Expense(title, amount, paidBy, participants, strategy, ratios);
        expenses.push_back(expense);
        expense->displayExpense();
    }

    void checkBalance(int userId) {
        userManager.displayUser(userId);
    }
};

// ---------- MAIN FUNCTION ----------
int main() {
    BillShareService app;

    // Creating users
    app.createUser("Alice");
    app.createUser("Bob");
    app.createUser("Charlie");

    vector<int> participants = {1, 2, 3};
    EqualSplit equalSplit;
    PercentageSplit percentageSplit;
    FixedSplit fixedSplit;

    cout << "\n💰 Equal Split Example:\n";
    app.createExpense("Lunch", 1200, 1, participants, &equalSplit, {});

    cout << "\n💰 Percentage Split Example:\n";
    app.createExpense("Dinner", 1500, 2, participants, &percentageSplit, {50, 30, 20});

    cout << "\n💰 Fixed Split Example:\n";
    app.createExpense("Trip", 3000, 3, participants, &fixedSplit, {1200, 1000, 800});

    cout << "\n🔍 Checking Balances:\n";
    app.checkBalance(1);
    app.checkBalance(2);
    app.checkBalance(3);

    return 0;
}
