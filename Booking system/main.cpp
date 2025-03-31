#include<bits/stdc++.h>

using namespace std;


class User {
    private:
    static int curUserID;
    int uid;
    string userName;
    int bookingId;
    vector<int> bookedSeat;

    public:

    User(string name){
        userName = name;
        uid = curUserID++;
    }

   int getUserId(){
    return uid;
   }

   void myBooking(){
    for(auto it : bookedSeat){
        cout<<"seat no :"<<it<<" \n";
    }
   }

   void updateBooking(vector<int> temp){
        for(auto it : temp){
            bookedSeat.push_back(it);
        }
   }
   
};

int User::curUserID = 1;

class Show{
    private:
    static int curShowId;
    int showId;
    string ShowName;
    

    public:
    Show(){}
    Show(string name ){
        ShowName = name;
        showId = curShowId++;
    }

    int getShowId(){
        return showId;
    }


    string getShowName(){
        return ShowName;
    }
};




class System{
    private:
    Show Movie;
    vector<bool> seats; // occupied seats
    unordered_map<int, vector<int>> reserved_seat; // userId -> { seat inds}


    public:
    System(){

    }
    void generateShow(string name , int capacity){
        Movie = Show(name);
        seats.resize(capacity , false);
    }

    
    
    bool bookSeats(int userId , vector<int> selected_seats){
        bool flag = false; // cheack vacancy;

        for(auto it : selected_seats){
            if(seats[it] || it<0 || it >= seats.size()){
                cout<<"please select vacant seat \n";
                return false;
            }
        }

        for(auto it : selected_seats){
            seats[it] = true;
            reserved_seat[userId].push_back(it);
        }
        return true;
    }

    void VacantSeat(){
        for(int i= 0 ; i < seats.size() ; i++){
            if(!seats[i]){
                cout<<"seat no :" <<i<<endl;
            }
        }
    }

    vector<int> selected(int n){
        vector<int> selectedSeats;
        for(int i = 0 ; i < n ; i++){
            int temp;
            cout<<"enter the seat number: \n";
            cin>>temp;
            selectedSeats.push_back(temp);
        }
        return selectedSeats;
    }

    void Cancel(int userId){
        for(auto it :reserved_seat[userId]){
            seats[it] = false;
        }
    }



};

int Show::curShowId = 1;




int main(){

    System Movie;
    
    Movie.generateShow("fightClub" , 55);

    Movie.VacantSeat();
    
    User u1("adam");
    int n;
    cout<<"enter number of seat to be selected\n";
    
    cin>>n;
    
    vector<int> temp =  Movie.selected(n);
    if(Movie.bookSeats(u1.getUserId() , temp)){
        u1.updateBooking(temp);
    }

    cout<<"vacant Seats:::\n";
    Movie.VacantSeat();
    
    
    Movie.Cancel(u1.getUserId());
    
    
    cout<<"vacant Seats:::\n";
    cout<<"\n\n\n\n";
    Movie.VacantSeat();


    

    return 0;
}