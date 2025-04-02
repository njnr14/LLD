#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>  // For smart pointers
using namespace std;

// Enums for Status
enum class PollStatus { ACTIVE, CLOSED };
enum class VoteType { PUBLIC, ANONYMOUS };

// ==============================
//  User Class
// ==============================
class User {
private:
    static int userCounter;
public:
    int id;
    string name;

    User(string name) : id(userCounter++), name(name) {}
};
int User::userCounter = 1;

// ==============================
//  Option Class
// ==============================
class Option {
private:
    static int optionCounter;
public:
    int id;
    string text;

    Option(string text) : id(optionCounter++), text(text) {}
};
int Option::optionCounter = 1;

// ==============================
//  Poll Class
// ==============================
class Poll {
private:
    static int pollCounter;
    unordered_map<int, int> votesPerOption;  // optionID -> voteCount
    unordered_map<int, int> userVotes;       // userID -> optionID
public:
    int id;
    string question;
    vector<Option> options;
    PollStatus status;
    int createdBy;
    VoteType voteType;

    Poll(string question, int creatorId, VoteType voteType)
        : id(pollCounter++), question(question), createdBy(creatorId), status(PollStatus::ACTIVE), voteType(voteType) {}

    void addOption(string optionText) {
        options.emplace_back(optionText);
        votesPerOption[options.back().id] = 0;
    }

    bool vote(int userId, int optionId) {
        if (status == PollStatus::CLOSED) {
            cout << "Poll is closed. Voting not allowed.\n";
            return false;
        }

        if (userVotes.count(userId)) {
            int prevOption = userVotes[userId];
            votesPerOption[prevOption]--;  // Remove old vote
        }

        userVotes[userId] = optionId;
        votesPerOption[optionId]++;
        return true;
    }

    void closePoll() { status = PollStatus::CLOSED; }

    void displayResults() const {
        cout << "Poll: " << question << " (Status: " << (status == PollStatus::ACTIVE ? "Active" : "Closed") << ")\n";
        for (const auto& opt : options) {
            cout << opt.text << " - " << votesPerOption.at(opt.id) << " votes\n";
        }
    }
};
int Poll::pollCounter = 1;

// ==============================
//  Poll Manager (SRP Applied)
// ==============================
class PollManager {
private:
    unordered_map<int, Poll> polls;

public:
    int createPoll(string question, int creatorId, VoteType voteType) {
        Poll poll(question, creatorId, voteType);
        int pollId = poll.id;
        polls[pollId] = move(poll);
        return pollId;
    }

    Poll* getPoll(int pollId) {
        return polls.count(pollId) ? &polls[pollId] : nullptr;
    }

    void closePoll(int pollId) {
        if (polls.count(pollId)) {
            polls[pollId].closePoll();
        }
    }

    void displayResults(int pollId) {
        if (polls.count(pollId)) {
            polls[pollId].displayResults();
        }
    }
};

// ==============================
//  User Manager (SRP Applied)
// ==============================
class UserManager {
private:
    unordered_map<int, User> users;

public:
    int createUser(string name) {
        User user(name);
        int userId = user.id;
        users[userId] = move(user);
        return userId;
    }

    User* getUser(int userId) {
        return users.count(userId) ? &users[userId] : nullptr;
    }
};

// ==============================
//  Chat Class (Manages Polls)
// ==============================
class Chat {
private:
    static int chatCounter;
    unordered_map<int, int> polls;  // pollID -> poll
public:
    int id;
    string name;
    vector<int> userIds;  // Users in the chat

    Chat(string name) : id(chatCounter++), name(name) {}

    void addUser(int userId) { userIds.push_back(userId); }
    void addPoll(int pollId) { polls[pollId] = pollId; }

    void listPolls() {
        cout << "Polls in chat: " << name << "\n";
        for (const auto& pollId : polls) {
            cout << "Poll ID: " << pollId.first << "\n";
        }
    }
};
int Chat::chatCounter = 1;

// ==============================
//  Chat Manager (SRP Applied)
// ==============================
class ChatManager {
private:
    unordered_map<int, Chat> chats;

public:
    int createChat(string name) {
        Chat chat(name);
        int chatId = chat.id;
        chats[chatId] = move(chat);
        return chatId;
    }

    Chat* getChat(int chatId) {
        return chats.count(chatId) ? &chats[chatId] : nullptr;
    }
};

// ==============================
//  System Controller
// ==============================
class PollingSystem {
private:
    UserManager userManager;
    ChatManager chatManager;
    PollManager pollManager;

public:
    int createUser(string name) { return userManager.createUser(name); }
    int createChat(string name) { return chatManager.createChat(name); }
    int createPoll(string question, int creatorId, VoteType voteType) {
        return pollManager.createPoll(question, creatorId, voteType);
    }

    void addVote(int pollId, int userId, int optionId) {
        Poll* poll = pollManager.getPoll(pollId);
        if (poll) {
            poll->vote(userId, optionId);
        }
    }

    void closePoll(int pollId) { pollManager.closePoll(pollId); }
    void displayPollResults(int pollId) { pollManager.displayResults(pollId); }
};

// ==============================
//  MAIN FUNCTION (TESTING)
// ==============================
int main() {
    PollingSystem system;

    int user1 = system.createUser("Alice");
    int user2 = system.createUser("Bob");

    int chat1 = system.createChat("Tech Discussion");

    int poll1 = system.createPoll("Best programming language?", user1, VoteType::PUBLIC);
    system.addVote(poll1, user1, 1);
    system.addVote(poll1, user2, 2);

    system.displayPollResults(poll1);
    system.closePoll(poll1);

    return 0;
}
