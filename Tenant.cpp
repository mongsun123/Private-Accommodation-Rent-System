#include "Tenant.h"

//For Initial Value
void addFavoriteProperty(Property* properties, TenantFavList** head, int ads_id, string userid) {
    TenantFavList* fav = new TenantFavList;
    Property* temp = properties;
    while (temp != nullptr) {
        if (temp->ads_id == ads_id) {
            fav->User_Id = userid;
            fav->Ads_Id = ads_id;
            fav->Prop_Name = temp->prop_name;
            fav->Completion_year = temp->completion_year;
            fav->Monthly_Rent = temp->monthly_rent;
            fav->Location = temp->location;
            fav->Property_Type = temp->property_type;
            fav->Size = temp->size;
            fav->next = nullptr;
            fav->back = nullptr;
        }
        temp = temp->next;
    }
    // Check if the list is empty
    if (*head == nullptr) {
        *head = fav;
        fav->back = nullptr;
    }
    else {
        TenantFavList* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = fav;
        fav->back = current;
    }
}

void saveFavoriteProperty(Property* properties, TenantFavList** head, TenantFavList* favorites, int ads_id, string userid) {
    TenantFavList* fav = new TenantFavList; //append to existing favorites list
    Property* temp = properties;
    TenantFavList* current = favorites; //exisiting favorites list
    bool propertyFound = false;
    bool alreadyFavorited = false;
    while (temp != nullptr) {
        if (temp->ads_id == ads_id ) {
            propertyFound = true;
            while (current != nullptr) {
                if (current->Ads_Id == ads_id) {
                    if (current->User_Id == userid) {
                        alreadyFavorited = true;
                        break;
                    }                   
                }
                current = current->next;
            }

            if (!alreadyFavorited) {
                fav->User_Id = userid;
                fav->Ads_Id = ads_id;
                fav->Prop_Name = temp->prop_name;
                fav->Completion_year = temp->completion_year;
                fav->Monthly_Rent = temp->monthly_rent;
                fav->Location = temp->location;
                fav->Property_Type = temp->property_type;
                fav->Size = temp->size;
                fav->next = nullptr;
                fav->back = nullptr;

                // Check if the list is empty
                if (*head == nullptr) {
                    *head = fav;
                    fav->back = nullptr;
                }
                else {
                    TenantFavList* current = *head;
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    current->next = fav;
                    fav->back = current;
                }
                cout << "Property with Ads_Id " << ads_id << " Added" << endl << endl;
                cout << "Favorite property saved: " << endl;
                cout << "Ads Id: " << fav->Ads_Id << endl;
                cout << "Property Name: " << fav->Prop_Name << endl;
                cout << "Completion Year: " << fav->Property_Type << endl;
                cout << "Monthly Rent: " << fav->Monthly_Rent << endl;
                cout << "Location: " << fav->Location << endl;
                cout << "Property Type: " << fav->Property_Type << endl;
                cout << "Size :" << fav->Size << endl << endl;
                //break;
            }  
        }
        temp = temp->next;
    }

    if (!propertyFound) {
        cout << "Property with Ads_Id " << ads_id << " not found." << endl << endl;
    }

    else if (alreadyFavorited) {
        cout << "Property with Ads_Id " << ads_id << " is favourited." << endl << endl;
    }
}

void displayFavList(TenantFavList* favorites, string userid) {
    if (favorites == nullptr) {
        cout << "There are no properties in your favorite list." << endl;
    }
    else {
        cout << "Your favorite properties: " << endl;
        TenantFavList* current = favorites;
        while (current != nullptr) {
            if (current->User_Id == userid) {
                cout << "Ads Id: " << current->Ads_Id << endl;
                cout << "Prop Name: " << current->Prop_Name << endl;
                cout << "Completion year: " << current->Property_Type << endl;
                cout << "Monthly Rent: " << current->Monthly_Rent << endl;
                cout << "Location: " << current->Location << endl;
                cout << "Property Type: " << current->Property_Type << endl;
                cout << "Size :" << current->Size << endl;
                cout << "Payment Status: " << current->Payment_Status << endl << endl;               
            }
            current = current->next;
        }
    }
}

void addToRentFromFav(TenantFavList* favorites, string userid) {
    if (favorites == nullptr) {
        cout << "There are no favorite properties in your list " << endl;
    }
    else {
        bool checkRequest = false;
        int adsIdToRent;
        cout << "Enter Ads Id of the property from favorite list to rent: ";
        cin >> adsIdToRent;
        TenantFavList* current = favorites;
        TenantFavList* temp = favorites;
        bool tenancyProcess = false;
        while (current != nullptr) {
            if (current->Ads_Id == adsIdToRent && current->Payment_Status != "") {
                if (current->User_Id != userid) {
                    tenancyProcess = true;
                }
                else {
                    checkRequest = true;
                }
            }
            current = current->next;
        }
        while (temp != nullptr) {
            if (temp->Ads_Id == adsIdToRent && temp->User_Id == userid && temp->Payment_Status == "" && checkRequest == false) {
                temp->Payment_Status = "Requested";
                cout << "Rent request has been placed for property: " << endl;
                cout << "Ads Id: " << temp->Ads_Id << endl;
                cout << "Prop Name: " << temp->Prop_Name << endl;
                cout << "Completion year: " << temp->Property_Type << endl;
                cout << "Monthly Rent: " << temp->Monthly_Rent << endl;
                cout << "Location: " << temp->Location << endl;
                cout << "Property Type: " << temp->Property_Type << endl;
                cout << "Size :" << temp->Size << endl;
                cout << "Payment Status: " << temp->Payment_Status << endl << endl;
                return;
            }
            temp = temp->next;
        }
        if (checkRequest == true || tenancyProcess == true) {
            cout << "Property with Ads_Id " << adsIdToRent << " is already in tenancy process" << endl << endl;
        }
        else {
            cout << "Property with Ads_Id " << adsIdToRent << " not found in your favorites list." << endl << endl;
        }
    }
}

