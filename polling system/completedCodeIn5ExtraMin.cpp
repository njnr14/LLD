#include<bits/stdc++.h>
using namespace std;


class User{
    public:
    static int Uuid;
    int id ;
    string name;

    User(string name):id(Uuid++) , name(name){}
    User(){}
};

int User::Uuid = 1;

class UserManager{
    private:
    unordered_map<int, User*> AllUser; //(userID -> User)

    public:

    void createUser(string name){
        User *u = new User(name);
        AllUser[u->id] = u;
        return;
    }


    User* getUser(int UserId){
        return AllUser.count(UserId) ? AllUser[UserId] : nullptr;
    }
};

class Option{
    public:
    static int Ouid;
    int id;
    string title;

    Option(string title):id(Ouid++) , title(title) {}
    Option(){}


};
int Option::Ouid =1;

class Poll{
    public:
    static int Puid;
    int id;
    string title;
    Chat* obj;
    User* createdBy;
    unordered_map<int,int> optionsAndVote ; //optionsID -> vote
    unordered_map<int,Option*> Choices ; //optionsID -> Option
    unordered_map<int,int> UserVote ; //UserID -> OptionId



    Poll(string title , User* u):id(Puid++) , title(title) ,createdBy(u) {};
    Poll(){};


    void addOption(string optionTitle){
        Option *option = new  Option(optionTitle);
        optionsAndVote[option->id] = 0;
        Choices[option->id] = option;
    }

    void addVote(User* u , Option* o ){
        if(UserVote.count(u->id)){
            int prevOption = UserVote[u->id]; //previous option
            optionsAndVote[prevOption]--; // deselecting prevOption
            optionsAndVote[o->id]++; // selection new Option
            UserVote[u->id] = o->id; // User -> newOption
        }

        UserVote[u->id] = o->id;
        optionsAndVote[o->id]++;
    }

    void display(){
        cout<<"poll ID:"<<id<<endl;
        cout<<"poll Name:"<<title<<endl;
        cout<<"created By:"<<createdBy->name<<endl;
        cout<<"options"<<endl;

        for(auto it: Choices){
            cout<<it.second->title<<endl;
        }
    }



};

class PollManager{
    public:
    unordered_map<int,Poll*> AllPolls; // pollId -> chat
    int  CreatePoll(string title , User* creater){
        Poll * p = new Poll(title , creater);
        AllPolls[p->id] = p;
        return p->id;

    }

    Poll* getPoll(int PollId){
        return AllPolls[PollId];
    }
};

int Poll::Puid =1;

class Chat{
    public:
    static int Cuid;
    int id;
    string name;
    unordered_map<int , User*> chatGroup; // userID -> user

    Chat(string name){
        this->name  = name;
        id = Cuid++;
    }

    void addUserInChat(User* u){
        chatGroup[u->id] = u;
    }

    
};



int Chat::Cuid = 1;

class ChatManager{
    public:
    unordered_map<int , Chat*> allChatGropus; // chatId , Chat

    void CreateChatGroup(string name){
        Chat *C  = new Chat(name);
        allChatGropus[C->id] = C;
    }

    void addUserInChatGroup(User* u , Chat* C){
        C->addUserInChat(u);
    }

    Chat* getChatGrp(int id){
        return allChatGropus[id];
    }
};


class System{

    private:
    System(){}

    public:
    static System* SysManger;
    static System* getSystem(){
        if(SysManger==nullptr){
            SysManger = new System();
        }

        return SysManger;
    }

    UserManager UserManager;
    ChatManager ChatManager;
    PollManager PollManager;

    void CreateUser(string name){
        UserManager.createUser(name);
    }

    User* getUser(int id){
        return UserManager.getUser(id);
    }

    void createChat(string grpName){
        ChatManager.CreateChatGroup(grpName);
    }

    Chat* getChatGrp(int id){
        return ChatManager.getChatGrp(id) ? ChatManager.getChatGrp(id) : nullptr;
    }

    void createPoll(string title , int createdBy , vector<string> options){
        User *u = getUser(createdBy);
        int PollId = PollManager.CreatePoll(title , u);

        Poll *p = PollManager.getPoll(PollId);

        for(auto it : options){
            p->addOption(it);
        }
    }


    void addVote(int userId , int chatId , int PollId ,int optionId){
        User* u= UserManager.getUser(userId);
        Chat *c= ChatManager.getChatGrp(chatId);
        Poll* p= PollManager.getPoll(PollId);
        Option* o = p->Choices[optionId];

        p->addVote(u,o);
    }

};

System* System::SysManger = nullptr;

int main() {
    System *sys = System::getSystem();

    // Step 1: Create Users
    sys->CreateUser("Alice");
    sys->CreateUser("Bob");
    sys->CreateUser("Charlie");

    // Get users
    User* alice = sys->getUser(1);
    User* bob = sys->getUser(2);
    User* charlie = sys->getUser(3);

    // Step 2: Create a Chat Group
    sys->createChat("Tech Discussion");

    // Get chat group
    Chat* chat = sys->getChatGrp(1);

    // Add users to chat group
    chat->addUserInChat(alice);
    chat->addUserInChat(bob);
    chat->addUserInChat(charlie);

    // Step 3: Create a Poll
    vector<string> options = {"Python", "C++", "JavaScript"};
    sys->createPoll("Which programming language do you prefer?", 1, options); // Alice creates poll

    // Get the poll
    Poll* poll = sys->PollManager.getPoll(1);

    // Step 4: Display Poll Details
    poll->display();

    // Step 5: Users Vote in Poll
    sys->addVote(1, 1, 1, 1); // Alice votes for Python
    sys->addVote(2, 1, 1, 2); // Bob votes for C++
    sys->addVote(3, 1, 1, 1); // Charlie votes for Python

    // Step 6: Display Updated Poll Results
    cout << "\nUpdated Poll Results:\n";
    for (auto it : poll->optionsAndVote) {
        cout << "Option: " << poll->Choices[it.first]->title << " | Votes: " << it.second << endl;
    }

    return 0;
}

