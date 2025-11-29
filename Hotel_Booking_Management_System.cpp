#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Booking {
    int roomNumber;
    string guestName;
    string bookingDate;
};

class Room {
public:
    int roomNumber;
    string type;
    double price;
    bool isBooked;

    Room(int r, string t, double p) {
        roomNumber = r;
        type = t;
        price = p;
        isBooked = false;
    }
};

class HotelSystem {
private:
    vector<Room> rooms;
    vector<Booking> bookings;
    const string fileName = "bookings.csv";

public:
    
    void addRoom() {
        int rNum;
        string rType;
        double rPrice;

        cout << "\nEnter Room Number: ";
        cin >> rNum;
        
       
        for(const auto& room : rooms) {
            if(room.roomNumber == rNum) {
                cout << "Error: Room already exists.\n";
                return;
            }
        }

        cout << "Enter Type (Standard/Deluxe/Suite): ";
        cin >> rType;
        cout << "Enter Price: ";
        cin >> rPrice;

        rooms.push_back(Room(rNum, rType, rPrice));
        cout << "Room " << rNum << " added successfully.\n";
    }

    
    void listRooms() {
        cout << "\n--- Room List ---\n";
        cout << left << setw(10) << "Room No" << setw(15) << "Type" << setw(10) << "Price" << endl;
        cout << "-----------------------------------\n";
        for (const auto& room : rooms) {
            cout << left << setw(10) << room.roomNumber 
                 << setw(15) << room.type 
                 << setw(10) << room.price << endl;
        }
    }

 
    void bookRoom() {
        int rNum;
        cout << "\nEnter Room Number to book: ";
        cin >> rNum;

        bool found = false;
        for (auto& room : rooms) {
            if (room.roomNumber == rNum) {
                found = true;
                if (room.isBooked) {
                    cout << "Room is already booked.\n";
                } else {
                    string name, date;
                    cout << "Enter Guest Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Date (DD-MM-YYYY): ";
                    cin >> date;

                    room.isBooked = true;
                    
                    Booking newBooking;
                    newBooking.roomNumber = rNum;
                    newBooking.guestName = name;
                    newBooking.bookingDate = date;
                    bookings.push_back(newBooking);

                    cout << "Room " << rNum << " booked for " << name << " on " << date << ".\n";
                }
                break;
            }
        }
        if (!found) cout << "Room not found.\n";
    }

    void checkAvailability() {
        cout << "\n--- Available Rooms ---\n";
        bool anyAvailable = false;
        for (const auto& room : rooms) {
            if (!room.isBooked) {
                cout << "Room " << room.roomNumber << " (" << room.type << ") - " << room.price << "\n";
                anyAvailable = true;
            }
        }
        if (!anyAvailable) cout << "No rooms available.\n";
    }

    void listBookings() {
        if (bookings.empty()) {
            cout << "\nNo current bookings.\n";
            return;
        }
        cout << "\n--- All Bookings ---\n";
        for (const auto& b : bookings) {
            cout << "Room: " << b.roomNumber << " | Guest: " << b.guestName << " | Date: " << b.bookingDate << endl;
        }
    }

    void bookingsForDate() {
        string searchDate;
        cout << "\nEnter Date to search (DD-MM-YYYY): ";
        cin >> searchDate;

        cout << "\n--- Bookings on " << searchDate << " ---\n";
        bool found = false;
        for (const auto& b : bookings) {
            if (b.bookingDate == searchDate) {
                cout << "Room: " << b.roomNumber << " | Guest: " << b.guestName << endl;
                found = true;
            }
        }
        if (!found) cout << "No bookings found for this date.\n";
    }

    void searchGuest() {
        string searchName;
        cout << "\nEnter Guest Name to search: ";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;
        for (const auto& b : bookings) {
            if (b.guestName == searchName) {
                cout << "Found: Room " << b.roomNumber << " booked on " << b.bookingDate << endl;
                found = true;
            }
        }
        if (!found) cout << "Guest not found.\n";
    }

    void saveToCSV() {
        ofstream file(fileName, ios::app);
        if (file.is_open()) {
            for (const auto& b : bookings) {
                file << b.roomNumber << "," << b.guestName << "," << b.bookingDate << "\n";
            }
            file.close();
            cout << "All bookings saved to " << fileName << " successfully.\n";
        } else {
            cout << "Error opening file.\n";
        }
    }
};

int main() {
    HotelSystem hotel;
    int choice;

    hotel.addRoom(); 

    while (true) {
        cout << "\n=== HOTEL MANAGEMENT ===\n";
        cout << "1) Add room\n";
        cout << "2) List rooms\n";
        cout << "3) Book room\n";
        cout << "4) Check room availability\n";
        cout << "5) List all bookings\n";
        cout << "6) Bookings for a date\n";
        cout << "7) Search guest\n";
        cout << "8) Save to CSV\n";
        cout << "9) Exit\n";
        cout << "Enter Option: ";
        cin >> choice;

        switch (choice) {
            case 1: hotel.addRoom(); break;
            case 2: hotel.listRooms(); break;
            case 3: hotel.bookRoom(); break;
            case 4: hotel.checkAvailability(); break;
            case 5: hotel.listBookings(); break;
            case 6: hotel.bookingsForDate(); break;
            case 7: hotel.searchGuest(); break;
            case 8: hotel.saveToCSV(); break;
            case 9: 
                cout << "Exiting...\n"; 
                return 0;
            default: cout << "Invalid option.\n";
        }
    }
}