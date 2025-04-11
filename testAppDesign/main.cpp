#include<bits/stdc++.h>
using namespace std;

class User{
    public:
    static int Uuid;
    int id;
    string email;
    string password;
    string name;


    User(string email , string name , string password):id(Uuid++) , email(email) , password(password) , name(name){};

};

int User::Uuid =1;


class UserManager{
    
    unordered_map<string , shared_ptr<User>> Alluser;
    
    public:

    bool createUser(string email , string name , string password){
        if(Alluser.find(email)!=Alluser.end()){
            cout<<"User already Exists\n";
            return false;
        }

        shared_ptr<User> u = make_shared<User>(email,name,password);
        Alluser[email] = u;
    }


    bool veriyUser(string email , string password){
        if(Alluser.find(email)==Alluser.end()){
            cout<<"User Do not Exists\n";
            return false;
        }

        shared_ptr<User> u = Alluser[email];
        if(u->password != password){
            return false;
        }
        return true;
    }

    shared_ptr<User> getUser(string email , string password){
        if(!veriyUser(email,password))return nullptr;
        
        return Alluser[email];
    }
   
};


enum AnswerType{
    SINGLE_CHOICE,
    MUTLI_CHOICE,
    FILL_THE_GAP,
    YES_NO
};



class Question{
    public:
    static int Quid;
    int id;
    string question;
    AnswerType type;
    unordered_set<string> options;
    unordered_set<string> answers;
    int score;


    Question(string question , AnswerType type , unordered_set<string> options , unordered_set<string> answer , int score):
            id(Quid++) , type(type), options(options) , answers(answer) , score(score){}
};


int Question::Quid = 1;

class Test{
    public:
    static int Tuid;
    int id;
    string testTitle;
    unordered_map<int , shared_ptr<Question>> testQuestions;
    int testTotalScore;
    

    Test(string title , unordered_map<int,shared_ptr<Question>> testQuestions ) : 
                testTitle(title) , testQuestions(testQuestions) {}

};


class TestManager{
    unordered_map<int , shared_ptr<Test>> AllTest;
    unordered_map<int , vector<pair<int,int>>> TestGivenByUser ; //userid-> {{testId , testScore}} 
    unordered_map<int , vector<pair<int,int>>> AllUserInTest ; //testid-> {{userScore , UserID} ,....}

    public:
    void createTest(string title , unordered_map<int,shared_ptr<Question>> testQuestions ){
        shared_ptr t= make_shared<Test>(title , testQuestions);
        AllTest[t->id] = t;
    }

    bool addQuestionInTest(int TestId , string question , AnswerType type , unordered_set<string> options , unordered_set<string> answer , int score){
        if(AllTest.find(TestId)==AllTest.end()){
            cout<<"Test do not exist\n";
            return false;
        }
        shared_ptr<Test> t = AllTest[TestId];
        shared_ptr<Question> q = make_shared<Question>(question , type,options , answer,score);

        t->testQuestions[q->id] = q;
        t->testTotalScore += score;

        return true;
    }


    void conductTestforUser(string email ,string password , shared_ptr<UserManager> userManager, int TestId){
        if(!userManager->veriyUser(email , password)){
            cout<<"invalid User \n";
            return;
        }
        if(AllTest.find(TestId)==AllTest.end()){
            cout<<"Test do Not Exist\n";
            return;
        }

        shared_ptr<Test> t = AllTest[TestId];
        shared_ptr<User> u = userManager->getUser(email,password);

        conductTest(t,u);

    }

    void conductTest(shared_ptr<Test> t, shared_ptr<User> u){
        int score = 0;

        // algorithm to condut test and calculate total score



        cout<<"Your Test Score is: "<<score<<endl;
        cout<<"Total score of Test:"<<t->testTotalScore<<endl;

        TestGivenByUser[u->id].push_back({t->id, score});
        return ;

    }

    int calculateRank(int userId , int TestId){
        vector<pair<int,int>> test = AllUserInTest[TestId];
        sort(test.rbegin() , test.rend());

        for(int i = 0 ; i < test.size()  ; i++){
            if(test[i].second == userId){
                return i+1;
            }
        }
    }

    void viewTestScore(string email ,string password , shared_ptr<UserManager> userManager ){
        if(!userManager->veriyUser(email,password))return;
        shared_ptr<User> u = userManager->getUser(email,password);
       
        

    }

};

int main(){

    return 0;
}