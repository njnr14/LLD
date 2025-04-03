#include<bits/stdc++.h>
using namespace std;

enum SplitType{
    EQUAL,
    PERCENTAGE,
    FIXED
};



class User{
    private:
    static int Uuid;
    int id;
    double balance;
    vector<int> Groups;
    string name;

    public:
    User(){}
    User(string name){
        this->id = Uuid++;
        this->name = name;
        balance = 0;
    }

    int getUserId(){
        return id;
    }
    int getBalance(){
        return balance;
    }

    void setBalance(double n){
        balance += n;
    }

    void DisplayUser(){}
};

int User::Uuid = 1;

class Expense{
    private:
    static int Euid;
    int id ;
    string title;
    double amount;
    unordered_set<int> users; // user id , user

    public:
    // Expense( string &title, double &amount , vector<User> &groupMember ){

    //     this->id = Euid++;
    //     this->title = title;
    //     this->amount = amount;  
        
    // }
    Expense(){}
    Expense( string title, double amount , vector<pair<User, double>> &groupMember , SplitType type ){

        this->id = Euid++;
        this->title = title;
        this->amount = amount;  
        double split = amount/groupMember.size();
        
        if(type == PERCENTAGE){
            for(auto it : groupMember){
                User &u = it.first;
                users.insert(u.getUserId());
                double split = amount * (it.second/100)*(-1);
                u.setBalance(split);
            }
        }
        if(type == EQUAL){
            double split = (-1)*(amount/groupMember.size());
            for(auto it : groupMember){
                users.insert(it.first.getUserId());
                it.first.setBalance(split);
            }
        }
        
        if(type == FIXED){
            for(auto it : groupMember){
                User &u = it.first;
                users.insert(u.getUserId());
                double split = (-1) * it.second;
                u.setBalance(split);
            }
        }

    }
    int getExpenseId(){
        return id;
    }
    void displayExpense(){}

};

int Expense::Euid = 1;


class BillShare{
    private:
    unordered_map<int,Expense> AllExpenses;
    unordered_map<int,User> AllUser;

    public:

    
    

    bool createExpense(string title, double amount , vector<pair<int, double>> &groupMember , SplitType type ){
        vector<pair<User , double>> UserGroup = getUserGroup(groupMember);

        Expense E(title  ,amount , UserGroup , type);
        AllExpenses[E.getExpenseId()]  = E;
        return true;

    }
    bool createExpense(string title, double amount , vector<pair<int, double>> groupMember , SplitType type , pair<int,int> &userPaid){
        vector<pair<User , double>> UserGroup = getUserGroup(groupMember);
        User u = AllUser[userPaid.first];
        u.setBalance(userPaid.second);
        Expense E(title  ,amount , UserGroup , type);
        AllExpenses[E.getExpenseId()]  = E;
        return true;

    }
    void CreateUser(string name){
        User u(name);
        AllUser[u.getUserId()] = u;
    }
    vector<pair<User, double>> getUserGroup( vector<pair<int, double>> &groupMember){
        vector<pair<User , double>> temp;
        for(auto it : groupMember){
            User u = AllUser[it.first];
            temp.push_back({u,it.second});
        }
        return temp;
    }   
};





int main(){

    BillShare App;

    App.CreateUser("ram");
    App.CreateUser("sham");

    
    vector<pair<int,double>> expense;
    expense.push_back({1,0});
    expense.push_back({2,0});
    App.createExpense("first" , 1000 , expense , EQUAL );

    return 0;
}