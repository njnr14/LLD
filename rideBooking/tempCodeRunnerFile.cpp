#include <bits/stdc++.h>
using namespace std;

enum class DriverStatus { AVAILABLE, BUSY };
enum class RideStatus { SEARCHING, IN_PROGRESS, COMPLETED, CANCELLED };

// Unique ID generators (thread-safe)
atomic<int> userIdCounter(1);
atomic<int> driverIdCounter(1);
atomic<int> rideIdCounter(1);

class User {
public:
    int id;
    string email, name, password;
    int location;

    User(string email, string name, string password, int location)
        : id(userIdCounter++), email(email), name(name), password(password), location(location) {}
};

class Driver {
public:
    int id;
    string email, name, password;
    int location;
    DriverStatus status;

    Driver(string email, string name, string password, int location)
        : id(driverIdCounter++), email(email), name(name), password(password), location(location), status(DriverStatus::AVAILABLE) {}
};

class Ride {
public:
    int id, userId, driverId, pickup, drop;
    int estimatedFare;
    RideStatus status;

    Ride(int userId, int pickup, int drop)
        : id(rideIdCounter++), userId(userId), pickup(pickup), drop(drop), estimatedFare(abs(pickup - drop) * 10), status(RideStatus::SEARCHING) {}
};

class UserService {
private:
    unordered_map<string, shared_ptr<User>> users;

public:
    void registerUser(string email, string name, string password, int location) {
        if (users.find(email) != users.end()) {
            cout << "User already exists.\n";
            return;
        }
        users[email] = make_shared<User>(email, name, password, location);
    }

    void updateUserLocation(string email, int newLocation) {
        if (users.find(email) == users.end()) {
            cout << "User not found.\n";
            return;
        }
        users[email]->location = newLocation;
    }

    shared_ptr<User> getUser(string email) {
        return users[email];
    }

    bool verifyUser(string email, string password) {
        return users.count(email) && users[email]->password == password;
    }
};

class DriverService {
private:
    unordered_map<int, shared_ptr<Driver>> drivers;

public:
    void registerDriver(string email, string name, string password, int location) {
        drivers[driverIdCounter] = make_shared<Driver>(email, name, password, location);
    }

    void updateDriverLocation(int driverId, int location) {
        if (drivers.count(driverId)) {
            drivers[driverId]->location = location;
        }
    }

    void updateDriverStatus(int driverId, DriverStatus status) {
        if (drivers.count(driverId)) {
            drivers[driverId]->status = status;
        }
    }

    vector<shared_ptr<Driver>> getAvailableDrivers() {
        vector<shared_ptr<Driver>> available;
        for (auto& [id, driver] : drivers) {
            if (driver->status == DriverStatus::AVAILABLE) available.push_back(driver);
        }
        return available;
    }
};

class RideMatchingService {
public:
    shared_ptr<Driver> findNearestDriver(int userLocation, vector<shared_ptr<Driver>>& availableDrivers) {
        if (availableDrivers.empty()) return nullptr;

        auto compare = [&](shared_ptr<Driver> a, shared_ptr<Driver> b) {
            return abs(a->location - userLocation) > abs(b->location - userLocation);
        };

        priority_queue<shared_ptr<Driver>, vector<shared_ptr<Driver>>, decltype(compare)> pq(compare, availableDrivers);
        return pq.top();
    }
};

class RideService {
private:
    unordered_map<int, shared_ptr<Ride>> rides;
    UserService& userService;
    DriverService& driverService;
    RideMatchingService matchingService;

public:
    RideService(UserService& u, DriverService& d) : userService(u), driverService(d) {}

    void requestRide(string userEmail, string password, int pickup, int drop) {
        if (!userService.verifyUser(userEmail, password)) {
            cout << "Invalid user credentials\n";
            return;
        }

        auto user = userService.getUser(userEmail);
        auto availableDrivers = driverService.getAvailableDrivers();
        auto nearestDriver = matchingService.findNearestDriver(user->location, availableDrivers);

        if (!nearestDriver) {
            cout << "No drivers available\n";
            return;
        }

        auto ride = make_shared<Ride>(user->id, pickup, drop);
        ride->status = RideStatus::IN_PROGRESS;
        ride->driverId = nearestDriver->id;
        rides[ride->id] = ride;

        nearestDriver->status = DriverStatus::BUSY;
        cout << "Ride assigned to driver " << nearestDriver->name << ". Estimated fare: $" << ride->estimatedFare << endl;
    }

    void completeRide(int rideId) {
        if (rides.count(rideId) == 0) return;
        rides[rideId]->status = RideStatus::COMPLETED;
        driverService.updateDriverStatus(rides[rideId]->driverId, DriverStatus::AVAILABLE);
        cout << "Ride completed.\n";
    }
};

int main() {
    UserService userService;
    DriverService driverService;
    RideService rideService(userService, driverService);

    userService.registerUser("alice@mail.com", "Alice", "pass123", 10);
    driverService.registerDriver("bob@driver.com", "Bob", "pass456", 15);

    rideService.requestRide("alice@mail.com", "pass123", 10, 25);
    return 0;
}
