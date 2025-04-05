// Refactored Social Media Feed System using Singleton, Strategy, Factory, and Clean Architecture

#include <bits/stdc++.h>
using namespace std;

// ------------------------------ Models ------------------------------
class Post {
public:
    static int Puid;
    int id;
    string title;
    string body;
    int creatorId;
    int timestamp;

    Post(string title, string body, int userID)
        : id(Puid++), title(title), body(body), creatorId(userID), timestamp(time(0)) {}

    void display() {
        cout << "Title: " << title << ", Body: " << body << ", Creator ID: " << creatorId << ", Timestamp: " << timestamp << endl;
    }
};
int Post::Puid = 1;

class User {
public:
    static int Uuid;
    int id;
    string name;
    string email;
    unordered_set<int> following;
    unordered_set<int> posts;

    User(string email, string name) : id(Uuid++), email(email), name(name) {}
};
int User::Uuid = 1;

// ------------------------------ Factory ------------------------------
class PostFactory {
public:
    static shared_ptr<Post> createPost(const string& title, const string& body, int userID) {
        return make_shared<Post>(title, body, userID);
    }
};

// ------------------------------ Controllers ------------------------------
class UserController {
    unordered_map<int, shared_ptr<User>> users;
    unordered_set<string> emailSet;

    UserController() {}
public:
    static UserController& getInstance() {
        static UserController instance;
        return instance;
    }

    shared_ptr<User> createUser(string email, string name) {
        if (emailSet.count(email)) {
            cout << "User already exists.\n";
            return nullptr;
        }
        shared_ptr<User> user = make_shared<User>(email, name);
        users[user->id] = user;
        emailSet.insert(email);
        return user;
    }

    shared_ptr<User> getUser(int id) {
        return users.count(id) ? users[id] : nullptr;
    }

    bool follow(int uid, int fid) {
        auto u = getUser(uid), f = getUser(fid);
        if (!u || !f) return false;
        u->following.insert(fid);
        return true;
    }
};

class PostController {
    unordered_map<int, shared_ptr<Post>> posts;
    PostController() {}

public:
    static PostController& getInstance() {
        static PostController instance;
        return instance;
    }

    shared_ptr<Post> createPost(const string& title, const string& body, shared_ptr<User> creator) {
        shared_ptr<Post> post = PostFactory::createPost(title, body, creator->id);
        posts[post->id] = post;
        creator->posts.insert(post->id);
        return post;
    }

    shared_ptr<Post> getPost(int pid) {
        return posts.count(pid) ? posts[pid] : nullptr;
    }

    vector<shared_ptr<Post>> getAllPosts() {
        vector<shared_ptr<Post>> all;
        for (auto& [_, p] : posts) all.push_back(p);
        return all;
    }
};

// ------------------------------ Strategy Pattern ------------------------------
class IFeedStrategy {
public:
    virtual vector<shared_ptr<Post>> getFeed(shared_ptr<User> user, int k) = 0;
    virtual ~IFeedStrategy() = default;
};

class RecencyFeedStrategy : public IFeedStrategy {
public:
    vector<shared_ptr<Post>> getFeed(shared_ptr<User> user, int k) override {
        vector<pair<int, shared_ptr<Post>>> postList;
        PostController& postCtrl = PostController::getInstance();

        for (int fid : user->following) {
            auto fUser = UserController::getInstance().getUser(fid);
            if (!fUser) continue;

            for (int pid : fUser->posts) {
                auto post = postCtrl.getPost(pid);
                if (post) postList.push_back({post->timestamp, post});
            }
        }

        sort(postList.rbegin(), postList.rend());
        vector<shared_ptr<Post>> result;
        for (int i = 0; i < min(k, (int)postList.size()); ++i) {
            result.push_back(postList[i].second);
        }
        return result;
    }
};

// ------------------------------ Feed Controller ------------------------------
class FeedController {
    IFeedStrategy* strategy;
public:
    FeedController(IFeedStrategy* strat) : strategy(strat) {}

    void displayFeed(int userId, int k) {
        auto user = UserController::getInstance().getUser(userId);
        if (!user) {
            cout << "User not found.\n";
            return;
        }

        vector<shared_ptr<Post>> feed = strategy->getFeed(user, k);
        for (auto& p : feed) p->display();
    }
};

// ------------------------------ Main ------------------------------
int main() {
    auto& userCtrl = UserController::getInstance();
    auto& postCtrl = PostController::getInstance();

    auto u1 = userCtrl.createUser("alice@example.com", "Alice");
    auto u2 = userCtrl.createUser("bob@example.com", "Bob");
    auto u3 = userCtrl.createUser("carol@example.com", "Carol");

    userCtrl.follow(u1->id, u2->id);
    userCtrl.follow(u1->id, u3->id);

    postCtrl.createPost("Trip", "Had a great trip!", u2);
    postCtrl.createPost("Food", "Delicious burger today.", u3);

    RecencyFeedStrategy strategy;
    FeedController feedCtrl(&strategy);
    feedCtrl.displayFeed(u1->id, 10);

    return 0;
}