void displayRentHistory(TenantFavList* favorites, string User_Id) {
    cout << "Renting History" << endl;
    if (favorites == nullptr) {
        cout << "No renting history found" << endl;
    }
    else {
        TenantFavList* current = favorites;
        bool found = false;
        while (current != nullptr) {
            if (current->User_Id == User_Id && current->Payment_Status != "") {
                cout << "User Id: " << current->User_Id << endl;
                cout << "Ads Id: " << current->Ads_Id << endl;
                cout << "Property Name: " << current->Prop_Name << endl;
                cout << "Completion year: " << current->Property_Type << endl;
                cout << "Monthly Rent: " << current->Monthly_Rent << endl;
                cout << "Location: " << current->Location << endl;
                cout << "Property Type: " << current->Property_Type << endl;
                cout << "Size :" << current->Size << endl;
                cout << "Payment Status: " << current->Payment_Status << endl << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "No renting history found for User Id: " << User_Id << endl;
        }
    }
}


void tenantDashboard(TenantFavList* favorites, Property* properties, string userid) {
    int choice; string action;
    int ads_id;
    do {
        cout << "-------------TENANT DASHBOARD-------------" << endl;
        cout << "Main Menu" << endl;
        cout << "1. Sort and display property information in descending order based on monthly rent, location and size " << endl;
        cout << "2. Search and display property details" << endl;
        cout << "3. Save Property" << endl;
        cout << "4. Place Rent Request" << endl;
        cout << "5. Display Renting History" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: 
            cout << "1 for Bubble Sort, 2 for Merge Sort: ";
            cin >> action;  
            if (action == "1") { //Bubble Sort
                {
                    auto start_time = chrono::high_resolution_clock::now(); // Record the start time;
                    bubbleSort(properties);
                    // Display sorted properties
                    Property* temp = properties;
                    while (temp) {
                        cout << "Ads ID: " << temp->ads_id << endl;
                        cout << "Property Name: " << temp->prop_name << endl;
                        cout << "Monthly Rent: " << temp->monthly_rent << endl;
                        cout << "Location: " << temp->location << endl;
                        cout << "Size: " << temp->size << endl;
                        cout << "--------------------------------------" << endl;
                        temp = temp->next;
                    }
                    auto end_time = chrono::high_resolution_clock::now(); // Record the end time
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time); // Calculate the duration

                    cout << "Bubble sort took " << duration.count() << " milliseconds." << endl;
                }
            }
            else if (action == "2") { //Merge Sort
                auto start = chrono::high_resolution_clock::now(); // Start time measurement
                displayProperties(mergeSort(properties));
                auto stop = chrono::high_resolution_clock::now();  // Stop time measurement
                auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                cout << "Time taken by merge sort: " << duration.count() << " milliseconds" << endl;
            }
            else {
                cout << "Invalid Action" << endl;
            }
            break;
        case 2:
            cout << "1 for Linear Search, 2 for Binary Search Tree: ";
            cin >> action;
            if (action == "1") { //Linear Search
                cout << "Enter property ID to search: ";
                cin >> ads_id;
                linearSearchProperty(properties, ads_id);
            }
            else if (action == "2") { //Binary Search Tree
                cout << "Enter property ID to search: ";
                cin >> ads_id;
                Property* propertiesBST = read_csvBST("C:/Users/User/Desktop/Degree Year 2 Sem 2/Data Structure/test.csv");
                auto start = chrono::high_resolution_clock::now();
                printProperty(bstSearch(propertiesBST, ads_id));
                auto stop = chrono::high_resolution_clock::now();  // Stop time measurement
                auto duration = chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                cout << "Time taken by binary search tree property: " << duration.count() << " nanoseconds" << endl;
            }
            else {
                cout << "Invalid Action" << endl;
            }
            break;
        case 3:
            cout << "Enter property ID to add into favourite list: ";
            cin >> ads_id;
            saveFavoriteProperty(properties,&favorites,favorites,ads_id,userid);
            break;
        case 4:
            displayFavList(favorites,userid);
            addToRentFromFav(favorites,userid);
            break;
        case 5:
            displayRentHistory(favorites, userid);
            break;
        case 6:
            void logout();
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    } while (choice != 6);
}



