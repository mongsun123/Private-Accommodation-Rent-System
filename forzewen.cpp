//Add new code
Property* linearSearchProperty(Property* head, int ads_id) {
    Property* current = head;

    while (current != nullptr) {
        if (current->ads_id == ads_id) {
            // Display property details
            cout << "\nProperty found!" << endl;
            cout << "Ads ID: " << current->ads_id << endl;
            cout << "Property Name: " << current->prop_name << endl;
            cout << "Location: " << current->location << endl;
            cout << "Monthly Rent: " << current->monthly_rent << endl;
            return current; // Found the property with matching ads_id
        }
        current = current->next;
    }
    cout << "Property not found!" << endl;
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

void bubbleSortProperty(Property** head) {
    if (*head == nullptr || (*head)->next == nullptr) {
        return; // If list is empty or has only one node, it is already sorted.
    }

    bool swapped;
    Property* current;
    Property* tail = nullptr;

    do {
        swapped = false;
        current = *head;

        while (current->next != tail) {
            // Extract the monthly_rent, location and size of two adjacent nodes
            int current_rent = extractRentValue(current->monthly_rent);
            int next_rent = extractRentValue(current->next->monthly_rent);

            string current_location = current->location;
            string next_location = current->next->location;

            int current_size = extractSizeValue(current->size);
            int next_size = extractSizeValue(current->next->size);

            // Compare the properties and swap if necessary
            if (current_rent < next_rent ||
                (current_rent == next_rent && current_location.compare(next_location) < 0) ||
                (current_rent == next_rent && current_location.compare(next_location) == 0 && current_size < next_size)) {
                swap(current->monthly_rent, current->next->monthly_rent);
                swap(current->location, current->next->location);
                swap(current->size, current->next->size);
                swapped = true;
            }

            current = current->next;
        }
        tail = current;

    } while (swapped);

    // Vector to hold pointers to the sorted properties
    vector<Property*> sortedProperties;

    // Now, the list is sorted. Traverse again to fill the vector
    current = *head;
    while (current != nullptr) {
        sortedProperties.push_back(current);
        current = current->next;
    }
    // Display the sorted properties
    cout << "Sorted properties:" << endl;
    for (Property* prop : sortedProperties) {
        cout << "Ads ID: " << prop->ads_id << endl << " Name: " << prop->prop_name << endl << " Location: " << prop->location << endl << " Monthly Rent: " << endl << prop->monthly_rent << endl << "\n";
    }
    /*for (int i = 0; i < 5 && i < sortedProperties.size(); i++) {
    
    Property* prop = sortedProperties[i];

    cout << "Ads ID: " << prop->ads_id << endl << " Name: " << prop->prop_name << endl << " Location: " << prop->location << endl << " Monthly Rent: " << endl << prop->monthly_rent << endl << "\n";
}*/
}




//Added code
Property* linearSearchProperty(Property* head, int ads_id);
void bubbleSortProperty(Property** head);
