#include "Properties.h"

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenstream(s);
    while (getline(tokenstream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Property* read_csv(string filename) {
    ifstream file(filename);
    string line, word;
    getline(file, line); // skip the header line

    Property* head = nullptr;

    while (getline(file, line)) {
        stringstream s(line);
        int ads_id;
        string prop_name, completion_year, monthly_rent, location, property_type, size, furnished, region, rooms, parking, bathroom;
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
        Property* newproperty = new Property;
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
            Property* temp = head;
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


void printPropertiesForFilter(Property* head) {
    string action;
    int count = 0;
    Property* temp = head;
    string choice, num_room, property_location, property_furnished;
    cout << "--------------------------------------------------------" << endl;
    cout << "Which section you want filter?" << endl;
    cout << "1. Number of Room" << endl;
    cout << "2. Furnished" << endl;
    cout << "3. Normal Display" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == "1") {
        cout << "How many room number you want search: ";
        cin >> num_room;
        while (temp != nullptr && count < 5) {
            if (temp->rooms == num_room || temp->rooms == num_room+".0") {
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
                    cout << facility << ", ";
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
                }
                else if (action == "n" && count < 5) {
                    count++;
                    if (count != 5) {
                        temp = temp->next;
                    }
                }
                else if (action == "p" && count < 5) {
                    count++;
                    if (count != 5) {
                        temp = temp->prev;
                        if (temp == nullptr) {
                        }
                    }
                }

                if (count == 5) {
                    cout << "press n for next, p for prev, other key for exit: ";
                    cin >> action;
                    if (action == "n") {
                        if (temp->next != nullptr) {
                            temp = temp->next;
                            count = 0;
                        }
                        else {
                            count = 0;
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
            else if (action == "p") {
                temp = temp->prev;
            }
            else {
                temp = temp->next;
            }
        }
    }
    
    else if (choice == "2") {
        cout << "Which furnished you want to search? (1. Fully, 2. Partially, or 3. Not Furnished): ";
        cin >> property_furnished;

        if (property_furnished == "1") {
            property_furnished = "Fully Furnished";
        }
        else if (property_furnished == "2") {
            property_furnished = "Partially Furnished";
        }
        else if (property_furnished == "3") {
            property_furnished = "Not Furnished";
        }

        while (temp != nullptr && count < 5) {
            if (temp->furnished == property_furnished) {
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
                    cout << facility << ", ";
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
                }
                else if (action == "n" && count < 5) {
                    count++;
                    if (count != 5) {
                        temp = temp->next;
                    }
                }
                else if (action == "p" && count < 5) {
                    count++;
                    if (count != 5) {
                        temp = temp->prev;
                        if (temp == nullptr) {
                        }
                    }
                }

                if (count == 5) {
                    cout << "press n for next, p for prev, other key for exit: ";
                    cin >> action;
                    if (action == "n") {
                        if (temp->next != nullptr) {
                            temp = temp->next;
                            count = 0;
                        }
                        else {
                            count = 0;
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
            else if (action == "p") {
                temp = temp->prev;
            }
            else {
                temp = temp->next;
            }
        }
    }
    else if (choice == "3") {
        while (temp != nullptr && count < 5) {
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
                cout << facility << ", ";
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
            }
            else if (action == "n" && count < 5) {
                count++;
                if (count != 5) {
                    temp = temp->next;
                }
            }
            else if (action == "p" && count < 5) {
                count++;
                if (count != 5) {
                    temp = temp->prev;
                    if (temp == nullptr) {
                        break;
                    }
                }
            }

            if (count == 5) {
                cout << "press n for next, p for prev, other key for exit: ";
                cin >> action;
                if (action == "n") {
                    if (temp->next != nullptr) {
                        temp = temp->next;
                        count = 0;
                    }
                    else {
                       // count = 0;
                        break;
                    }
                }
                else if (action == "p") {
                    if (temp->prev != nullptr) {
                        temp = temp->prev;
                        count = 0;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
    }
}

Property* linearSearchProperty(Property* head, int ads_id) {
    Property* current = head;
    auto start = chrono::high_resolution_clock::now(); // Start time measurement
    while (current != nullptr) {
        if (current->ads_id == ads_id) {
            // Display property details
            cout << "\nProperty found!" << endl;
            cout << "Ads ID: " << current->ads_id << endl;
            cout << "Property Name: " << current->prop_name << endl;
            cout << "Location: " << current->location << endl;
            cout << "Monthly Rent: " << current->monthly_rent << endl;
            auto stop = chrono::high_resolution_clock::now();  // Stop time measurement
            auto duration = chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            cout << "Time taken by linear search property: " << duration.count() << " nanoseconds" << endl;
            return current; // Found the property with matching ads_id
        }
        current = current->next;
    }
    cout << "Property not found!" << endl;
    auto stop = chrono::high_resolution_clock::now();  // Stop time measurement
    auto duration = chrono::duration_cast<std::chrono::seconds>(stop - start);
    cout << "Time taken by linear search property: " << duration.count() << " seconds" << endl;
    return nullptr; // Property not found 
}

int extractRentValue(string monthly_rent) {
    string rent_number = "";
    for (char c : monthly_rent) {
        if (isdigit(c)) {
            rent_number += c;
        }
    }
    // Handle the case when there's no digit in the string
    if (rent_number.empty()) {
        return 0;
    }
    return stoi(rent_number);
}

int extractSizeValue(string size) {
    string numbers = "0123456789";
    string size_number = "";

    for (char c : size) {
        if (numbers.find(c) != string::npos) {
            size_number += c;
        }
    }
    return stoi(size_number);
}

void swap(Property* a, Property* b) {
    int temp_ads_id = a->ads_id;
    string temp_prop_name = a->prop_name;
    string temp_completion_year = a->completion_year;
    string temp_monthly_rent = a->monthly_rent;
    string temp_location = a->location;
    string temp_property_type = a->property_type;
    string temp_size = a->size;
    string temp_furnished = a->furnished;
    string temp_region = a->region;
    string temp_rooms = a->rooms;
    string temp_parking = a->parking;
    string temp_bathroom = a->bathroom;
    vector<string> temp_facilities = a->facilities;
    vector<string> temp_additional_facilities = a->additional_facilities;

    a->ads_id = b->ads_id;
    a->prop_name = b->prop_name;
    a->completion_year = b->completion_year;
    a->monthly_rent = b->monthly_rent;
    a->location = b->location;
    a->property_type = b->property_type;
    a->size = b->size;
    a->furnished = b->furnished;
    a->region = b->region;
    a->rooms = b->rooms;
    a->parking = b->parking;
    a->bathroom = b->bathroom;
    a->facilities = b->facilities;
    a->additional_facilities = b->additional_facilities;

    b->ads_id = temp_ads_id;
    b->prop_name = temp_prop_name;
    b->completion_year = temp_completion_year;
    b->monthly_rent = temp_monthly_rent;
    b->location = temp_location;
    b->property_type = temp_property_type;
    b->size = temp_size;
    b->furnished = temp_furnished;
    b->region = temp_region;
    b->rooms = temp_rooms;
    b->parking = temp_parking;
    b->bathroom = temp_bathroom;
    b->facilities = temp_facilities;
    b->additional_facilities = temp_additional_facilities;
}


void bubbleSort(Property* head) {
    if (head == nullptr);

    bool swapped;
    Property* ptr1;
    Property* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            // Compare monthly rent first
            if (extractRentValue(ptr1->monthly_rent) < extractRentValue(ptr1->next->monthly_rent)) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            // If monthly rent is the same, compare location
            else if (extractRentValue(ptr1->monthly_rent) == extractRentValue(ptr1->next->monthly_rent) &&
                ptr1->location < ptr1->next->location) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            // If both monthly rent and location are the same, compare size
            else if (extractRentValue(ptr1->monthly_rent) == extractRentValue(ptr1->next->monthly_rent) &&
                ptr1->location == ptr1->next->location &&
                extractSizeValue(ptr1->size) < extractSizeValue(ptr1->next->size)) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to perform Merge Sort on a linked list of Property elements
Property* mergeSort(Property* head) {
    // Base case: If the list is empty or has only one element, it's already sorted
    if (!head || !head->next)
        return head;

    // Calculate the length of the linked list
    int length = 0;
    Property* current = head;
    while (current) {
        length++;
        current = current->next;
    }

    // Create a dummy node to simplify merging
    Property dummy;
    dummy.next = head;

    // Iterate over the list in multiple steps, merging sublists of size step
    for (int step = 1; step < length; step *= 2) {
        Property* prevTail = &dummy; // Pointer to the tail of the merged list
        Property* curr = dummy.next; // Pointer to the current sublist

        // Merge pairs of sublists of size 'step'
        while (curr) {
            Property* left = curr; // Left sublist
            Property* right = split(left, step); // Right sublist
            curr = split(right, step); // Move the current pointer to the next sublist

            // Merge the left and right sublists, updating the prevTail pointer
            prevTail = merge(prevTail, left, right);
        }
    }
    return dummy.next; // Return the sorted list
}

// Function to split a linked list into two parts, given a step size
Property* split(Property* head, int step) {
    for (int i = 1; head && i < step; i++)
        head = head->next;

    if (!head)
        return nullptr;

    Property* rest = head->next; // Store the second part of the split
    head->next = nullptr; // Disconnect the first part
    return rest; // Return the second part
}

// Function to merge two sorted linked lists into a single sorted list
Property* merge(Property* tail, Property* left, Property* right) {
    tail->next = nullptr; // Initialize the merged list with a null terminator

    // Iterate while both left and right sublists have elements
    while (left && right) {
        // Compare and merge based on rent, location, and size criteria
        if (extractRentValue(left->monthly_rent) > extractRentValue(right->monthly_rent) ||
            (extractRentValue(left->monthly_rent) == extractRentValue(right->monthly_rent) && left->location > right->location) ||
            (extractRentValue(left->monthly_rent) == extractRentValue(right->monthly_rent) && left->location == right->location && extractSizeValue(left->size) > extractSizeValue(right->size))) {
            tail->next = left; // Append left element to the merged list
            left = left->next; // Move to the next element in the left sublist
        }
        else {
            tail->next = right; // Append right element to the merged list
            right = right->next; // Move to the next element in the right sublist
        }
        tail = tail->next; // Move the tail pointer
    }

    tail->next = left ? left : right; // Append any remaining elements from either sublist

    while (tail->next)
        tail = tail->next; // Move the tail pointer to the end of the merged list

    return tail; // Return the tail of the merged list
}

// Function to display the properties in the linked list
void displayProperties(Property* head) {
    Property* current = head;
    while (current) {
        // Display property details
        cout << "Ads ID: " << current->ads_id << endl;
        cout << "Property Name: " << current->prop_name << endl;
        cout << "Monthly Rent: " << current->monthly_rent << endl;
        cout << "Location: " << current->location << endl;
        cout << "Size: " << current->size << endl;
        cout << "-----------------------------" << endl;

        current = current->next; // Move to the next property in the list
    }
}

//Binary Search Tree Algorithm//
Property* bstInsert(Property* root, Property prop) {
    if (root == nullptr) {
        root = new Property();
        *root = prop;  // copy the data
    }
    else if (prop.ads_id < root->ads_id) {
        root->left = bstInsert(root->left, prop);
    }
    else {
        root->right = bstInsert(root->right, prop);
    }

    return root;
}

vector<string> splitBST(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Property* read_csvBST(string filename) {
    ifstream file(filename);
    string line, word;
    getline(file, line); // Skip the header line

    Property* root = nullptr;

    while (getline(file, line)) {
        stringstream s(line);
        int ads_id;
        string prop_name, completion_year, monthly_rent, location, property_type, rooms, parking, bathroom, size, furnished, region;
        vector<string> facilities, additional_facilities;
        int column_index = 0;

        // ... [Your CSV parsing code here] ...
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
                facilities = splitBST(word, ',');
                break;
            case 12:
                additional_facilities = splitBST(word, ',');
                break;
            case 13:
                region = word;
                break;
            }
            column_index++;
        }
        // Create a new property struct
        Property newProperty;
        newProperty.ads_id = ads_id;
        newProperty.prop_name = prop_name;
        newProperty.completion_year = completion_year;
        newProperty.monthly_rent = monthly_rent;
        newProperty.location = location;
        newProperty.property_type = property_type;
        newProperty.rooms = rooms;
        newProperty.parking = parking;
        newProperty.bathroom = bathroom;
        newProperty.size = size;
        newProperty.furnished = furnished;
        newProperty.facilities = facilities;
        newProperty.additional_facilities = additional_facilities;
        newProperty.region = region;

        // Insert the property into the BST
        root = bstInsert(root, newProperty);
    }

    return root; // This now returns the root of the BST instead of the head of the linked list
}

Property* bstSearch(Property* root, int ads_id) {
    if (root == nullptr || root->ads_id == ads_id) {
        return root;
    }
    if (root->ads_id < ads_id) {
        return bstSearch(root->right, ads_id);
    }
    return bstSearch(root->left, ads_id);
}

// Helper function to find the minimum value node in a subtree
Property* findMinValueNode(Property* root) {
    Property* current = root;

    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Function to print a property (for demonstration purposes)
void printProperty(Property* prop) {
    if (prop == nullptr) {
        cout << "Property not found." << endl;
        return;
    }

    cout << "Property ID: " << prop->ads_id << endl;
    cout << "Property Name: " << prop->prop_name << endl;
    cout << "Location: " << prop->location << endl;
    cout << "Monthly Rent: " << prop->monthly_rent << endl;
    // ... [You can add more fields to display if you want] ...
    cout << endl;
}

// Recursive function to print BST pre-order (for demonstration purposes)
void preOrder(Property* root) {
    if (root == nullptr) return;

    //printProperty(root);
    inOrder(root->left);
    inOrder(root->right);
}

// Recursive function to print BST in-order (for demonstration purposes)
void inOrder(Property* root) {
    if (root == nullptr) return;

    inOrder(root->left);
    //printProperty(root);
    inOrder(root->right);
}

// Recursive function to print BST post-order (for demonstration purposes)
void postOrder(Property* root) {
    if (root == nullptr) return;

    inOrder(root->left);
    inOrder(root->right);
    //printProperty(root);
}
