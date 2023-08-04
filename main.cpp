#include <iostream>
#include <string>
using namespace std;

struct Property {
    string ads_id; // ads_id
    string prop_name;
    string completion_year; // assuming NaN values are represented as -1
    double monthly_rent;
    string location;
    string property_type;
    int rooms;
    int parking; // assuming NaN values are represented as -1
    int bathroom; // assuming NaN values are represented as -1
    double size;
    string furnished;
    string facilities;
    string additional_facilities;
    string region;

    Property* prev;
    Property* next;
};

class CircularDoublyLinkedList {
    Property* head;

public:
    CircularDoublyLinkedList() {
        head = NULL;
    }

    void addData(int ads_id, std::string prop_name, int completion_year, std::string monthly_rent, std::string location, std::string property_type, std::string rooms, int parking, int bathroom, std::string size, std::string furnished, std::string facilities, std::string additional_facilities, std::string region);
    void displayData();
    void sortData();
    Node* searchData(int ads_id);
    void deleteData(int ads_id);
};
