#include <bits/stdc++.h>
#include <cstddef>
#include <memory>
#include <system_error>
#include <unordered_map>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'ride_booking' function below.
 *
 * The function accepts STRING_ARRAY input_args as parameter.
 */

// cab:
// capacity:
// available:



// search ride:
// book ride:


// ride:
// cab:
// start:
// end:


// management:



class Cab{
    public:
    static double Cuid;
    double id;
    double totalCapacity;
    double Occupied;
    double curLong;
    double curLat;
    bool isAvailable;
    
    
    Cab(double totalCapacity , double curLat , double curLong): id(Cuid++) , totalCapacity(totalCapacity)  , Occupied(0), curLong(curLong) , curLat(curLat) ,isAvailable(true){}
    
    
};



double Cab::Cuid = 1;


class Ride{
    public:
    static double Ruid;
    double id;
    string name;
    double seatOccupied;
    pair<double,double>  start;
    pair<double,double>  Destination;
    shared_ptr<Cab> cab;
    
    
    Ride(string name, double seats , pair<double,double> Source , pair<double,double> destination , shared_ptr<Cab> cab): id(Ruid++) ,name(name), seatOccupied(seats) , start(Source) , Destination(destination) ,
    cab(cab){}
    
    
};


double Ride::Ruid = 1;

class CabManager{
    
    public:
    unordered_map<double , shared_ptr<Cab> > AllCab;
    
    void createCab(double totalCapacity , double curLat , double curLong){
        shared_ptr<Cab> c = make_shared<Cab>(totalCapacity , curLat , curLong);
        AllCab[c->id] = c;
        
    }
    
    vector<shared_ptr<Cab>> searchCab(double Lat , double Long){
        vector<shared_ptr<Cab>> ans;
        
        for(auto it : AllCab){
            shared_ptr<Cab> c=  it.second;
            double dest = getDistance(c , Lat , Long);
            if(c->isAvailable && dest <=5 ){
                ans.push_back(c);
            }
        }
        
        return ans;
    }
    
    double getDistance(shared_ptr<Cab> c , double Lat , double Long){
        double dest = sqrt(((Lat - c->curLat)*(Lat - c->curLat)) + ((Long - c->curLong)*(Long - c-> curLong))) * 111;
        
        return dest;
    }
    
    void updateStatus(shared_ptr<Cab> c , bool status){
        
        if(c==nullptr)return;
        c->isAvailable = status;
    }
    
};


class RideManager{
    
    unordered_map<double, shared_ptr<Ride>> AllRide;
    shared_ptr<CabManager> cabManager;
     
    void createRide(string name, double seats , pair<double,double> Source , pair<double,double> destination){
        
        vector<shared_ptr<Cab>> cabs = cabManager->searchCab(Source.first, Source.second);
        shared_ptr<Cab> c = NULL;
        for(auto it : cabs){
            if(it->totalCapacity - it->Occupied >= 0){
                c = it;
                break;
            }
        }
        if(c==NULL){
            cout<<"no cab available\n";
            return;
        }
        
        shared_ptr<Ride> r = make_shared<Ride>(name,seats,Source ,destination  ,c);
        
        if(seats==c->totalCapacity)cabManager->updateStatus(c, false);
        c->Occupied = seats;
        
        AllRide[r->id] = r;
    }
    
    vector<shared_ptr<Ride>> findRide(pair<double,double> des , double seats){
        vector<shared_ptr<Ride>> ans;
        for(auto it : AllRide){
            if(it.second->Destination == des  && seats <= it.second->cab->totalCapacity -it.second->cab->Occupied){
                ans.push_back(it.second);
            }
        }
        
        return ans;
    }
    
    
    
};
  



void ride_booking(vector<string> input_args) {
    shared_ptr<CabManager>  cabManager;
    shared_ptr<RideManager> rideManager;
    
    string name;
    double seats =0 ;
    double s
}


int main()
{
    string input_args_count_temp;
    getline(cin, input_args_count_temp);

    int input_args_count = stoi(ltrim(rtrim(input_args_count_temp)));

    vector<string> input_args(input_args_count);

    for (int i = 0; i < input_args_count; i++) {
        string input_args_item;
        getline(cin, input_args_item);

        input_args[i] = input_args_item;
    }

    ride_booking(input_args);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}