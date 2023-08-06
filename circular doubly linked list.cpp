#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct property {
    int ads_id;
    string prop_name;
    string completion_year;
    string monthly_rent;
    string location;
    string property_type;
    string rooms;
    string parking;
    string bathroom;
    string size;
    string furnished;
    vector<string> facilities;
    vector<string> additional_facilities;
    string region;
    property* next;
    property* prev;
};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenstream(s);
    while (getline(tokenstream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

property* read_csv(string filename) {
    ifstream file(filename);
    string line, word;
    getline(file, line); // skip the header line

    property* head = nullptr;

    while (getline(file, line)) {
        stringstream s(line);
        int ads_id;
        string prop_name, completion_year, monthly_rent, location, property_type, rooms, parking, bathroom, size, furnished, region;
        vector<string> facilities, additional_facilities;
        int column_index = 0;

        while (getline(s, word, ',')) {
            if (word[0] == '"') {
                while (word.back() != '"' || word.size() < 2) {
                    string extra_word;
                    getline(s, extra_word, ',');
                    word += "," + extra_word;
                }
                word = word.substr(1, word.size() - 2);
            }

            switch (column_index) {
            case 0:
                ads_id = stoi(word);
                break;
            case 1:
                prop_name = word;
                break;
            case 2:
                completion_year = word;
                break;
            case 3:
                monthly_rent = word;
                break;
            case 4:
                location = word;
                break;
            case 5:
                property_type = word;
                break;
            case 6:
                rooms = word;
                break;
            case 7:
                parking = word;
                break;
            case 8:
                bathroom = word;
                break;
            case 9:
                size = word;
                break;
            case 10:
                furnished = word;
                break;
            case 11:
                facilities = split(word, ',');
                break;
            case 12:
                additional_facilities = split(word, ',');
                break;
            case 13:
                region = word;
                break;
            }
            column_index++;
        }

         //create a new property struct
        property* newproperty = new property;
        newproperty->ads_id = ads_id;
        newproperty->prop_name = prop_name;
        newproperty->completion_year = completion_year;
        newproperty->monthly_rent = monthly_rent;
        newproperty->location = location;
        newproperty->property_type = property_type;
        newproperty->rooms = rooms;
        newproperty->parking = parking;
        newproperty->bathroom = bathroom;
        newproperty->size = size;
        newproperty->furnished = furnished;
        newproperty->facilities = facilities;
        newproperty->additional_facilities = additional_facilities;
        newproperty->region = region;
        newproperty->next = nullptr;

         //check if the list is empty
        if (head == nullptr) {          
            head = newproperty;
            newproperty->prev = nullptr;
        }
        else {
             //find the last property in the list
            property* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }

            // add the new property to the end of the list
            temp->next = newproperty;
            newproperty->prev = temp;
        }
    }
    return head;
}

void printproperties(property* head) {
    string action;
    int count = 0;
    property* temp = head;
    property* lastnode = head;
    while (lastnode->next != nullptr) {
        lastnode = lastnode->next;
    }
    while (temp != nullptr && count<5) {
            cout << "--------------------------------------------------------" << endl;
            cout << "property id: " << temp->ads_id << endl
                << "property name: " << temp->prop_name << endl
                << "completion year: " << temp->completion_year << endl
                << "monthly rent: " << temp->monthly_rent << endl
                << "location: " << temp->location << endl
                << "property type: " << temp->property_type << endl
                << "rooms: " << temp->rooms << endl
                << "parking: " << temp->parking << endl
                << "bathroom: " << temp->bathroom << endl
                << "size: " << temp->size << endl
                << "furnished: " << temp->furnished << endl
                << "facilities: ";
            for (string facility : temp->facilities) {
                cout << facility << ", " ;
            }
            cout << endl;
            cout << "additional facilities: ";
            for (string additional_facility : temp->additional_facilities) {
                cout << additional_facility << ", ";
            }
            cout << endl;    
            cout << "region: " << temp->region << endl;
            cout << "--------------------------------------------------------" << endl;
            if (action == "") {
                count++;
                if (count != 5) {
                    temp = temp->next;
                }
            }else if (action == "n" && count<5){
                count++;
                if (count != 5) {
                    temp = temp->next;
                }
            }else if (action == "p" && count<5) {
                count++;
                if (count != 5) {
                    temp = temp->prev;
                    if (temp == nullptr) {
                        temp = lastnode; //circular
                    }
                }
            }
 
        if (count == 5) {
            cout << "press n for next, p for prev, d for delete, other key for exit: ";
            cin >> action;
            if (action == "n") {
                if (temp->next != nullptr) {
                    temp = temp->next;
                    count = 0;
                }
                else {
                    count = 0;
                    temp = head; // circular
                }
            }
            else if (action == "p") {
                if (temp->prev != nullptr) {
                    temp = temp->prev;
                    count = 0;
                }
            }
            else {
                break;
            }
        }
        
    }
}

int main() {
    property* properties = read_csv("c:/users/user/desktop/mudah-apartment-kl-selangor.csv");
    printproperties(properties);
    return 0;
}
