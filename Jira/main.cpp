
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
    unordered_set<Task , TaskHash> tasks;// should have used map everywhere 
    unordered_set<Sprint , SprintHash > sprints;// should have used map everywhere


    User(string name){
        id = UserUid++;
        userName = name; 
    }

    bool createTask(string name , Tasktype type, string des, StatusType status){
        Task t(name , des,type , status);
        
        tasks.insert(t);
        return true;
        
    }
    bool createSprint(string name , string des ){
        Sprint s(name , des);

        sprints.insert(s);
       
        
    }
    
    void displayAlltask(){
        for(auto it : tasks){
            cout<<it.taskName;
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
    Task(){}
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

    void displayTask(){
        cout<<taskName<<endl;
        cout<<id<<endl;
        cout<<description<<endl;
        cout<<type<<endl;
        cout<<status<<endl;
    }
};

int Task::TaskUid =1;


struct TaskHash {
    size_t operator()(const Task &T) const {
        return hash<int>()(T.id);  // Hashing by prodId
    }
    
};


class Sprint{
    public:
    int id;
    string sprintName;
    string description;
    StatusType status;
    unordered_set<Task ,TaskHash> currTasks;// should have used map everywhere
    // unordered_map<Task , vector<User>>  tasks;  for multiple users
    Sprint(){}
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

    bool operator==(Sprint &s){
        return id==s.id;
    }

};


struct SprintHash{
    size_t operator()(Sprint &s){
        return hash<int>()(s.id);
    }
};


int main(){
    
}