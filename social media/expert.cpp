#include <bits/stdc++.h>
using namespace std;

// ------------------------ MODELS ------------------------
class Post {
public:
    static int nextId;
    int id;
    int creatorId;
    string caption;
    int timestamp;

    Post(int creatorId, const string& caption, int ts)
        : id(nextId++), creatorId(creatorId), caption(caption), timestamp(ts) {}

    void display() const {
        cout << "Post ID: " << id << ", Creator ID: " << creatorId << ", Caption: " << caption << ", Timestamp: " << timestamp << endl;
    }
};
int Post::nextId = 1;

class User {
public:
    static int nextId;
    int id;
    string name;
    unordered_set<int> following;
    vector<pair<int, int>> myPosts; // {timestamp, postId}

    User(const string& name) : id(nextId++), name(name) {}

    void follow(int otherId) { following.insert(otherId); }
    void unfollow(int otherId) { following.erase(otherId); }
};
int User::nextId = 1;

// ------------------------ CONTROLLERS ------------------------
class UserController {
    unordered_map<int, shared_ptr<User>> users;

public:
    shared_ptr<User> createUser(const string& name) {
        auto user = make_shared<User>(name);
        users[user->id] = user;
        cout << "Created User: ID=" << user->id << ", Name=" << name << endl;
        return user;
    }

    shared_ptr<User> getUser(int id) {
        return users.count(id) ? users[id] : nullptr;
    }
};

class PostController {
    unordered_map<int, shared_ptr<Post>> posts;
    int timestamp = 1;

public:
    shared_ptr<Post> createPost(int userId, const string& caption, UserController& uc) {
        auto post = make_shared<Post>(userId, caption, timestamp++);
        posts[post->id] = post;
        auto user = uc.getUser(userId);
        if (user) user->myPosts.emplace_back(post->timestamp, post->id);
        return post;
    }

    shared_ptr<Post> getPost(int id) {
        return posts.count(id) ? posts[id] : nullptr;
    }
};

class FeedController {
    PostController& postCtrl;
    UserController& userCtrl;

public:
    FeedController(PostController& p, UserController& u) : postCtrl(p), userCtrl(u) {}

    vector<shared_ptr<Post>> getFeed(int userId, int k) {
        auto user = userCtrl.getUser(userId);
        if (!user) return {};

        auto cmp = [](pair<int, shared_ptr<Post>>& a, pair<int, shared_ptr<Post>>& b) {
            return a.first > b.first; // min-heap for recent k posts
        };
        priority_queue<pair<int, shared_ptr<Post>>, vector<pair<int, shared_ptr<Post>>>, decltype(cmp)> pq(cmp);

        for (int followId : user->following) {
            auto followedUser = userCtrl.getUser(followId);
            if (!followedUser) continue;
            for (auto& [ts, pid] : followedUser->myPosts) {
                auto post = postCtrl.getPost(pid);
                if (post) {
                    pq.push({ts, post});
                    if ((int)pq.size() > k) pq.pop();
                }
            }
        }

        vector<shared_ptr<Post>> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// ------------------------ MAIN ------------------------
int main() {
    UserController userController;
    PostController postController;
    FeedController feedController(postController, userController);

    auto u1 = userController.createUser("Alice");
    auto u2 = userController.createUser("Bob");
    auto u3 = userController.createUser("Charlie");

    u1->follow(u2->id);
    u1->follow(u3->id);

    postController.createPost(u2->id, "Post from Bob 1", userController);
    postController.createPost(u3->id, "Post from Charlie 1", userController);
    postController.createPost(u2->id, "Post from Bob 2", userController);
    postController.createPost(u3->id, "Post from Charlie 2", userController);

    cout << "\nFeed for Alice:\n";
    auto feed = feedController.getFeed(u1->id, 10);
    for (auto& post : feed) {
        post->display();
    }

    return 0;
}