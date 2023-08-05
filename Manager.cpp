#include <iostream>
#include <string>
using namespace std;

struct User {
    string User_Id;
    string User_Password;
    string User_Name;
    string User_Email;
    string User_Role;
    string User_Status;
    User* next;
    User* prev;

};

// Function to add a new user to the linked list
void addUser(User** head, string userId, string password, string name, string email, string role, string status) {
    // Create a new user struct
    User* newUser = new User;
    newUser->User_Id = userId;
    newUser->User_Password = password;
    newUser->User_Name = name;
    newUser->User_Email = email;
    newUser->User_Role = role;
    newUser->User_Status = status;
    newUser->next = nullptr;

    // Check if the list is empty
    if (*head == nullptr) {
        *head = newUser;
        newUser->prev = nullptr;
    }
    else {
        // Find the last user in the list
        User* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        // Add the new user to the end of the list
        temp->next = newUser;
        newUser->prev = temp;
    }
}

// Function to display all tenants' detail in the linked list
void displayAllTenant(User* head) {
    cout << "Tenant Information" << endl;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Role == "Tenant") {
            cout << "----------------------" << endl;
            cout << "User ID: " << temp->User_Id << endl;
            cout << "Name: " << temp->User_Name << endl;
            cout << "Email: " << temp->User_Email << endl;
            cout << "Role: " << temp->User_Role << endl;
            cout << "Status: " << temp->User_Status << endl;
            cout << "----------------------" << endl;
        }
        temp = temp->next;
    }
}

void displayAllInactiveTenant(User* head) {
    int no = 1;
    cout << "Tenant Inactive Account" << endl;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Role == "Tenant") {
            cout << no << ". User ID: " << temp->User_Id << endl;
            no++;
        }
        temp = temp->next;
    }
}

bool searchTenant(User* head, string uid) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == uid && temp->User_Role == "Tenant") {
            cout << "----------------------" << endl;
            cout << "User ID: " << temp->User_Id << endl;
            cout << "Name: " << temp->User_Name << endl;
            cout << "Email: " << temp->User_Email << endl;
            cout << "Role: " << temp->User_Role << endl;
            cout << "Status: " << temp->User_Status << endl;
            cout << "----------------------" << endl;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool deleteTenantByStatus(User* head, string userId) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == userId && temp->User_Status == "Inactive" && temp->User_Role == "Tenant") {
            // Adjust the previous node's next pointer
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            else {
                // If the user to be deleted is the head node
                head = temp->next;
            }

            // Adjust the next node's previous pointer
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }

            //Delete the user
            delete temp;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/*
void deleteTenantByStatus2(User* head, string action) {
    User* tempNext = nullptr; // Used for storing next node of the linked list prior deletion
    User* temp = head;
    
    while (temp != nullptr) {
        // Circular: Find the last node
        User* lastNode = head; // Used for storing last node of the linked list
        while (lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
        if (temp->User_Role == "Tenant" && temp->User_Status == "Inactive") {
            cout << "----------------------" << endl;
            cout << "User ID: " << temp->User_Id << endl;
            cout << "Name: " << temp->User_Name << endl;
            cout << "Email: " << temp->User_Email << endl;
            cout << "Role: " << temp->User_Role << endl;
            cout << "Status: " << temp->User_Status << endl;
            cout << "----------------------" << endl;
            cout << "Press n for next, p for prev, d for delete, other key for exit: ";
            cin >> action;
            if (action == "n") {
                if (temp->next != nullptr) {
                    temp = temp->next;
                }
                else {
                    temp = head; // Circular
                }
            }
            else if (action == "p") {
                if (temp != nullptr) {
                    temp = temp->prev;
                }
                else {
                    temp = lastNode;
                }
            }
            else if (action == "d") {
                // Keep track of the next node
                if (temp->next != nullptr) {
                    tempNext = temp->next;
                }
                else {
                    tempNext = head;
                }

                // Adjust the previous node's next pointer
                if (temp->prev != nullptr) {
                    temp->prev->next = temp->next;
                }
                else {
                    // If the user to be deleted is the head node
                    head = temp->next;
                }
                // Adjust the next node's previous pointer
                if (temp->next != nullptr) {
                    temp->next->prev = temp->prev;
                }

                delete temp;
                cout << "Delete record successfully!" << endl;

                temp = tempNext;
            }
            else {
                break;
            }
        }
        else {
            temp = temp->next;
        }
    }
}*/

int main() {
    User* userList = new User;
    userList = nullptr;
    int choice;string action, uid;
    cout << "Welcome Manager To PRIVATE ACCOMMODATION RENT SYSTEM" << endl;
    // Example usage:
    addUser(&userList, "x123", "password123", "John Doe", "john@example.com", "Admin", "Inactive");
    addUser(&userList, "u123", "password123", "Max Kilman", "john@example.com", "Tenant", "Inactive");
    addUser(&userList, "x345", "password123", "Franky Dane", "john@example.com", "Admin", "Inactive");
    addUser(&userList, "u456", "securepass", "Jane Smith", "jane@example.com", "Tenant", "Active");
    addUser(&userList, "u789", "12345678", "Bob Johnson", "bob@example.com", "Tenant", "Inactive");

    do {

        cout << "--------------------------------------------------------" << endl;
        cout << "Main Menu" << endl;
        cout << "1. Display all registered tenants' details" << endl;
        cout << "2. Search tenant's details" << endl;
        cout << "3. Delete tenant accounts based on inactivity status" << endl;
        cout << "4. Generate top 10 property report" << endl;
        cout << "5. Manage tenancy process upon renting request received" << endl;
        cout << "6. Manage payment of the confirmed tenancy" << endl;
        cout << "7. Logout" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllTenant(userList);
            break;
        case 2:
            cout << "Search the tenant's user ID: ";
            cin >> uid;
            if (!searchTenant(userList, uid)) {
                cout << "Record not found!" << endl;
            }
            break;
        case 3:
            displayAllInactiveTenant(userList);
            cout << "Delete the tenant's inactive account using user ID: ";
            cin >> uid;
            if (!deleteTenantByStatus(userList, uid)) {
                cout << "Account not found!" << endl;
            }
            else {
                cout << "Account is deleted successfully!" << endl;
            }
            break;
        case 4:
            //generateTopPropertyReport();
            break;
        case 5:
            //manageTenancyProcess();
            break;
        case 6:
            // managePayment();
            break;
        case 7:
            cout << "Logging out the system. Thank You!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    } while (choice != 7);
    return 0;





    //cout << "Before deletion:" << endl;


    // Example usage of deleting a specific user by User_Id
   // deleteTenantByStatus(userList, "u456");

    //cout << "After deletion:" << endl;
    //displayAllTenant(userList);

    // Don't forget to free the memory after you're done using the linked list
    //deleteAllUsers(userList);

    //return 0;
}
