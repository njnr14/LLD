#include<bits/stdc++.h>
using namespace std;

enum StatusType{
    Pending,
    Ongoing,
    Completed
};

enum Tasktype{
    Story,
    Feature,
    Bugs
};


class User : private Task , private Sprint{
    public:
    static int UserUid;
    int id;
    string userName;
    unordered_set<Task> tasks;
    vector<Task> sprints;


    User(string name){
        id = UserUid++;
        userName = name; 
    }

    bool createTask(string name , Tasktype type, string des, StatusType status){
        Task t(name ,type, des , status);
        if(t){
        tasks.insert(t);
        return true;
        }
        else{
            cout<<"error in createTask \n";
        }
        
    }
    bool createSprint(string name , string des , StatusType status){
        Sprint s(name , des , status);
        if(s){
        sprints.insert(s);
        return true;
        }
        else{
            cout<<"error in createTask \n";
        }
        
    }
    
    void displaytask(){
        for(auto it : tasks){
            cout<<it<<endl;
        }
    }

    

};

int User::UserUid =1;

class Task{
    public:
    static int TaskUid;
    int id;
    string taskName;
    string description;
    Tasktype type;
    StatusType status;

    bool operator==(Task &obj){
        return id == obj.id;
    }
    Task(string name , string des , Tasktype type , StatusType status){
        taskName = name;
        description =des;
        this->type = type ;
        this->status = status;
    }

    bool updateStatus(Task &t , StatusType curStatus){
        t.status =curStatus;
        return true;
    }
};

int Task::TaskUid =1;


namespace std {
    template <>
    struct hash<Task> {
        size_t operator()(const Task &T) const {
            return hash<int>()(T.id);  // Hashing by prodId
        }
    };
}


class Sprint{
    public:
    int id;
    string sprintName;
    string description;
    StatusType status;
    unordered_set<Task> currTasks;
    // unordered_map<Task , vector<User>>  tasks;

    Sprint(string name , string des){
        sprintName = name;
        description = des;
        status = Pending;
    }
    bool addTask(Task &t){
        this->currTasks.insert(t);
        return true;
    }
    bool updateSprintStatus(Sprint &obj , StatusType currStatus){
        obj.status = currStatus;
        return true;
    }

    bool removeTaskFromSprint(Sprint &s , Task &t){
        if(s.currTasks.find(t)==s.currTasks.end())return false;
        s.currTasks.erase(t);
        return true;

    }

};



int main(){
    return 0;
}



