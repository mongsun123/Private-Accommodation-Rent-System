#include <iostream>
#include <string>
using namespace std;

struct Node {
    int ads_id;
    string prop_name;
    int completion_year; // assuming NaN values are represented as -1
    string monthly_rent;
    string location;
    string property_type;
    string rooms;
    int parking; // assuming NaN values are represented as -1
    int bathroom; // assuming NaN values are represented as -1
    tring size;
    string furnished;
    string facilities;
    string additional_facilities;
    string region;

    Node* prev;
    Node* next;
};
