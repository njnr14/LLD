#include<bits/stdc++.h>
using namespace std;


class User{
    public:
    static int Uuid;
    string email;
    int id;
    string name;
    string password;
    int Location;


    User(string name, string password) : name(name) ,id(Uuid++) , password(password) {};


};

int User::Uuid =1;

enum DriverStatus{
    IDLE,
    NOT_IDLE
};

class Driver{
    public:
    static int Duid;
    int id;
    string email;
    string name;
    string password;
    int  Location;
    DriverStatus Status;
    int rideRequest;



    Driver(string email , string name , string password) : id(Duid++) ,email(email), name(name) , password(password){};


};



class UserManager{
    unordered_map<string , shared_ptr<User>> AllUser;
    
    public:

    void CreateUser(string Email, string Name , string Password ){

        if(AllUser.find(Email)!=AllUser.end()){
            cout<<"User All ready Exists \n";
            return;
        }

        shared_ptr<User> u = make_shared<User>(Email, Name, Password);
       
        AllUser[u->email] = u;


    }
    void updateUserLocation(string Email, string password, int currLocation){
        if(!VerifyUser(Email , password)){
            cout<<"Invalid User \n";
            return;

        }

        shared_ptr<User> u = AllUser[Email];
    }
    shared_ptr<User> getUser(string Email){
        return AllUser[Email];
    };
    bool VerifyUser(string Email, string Password){
        return AllUser[Email]->password  ==  Password;
    };


};


class DriverManager{
    unordered_map<int , shared_ptr<Driver>> AllDriver;
    public:
    void CreateDriver(){}
    void updateDriverLocation(){}
    shared_ptr<Driver> getUser(){};
    vector<shared_ptr<Driver>> getAvailbleDriver(){};
    void UpdateDriverStatus(){}
    bool VerifyDriver(int Id, string password){};


};




enum RideStatus{
    SEARCHING,
    IN_PROGRESS,
    FINISHED
};


class Ride{
    public:
    static int Ruid;
    int id;
    int UserId;
    int DriverId;
    int PickUP;
    int Destination;
    int expectedFare;

    RideStatus Status;


    Ride(int UserId , int PickUp ,int Destination):id(Ruid++) ,UserId(UserId) ,PickUP(PickUP) , Destination(Destination) , expectedFare(abs(PickUP - Destination)), Status(SEARCHING){}
    
};


class RideManager{
    UserManager UserManager;
    DriverManager driverManager;

    unordered_map<int , shared_ptr<Ride>> AllRide;

    void createRide(string Email, string password , int PickUp ,int Destination){

        // verify User
        if(!UserManager.VerifyUser(Email , password)){
            cout<<"Invalid User \n";
        }

        shared_ptr<Ride> ride = make_shared<Ride>(Email, PickUp ,Destination);
        AllRide[ride->id] = ride;

        vector<shared_ptr<Driver>> AvailabeDriver = driverManager.getAvailbleDriver();
        //Need Algo for Nearest Driver


        for(auto it : AvailabeDriver){
            it->rideRequest = ride->id;
        }
    }
};


int main(){
    return 0;

}