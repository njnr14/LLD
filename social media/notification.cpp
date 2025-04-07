#include<bits/stdc++.h>

using namespace std;


class User{
    public:
    void notify(string s){
        cout<<"new notification"<<s<<endl;
    }
};


class NotificationService{
    virtual void sendNotification(unordered_set<shared_ptr<User>> &groupMember,string notification , shared_ptr<User> &sender)  = 0;
    
};

class GroupNotification : public NotificationService{
    public:
    void sendNotification(unordered_set<shared_ptr<User>> &groupMember,string notification , shared_ptr<User> &sender) override{
        for(auto it : groupMember){
            if(it!=sender)it->notify(notification);
        }

    }

} ;


class Group{
    public:
    int id;
    unordered_set<shared_ptr<User>> groupMember;

    Group(int id){
        this->id = id;
    }

    bool addMember(shared_ptr<User> &u){
        if(groupMember.find(u)==groupMember.end())return false; 
        groupMember.insert(u);
        return true;
    }

    bool removeMember(shared_ptr<User> &u){
        if(groupMember.find(u)==groupMember.end())return false;
        groupMember.insert(u);
        return true;
    }

};


class GroupService{
    unordered_map<int , shared_ptr<Group>> AllGroups;
    shared_ptr<GroupNotification> notification;
    public:
    void CreateGroup(){}
    bool addMemberInGroup(){}
    bool RemoveMemberFromGroup(){}
    void sendMessage(string &s ,shared_ptr<User>&u , int id){
        //input validation

        //send message in chat

        //send Notification
        string newNotification ="new Message in the group";
        notification->sendNotification(AllGroups[id]->groupMember , newNotification , u);
    }
};





int main(){
    return 0;

}