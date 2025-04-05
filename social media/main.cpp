#include<bits/stdc++.h>

using namespace std;


class User{
    public:
    static int Uuid;
    int id;
    string name;
    string email;
    unordered_set<int> Following;
    unordered_set<int> Posts ; // postID , Post

    User(string email , string name):id(Uuid++) , email(email), name(name) {};

};




class UserController{
    unordered_map<int,shared_ptr<User>> Allusers;
    unordered_set<string> userSet;
    public:
    void createUser(string email ,string name){
        if(userSet.find(email)!=userSet.end()){
            cout<<"User already Exist\n";
            return;
        }
        
        shared_ptr<User> u = make_shared<User>(email,name);
        Allusers[u->id] = u;
        userSet.insert(email);
        cout<<"User created \n";
        
    }
    shared_ptr<User> getUser(int id){
        if(Allusers.find(id)==Allusers.end())return nullptr;
        return Allusers[id];
    }
    bool followUser(shared_ptr<User>user , int userIdToFollow){
        if(Allusers.find(userIdToFollow)==Allusers.end() || user==nullptr){
            cout<<"User do not exists\n"<<endl;
            return false;
        }
        user->Following.insert(userIdToFollow);
        return true;
    };
    bool unfollowUser(shared_ptr<User> user , int userIdToUnfollow){
        if(Allusers.find(userIdToUnfollow)==Allusers.end() || user==nullptr){
            cout<<"User do not exists\n"<<endl;
            return false;
        }
        if(user->Following.find(userIdToUnfollow)==user->Following.end()){
            cout<<"User do not follow this user"<<endl;
            return false;
        }

        user->Following.erase(userIdToUnfollow);
    };


};


int cnt = 1;


class Post{
    public:
    static int Puid;
    int id;
    string title;
    string body;
    int creatorId;
    int timestamp;

    Post(string title , string body , int userID ):id(Puid++),title(title) , body(body) , creatorId(userID) , timestamp(cnt++){}
    void displayPost(){
        cout<<"title: "<<title<<endl;
        cout<<"body: "<<body<<endl;
        cout<<"creatorId: "<<creatorId<<endl;
    }

};


class PostController{
    unordered_map<int , shared_ptr<Post>> AllPosts;
    
    
    public:

    void createPost(string title, string body , shared_ptr<User> creator){
        shared_ptr<Post> p = make_shared<Post>(title,body,creator->id);
        AllPosts[p->id] = p;
        creator->Posts.insert(p->id);
        p->displayPost();
    }

    shared_ptr<Post> getPost(int id){
        if(AllPosts.find(id)==AllPosts.end()){
            cout<<"Post doesn't exists\n";
            return nullptr;
        }

        return AllPosts[id];
    }


};



class FeedController{
    PostController postManager;
    UserController userManager;
    public:
    //users -> allpost ->post
    vector<int> getFeed(vector<int> &followingUsers , int k){
        vector<pair<int,int>> AllUsersPost;
        for(auto it:followingUsers){
            shared_ptr<User> u = userManager.getUser(it);
            if(u==nullptr)continue;

            for(auto post : u->Posts){
                shared_ptr<Post> p = postManager.getPost(post);
                if(p==nullptr)continue;
                AllUsersPost.push_back({p->timestamp , p->id});
            }
        }
        sort(AllUsersPost.rbegin(), AllUsersPost.rend());
        vector<int> response;
        for(int i = 0 ; i <min(k,(int)AllUsersPost.size()) ; i++){
            response.push_back(AllUsersPost[i].second);
        }

        return response;
    }


    void viewFeed(vector<int> &feed){
        for(auto it:feed){
            shared_ptr<Post> p = postManager.getPost(it);
            p->displayPost();
        }
    }

};


int main(){
    return 0;
}