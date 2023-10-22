#include "Manager.h"
#include "User.h"
#include "Tenant.h"

//Managger main menu
void managerDashboard(User* head, TenantFavList* favorites) {
    int choice;
    string uid;
    do {
        cout << "-------------MANAGER DASHBOARD-------------" << endl;
        cout << "1. Display all registered tenants' details" << endl;
        cout << "2. Search tenant's details" << endl;
        cout << "3. Delete tenant accounts based on inactivity status" << endl;
        cout << "4. Generate top 10 property report" << endl;
        cout << "5. Manage tenancy process upon renting request received" << endl;
        cout << "6. Manage payment of the confirmed tenancy" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllTenant(head);
            break;
        case 2:
            cout << "Sarch the tenant's user id: ";
            cin >> uid;
            if (!searchTenant(head, uid)) {
                cout << "Record not found!" << endl;
            }
            break;
        case 3:
            if (displayAllInactiveTenant(head) != 1) {
                cout << "Delete the tenant's inactive account using user id: ";
                cin >> uid;
                if (!deleteTenantByStatus(head, uid)) {
                    cout << "Account not found!" << endl;
                }
                else {
                    cout << "Account is deleted successfully!" << endl;
                }
            }                     
            break;
        case 4:
            summarizeTopFavoriteProperties(favorites);
            break;
        case 5:
            manageTenancyProcess(favorites);
            break;
        case 6:
            managePayment(favorites);
            break;
        case 7:
            void logout();
           // cout << "Logging out the system. Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    } while (choice != 7);
}

void summarizeTopFavoriteProperties(TenantFavList* favorites) {
    cout << "Top 10 Favorite Properties Summary:" << endl;

    unordered_map<int, int> propertyCountMap;
    TenantFavList* current = favorites;

    // Count the occurrences of each property
    while (current != nullptr) {
        propertyCountMap[current->Ads_Id]++;
        current = current->next;
    }

    // Create a vector of pairs for sorting
    vector<pair<int, int>> propertyCountPairs;
    for (const auto& entry : propertyCountMap) {
        propertyCountPairs.push_back(make_pair(entry.first, entry.second));
    }

    // Sort the vector in descending order based on property count
    sort(propertyCountPairs.begin(), propertyCountPairs.end(),
        [](pair<int, int>& a, pair<int, int>& b) {
            return a.second > b.second;
        });

    // Display the top 10 favorite properties with details
    int count = 0;
    for (auto& pair : propertyCountPairs) {
        if (count >= 10) {
            break;
        }

        cout << "TOP " << count + 1 << endl;

        // Find and display property details
        TenantFavList* fav = favorites;
        while (fav != nullptr) {
            if (fav->Ads_Id == pair.first) {
                cout << "Total Favourite: " << pair.second << endl;
                cout << "Ads Id: " << fav->Ads_Id << endl;
                cout << "Property Name: " << fav->Prop_Name << endl;
                cout << "Completion year: " << fav->Property_Type << endl;
                cout << "Monthly Rent: " << fav->Monthly_Rent << endl;
                cout << "Location: " << fav->Location << endl;
                cout << "Property Type: " << fav->Property_Type << endl;
                cout << "Size :" << fav->Size << endl;
                cout << "----------------------" << endl << endl;
                break;
            }
            fav = fav->next;
        }

        count++;
    }

    if (count == 0) {
        cout << "No favorite properties found." << endl;
    }
}

void manageTenancyProcess(TenantFavList* favorites) {
        cout << "Properties with requested status:" << endl;
        TenantFavList* fav = favorites; // Use for find requested payment status
        TenantFavList* temp = favorites; // Use for find the given ads_id
        bool pendingPropertiesExist = false;
        // Display property info that is only with payment status requested
        while (fav != nullptr) {
            if (fav->Payment_Status == "Requested") {
                pendingPropertiesExist = true;
                cout << "----------------------" << endl;
                cout << "User Id: " << fav->User_Id << endl;
                cout << "Ads Id: " << fav->Ads_Id << endl;
                cout << "Prop Name: " << fav->Prop_Name << endl;
                cout << "Completion year: " << fav->Property_Type << endl;
                cout << "Monthly Rent: " << fav->Monthly_Rent << endl;
                cout << "Location: " << fav->Location << endl;
                cout << "Property Type: " << fav->Property_Type << endl;
                cout << "Size :" << fav->Size << endl << endl;
                cout << "Payment Status: " << fav->Payment_Status << endl;
                cout << "----------------------" << endl << endl;
            }
            fav = fav->next ;
        }

        //No properties found
        if (!pendingPropertiesExist) {
            cout << "No properties are currently in requested status." << endl;
            return;
        }

        //Select the property and user
        int adsIdToProcess;
        cout << "Enter Ads Id to process rent request: ";
        cin >> adsIdToProcess;

        string userid;
        cout << "Enter User Id to process rent request: ";
        cin >> userid;
    
        bool propertyApproved = false;
        while (temp != nullptr) {
            if (temp->Ads_Id == adsIdToProcess && temp->Payment_Status == "Approved") {
                propertyApproved = true;
                break;
            }
            temp = temp->next;
        }

         // Find the property with the given Ads Id
        temp = favorites; // reset pointer
        bool propertyFound = false;
        while (temp != nullptr) {
            if (temp->Ads_Id == adsIdToProcess && temp->User_Id == userid && temp->Payment_Status == "Requested") {
                cout << "Rent request received for property: " << endl;
                cout << "Ads Id: " << temp->Ads_Id << endl;
                cout << "Prop Name: " << temp->Prop_Name << endl;
                cout << "Completion year: " << temp->Property_Type << endl;
                cout << "Monthly Rent: " << temp->Monthly_Rent << endl;
                cout << "Location: " << temp->Location << endl;
                cout << "Property Type: " << temp->Property_Type << endl;
                cout << "Size :" << temp->Size << endl << endl;
                cout << "Payment Status: " << temp->Payment_Status << endl << endl;

                cout << "Do you want to approve or deny the request? (Enter 'approve' or 'deny'): ";
                string response;
                cin >> response;
                
                if (response == "approve" && propertyApproved == false) {
                    temp->Payment_Status = "Approved";
                    cout << "Rent request approved." << endl;
                    cout << "New payment status: " << temp->Payment_Status << endl << endl;
                }
                else if (response == "deny") {
                    temp->Payment_Status = "Denied";
                    cout << "Rent request denied." << endl;
                    cout << "New payment status: " << temp->Payment_Status << endl << endl;
                }
                else if (propertyApproved == true){
                    cout << "The property is appointed by other tenant." << endl;
                }
                else {
                    cout << "Invalid response. Please try again." << endl;
                }
                propertyFound = true;
                break;
            }
            temp = temp->next;
        } 
    
           //No property found in the fav list of user
        if (!propertyFound) {
            cout << "Property with Ads_Id " << adsIdToProcess << " of user id " << userid << " not found or has no rent request." << endl << endl;
        }
    }

void managePayment(TenantFavList* favorites) {
        cout << "Properties with approved status:" << endl;
        bool approvedPropertiesExist = false;
        TenantFavList* fav = favorites; // Use for find approved payment status
        TenantFavList* temp = favorites; // Use for find the given ads_id
        // Display the approved status property info
        while (fav != nullptr) {
            if (fav->Payment_Status == "Approved") {
                approvedPropertiesExist = true;
                cout << "----------------------" << endl;
                cout << "Ads Id: " << fav->Ads_Id << endl;
                cout << "Prop Name: " << fav->Prop_Name << endl;
                cout << "Completion year: " << fav->Property_Type << endl;
                cout << "Payment Status: " << fav->Payment_Status << endl << endl;
            }
            fav = fav->next;
        }
        
        //No approved properties
        if (!approvedPropertiesExist) {
            cout << "No properties are currently in approved status." << endl;
            return;
        }
    
        // Update the payment status of selected property
        cout << "Enter Ads Id to process payment: ";
        int adsIdToProcess;
        cin >> adsIdToProcess;
    
        // Find the property with the given Ads Id
        bool propertyFound = false;
        while (temp != nullptr) {

            if (temp->Ads_Id == adsIdToProcess && temp->Payment_Status == "Approved") {
                cout << "Property approved for rent: " << endl;
                cout << "Ads Id: " << temp->Ads_Id << endl;
                cout << "Prop Name: " << temp->Prop_Name << endl;
                cout << "Completion year: " << temp->Property_Type << endl;
                cout << "Payment Status: " << temp->Payment_Status << endl << endl;


                // change the status to Paid
                temp->Payment_Status = "Paid";

                cout << "Payment received. New payment status: " << temp->Payment_Status << endl << endl;
                propertyFound = true;
                break;
            }
            temp = temp->next;
        }
        if (!propertyFound) {
            cout << "Property with Ads_Id " << adsIdToProcess << " not found or has no rent approval." << endl << endl;
        }
    }



