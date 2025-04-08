#include <bits/stdc++.h>
using namespace std;

class User {
public:
    static int Uuid;
    int id;
    string name;

    User(string name) : id(Uuid++), name(name) {}
};

int User::Uuid = 1;

class UserManager {
private:
    unordered_map<int, shared_ptr<User>> AllUser; // (userID -> User)

public:
    void createUser(string name) {
        shared_ptr<User> u = make_shared<User>(name);
        AllUser[u->id] = u;
    }

    shared_ptr<User> getUser(int UserId) {
        return AllUser.count(UserId) ? AllUser[UserId] : nullptr;
    }
};

class Option {
public:
    static int Ouid;
    int id;
    string title;

    Option(string title) : id(Ouid++), title(title) {}
};

int Option::Ouid = 1;

class Poll {
public:
    static int Puid;
    int id;
    string title;
    shared_ptr<User> createdBy;
    unordered_map<int, int> optionsAndVote; // optionsID -> vote
    unordered_map<int, shared_ptr<Option>> Choices; // optionsID -> Option
    unordered_map<int, int> UserVote; // UserID -> OptionId

    Poll(string title, shared_ptr<User> u) : id(Puid++), title(title), createdBy(u) {}

    void addOption(string optionTitle) {
        shared_ptr<Option> option = make_shared<Option>(optionTitle);
        optionsAndVote[option->id] = 0;
        Choices[option->id] = option;
    }

    void addVote(shared_ptr<User> u, shared_ptr<Option> o) {
        if (UserVote.count(u->id)) {
            int prevOption = UserVote[u->id]; // previous option
            optionsAndVote[prevOption]--; // deselecting prevOption
        }

        UserVote[u->id] = o->id;
        optionsAndVote[o->id]++;
    }

    void display() {
        cout << "Poll ID: " << id << endl;
        cout << "Poll Name: " << title << endl;
        cout << "Created By: " << createdBy->name << endl;
        cout << "Options:" << endl;

        for (auto it : Choices) {
            cout << it.second->title << endl;
        }
    }
};

int Poll::Puid = 1;

class PollManager {
public:
    unordered_map<int, shared_ptr<Poll>> AllPolls; // pollId -> Poll

    int CreatePoll(string title, shared_ptr<User> creator) {
        shared_ptr<Poll> p = make_shared<Poll>(title, creator);
        AllPolls[p->id] = p;
        return p->id;
    }

    shared_ptr<Poll> getPoll(int PollId) {
        return AllPolls[PollId];
    }
};

class Chat {
public:
    static int Cuid;
    int id;
    string name;
    unordered_map<int, shared_ptr<User>> chatGroup; // userID -> user

    Chat(string name) : id(Cuid++), name(name) {}

    void addUserInChat(shared_ptr<User> u) {
        chatGroup[u->id] = u;
    }
};

int Chat::Cuid = 1;

class ChatManager {
public:
    unordered_map<int, shared_ptr<Chat>> allChatGroups; // chatId -> Chat

    void CreateChatGroup(string name) {
        shared_ptr<Chat> C = make_shared<Chat>(name);
        allChatGroups[C->id] = C;
    }

    void addUserInChatGroup(shared_ptr<User> u, shared_ptr<Chat> C) {
        C->addUserInChat(u);
    }

    shared_ptr<Chat> getChatGrp(int id) {
        return allChatGroups[id];
    }
};

class System {
private:

System() {}
public:
    static shared_ptr<System> SysManager;
    
    static shared_ptr<System> getSystem() {
        if (!SysManager) {
            SysManager = shared_ptr<System>(new System());
        }
        return SysManager;
    }

    UserManager userManager;
    ChatManager chatManager;
    PollManager pollManager;

    void CreateUser(string name) {
        userManager.createUser(name);
    }

    shared_ptr<User> getUser(int id) {
        return userManager.getUser(id);
    }

    void createChat(string grpName) {
        chatManager.CreateChatGroup(grpName);
    }

    shared_ptr<Chat> getChatGrp(int id) {
        return chatManager.getChatGrp(id);
    }

    void createPoll(string title, int createdBy, vector<string> options) {
        shared_ptr<User> u = getUser(createdBy);
        if (!u) return;

        int PollId = pollManager.CreatePoll(title, u);
        shared_ptr<Poll> p = pollManager.getPoll(PollId);

        for (auto& it : options) {
            p->addOption(it);
        }
    }

    void addVote(int userId, int chatId, int pollId, int optionId) {
        shared_ptr<User> u = getUser(userId);
        shared_ptr<Chat> c = getChatGrp(chatId);
        shared_ptr<Poll> p = pollManager.getPoll(pollId);

        if (!u || !c || !p || p->Choices.find(optionId) == p->Choices.end()) return;

        shared_ptr<Option> o = p->Choices[optionId];
        p->addVote(u, o);
    }
};

shared_ptr<System> System::SysManager = nullptr;

int main() {
    shared_ptr<System> sys = System::getSystem();

    // Step 1: Create Users
    sys->CreateUser("Alice");
    sys->CreateUser("Bob");
    sys->CreateUser("Charlie");

    // Get users
    shared_ptr<User> alice = sys->getUser(1);
    shared_ptr<User> bob = sys->getUser(2);
    shared_ptr<User> charlie = sys->getUser(3);

    // Step 2: Create a Chat Group
    sys->createChat("Tech Discussion");

    // Get chat group
    shared_ptr<Chat> chat = sys->getChatGrp(1);

    // Add users to chat group
    chat->addUserInChat(alice);
    chat->addUserInChat(bob);
    chat->addUserInChat(charlie);

    // Step 3: Create a Poll
    vector<string> options = {"Python", "C++", "JavaScript"};
    sys->createPoll("Which programming language do you prefer?", 1, options); // Alice creates poll

    // Get the poll
    shared_ptr<Poll> poll = sys->pollManager.getPoll(1);

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
