#include<bits/stdc++.h>
using namespace std;


enum class StatusType { Pending, Ongoing, Completed };
enum class TaskType { Story, Feature, Bug };

class Task {
    protected:
        static int taskCounter;
        int id;
        string name;
        string description;
        StatusType status;
        TaskType type;
    
    public:
        Task(string name, string description, TaskType type)
            : id(taskCounter++), name(name), description(description), type(type), status(StatusType::Pending) {}
    
        virtual void displayTask() const = 0;  // Polymorphism
    
        void updateStatus(StatusType newStatus) { status = newStatus; }
        int getId() const { return id; }
        StatusType getStatus() const { return status; }
        string getName() const { return name; }
    };

int Task::taskCounter = 1;


class StoryTask : public Task {
        private:
            vector<unique_ptr<Task>> subTasks;
        
        public:
            StoryTask(string name, string description)
                : Task(name, description, TaskType::Story) {}
        
            void addSubTask(unique_ptr<Task> subTask) { subTasks.push_back(move(subTask)); }
        
            void displayTask() const override {
                cout << "Story: " << name << ", Status: " << static_cast<int>(status) << endl;
                for (const auto &subTask : subTasks) {
                    cout << "  - Subtask: ";
                    subTask->displayTask();
                }
            }
        };
        
class FeatureTask : public Task {
        public:
            FeatureTask(string name, string description)
                : Task(name, description, TaskType::Feature) {}
        
            void displayTask() const override {
                cout << "Feature: " << name << ", Status: " << static_cast<int>(status) << endl;
            }
        };
        
class BugTask : public Task {
        public:
            BugTask(string name, string description)
                : Task(name, description, TaskType::Bug) {}
        
            void displayTask() const override {
                cout << "Bug: " << name << ", Status: " << static_cast<int>(status) << endl;
            }
        };

class StoryTask : public Task {
            private:
                vector<unique_ptr<Task>> subTasks;
            
            public:
                StoryTask(string name, string description)
                    : Task(name, description, TaskType::Story) {}
            
                void addSubTask(unique_ptr<Task> subTask) { subTasks.push_back(move(subTask)); }
            
                void displayTask() const override {
                    cout << "Story: " << name << ", Status: " << static_cast<int>(status) << endl;
                    for (const auto &subTask : subTasks) {
                        cout << "  - Subtask: ";
                        subTask->displayTask();
                    }
                }
            };
            
class FeatureTask : public Task {
            public:
                FeatureTask(string name, string description)
                    : Task(name, description, TaskType::Feature) {}
            
                void displayTask() const override {
                    cout << "Feature: " << name << ", Status: " << static_cast<int>(status) << endl;
                }
            };
            
class BugTask : public Task {
public:
    BugTask(string name, string description)
        : Task(name, description, TaskType::Bug) {}

    void displayTask() const override {
        cout << "Bug: " << name << ", Status: " << static_cast<int>(status) << endl;
    }
};
class Sprint {
    private:
        static int sprintCounter;
        int id;
        string name;
        string description;
        unordered_map<int, shared_ptr<Task>> tasks;
    
    public:
        Sprint(string name, string description) : id(sprintCounter++), name(name), description(description) {}
    
        void addTask(shared_ptr<Task> task) { tasks[task->getId()] = task; }
    
        void removeTask(int taskId) { tasks.erase(taskId); }
    
        void displaySprint() const {
            cout << "Sprint: " << name << endl;
            for (const auto &pair : tasks) {
                pair.second->displayTask();
            }
        }
};
    int Sprint::sprintCounter = 1;
class User {
private:
    static int userCounter;
    int id;
    string name;
    unordered_map<int, shared_ptr<Task>> assignedTasks;

public:
    User(string name) : id(userCounter++), name(name) {}

    void assignTask(shared_ptr<Task> task) { assignedTasks[task->getId()] = task; }

    void displayTasks() const {
        cout << "Tasks assigned to " << name << ":" << endl;
        for (const auto &pair : assignedTasks) {
            pair.second->displayTask();
        }
    }
};
int User::userCounter = 1;
class JiraSystem {
            private:
                unordered_map<int, shared_ptr<User>> users;
                unordered_map<int, shared_ptr<Sprint>> sprints;
                unordered_map<int, shared_ptr<Task>> tasks;
            
            public:
                shared_ptr<User> createUser(string name) {
                    auto user = make_shared<User>(name);
                    users[user->getId()] = user;
                    return user;
                }
            
                shared_ptr<Task> createTask(string name, string description, TaskType type) {
                    shared_ptr<Task> task;
                    if (type == TaskType::Story) task = make_shared<StoryTask>(name, description);
                    else if (type == TaskType::Feature) task = make_shared<FeatureTask>(name, description);
                    else task = make_shared<BugTask>(name, description);
            
                    tasks[task->getId()] = task;
                    return task;
                }
            };
                                                            

