#include "User.h"
#include "Admin.h"
#include "Tenant.h"
#include "Manager.h"

string loggedUserId = "";

// Function to add a new user to the linked list
void addUser(User** head, string User_Id, string User_Password, string User_Name, string User_Email, string User_Role, string User_Status) {
    // Create a new user struct
    User* newUser = new User;
    newUser->User_Id = User_Id;
    newUser->User_Password = User_Password;
    newUser->User_Name = User_Name;
    newUser->User_Email = User_Email;
    newUser->User_Role = User_Role;
    newUser->User_Status = User_Status;
    newUser->next = nullptr;
    newUser->prev = nullptr;

    // Check if the list is empty
    if (*head == nullptr) {
        *head = newUser;
        newUser->prev = nullptr;
    }
    else {
        User* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
        newUser->prev = current;
    }
}

bool verifyExisitingUser(User* head, string User_Id) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == User_Id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Function to display all users in the linked list
void displayUsers(User* head) {
    User* temp = head;
    while (temp != nullptr){
        cout << "----------------------" << endl;
        cout << "User ID: " << temp->User_Id << endl;
        cout << "Name: " << temp->User_Name << endl;
        cout << "Email: " << temp->User_Email << endl;
        cout << "Role: " << temp->User_Role << endl;
        cout << "Status: " << temp->User_Status << endl;
        cout << "----------------------" << endl;
        temp = temp->next;
    }
}

void displayAllTenant(User* head) {
    cout << "Tenant Information" << endl;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Role == "Tenant") {
            cout << "----------------------" << endl;
            cout << "User Id: " << temp->User_Id << endl;
            cout << "Name: " << temp->User_Name << endl;
            cout << "Email: " << temp->User_Email << endl;
            cout << "Role: " << temp->User_Role << endl;
            cout << "Status: " << temp->User_Status << endl;
            cout << "----------------------" << endl;
        }
        temp = temp->next;
    }
}

int displayAllInactiveTenant(User* head) {
    int no = 1;
    cout << "Tenant Inactive Account" << endl;
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Role == "Tenant" && temp->User_Status=="Inactive") {
            cout << no << ". user id: " << temp->User_Id << endl;
            no++;
        }
        temp = temp->next;
    }
    if (no == 1) {
        cout<< "No Inactive Tenant Account"<<endl;
        return no;
    }
    return no;
} 

void displayTenantForAdmin(User* head) {
    User* temp = head;
    while (temp->prev != nullptr) {
        temp = temp->prev;
    }
    string choice;
    cout << "Press 1 for view ACTIVE tenant, Press 2 for view INACTIVE tenant : ";
    cin >> choice;
    while (temp != nullptr) {
        if (temp->User_Role == "Tenant") {
            if (choice == "1" && temp->User_Status == "Active") {
                cout << "User ID: " << temp->User_Id << endl;
                cout << "Name: " << temp->User_Name << endl;
                cout << "Email: " << temp->User_Email << endl;
                cout << "Role: " << temp->User_Role << endl;
                cout << "Status: " << temp->User_Status << endl;
                cout << "----------------------" << endl;
            }
            else if (choice == "2" && temp->User_Status == "Inactive") {
                cout << "User ID: " << temp->User_Id << endl;
                cout << "Name: " << temp->User_Name << endl;
                cout << "Email: " << temp->User_Email << endl;
                cout << "Role: " << temp->User_Role << endl;
                cout << "Status: " << temp->User_Status << endl;
                cout << "----------------------" << endl;
            }
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

bool deleteTenantByStatus(User* head, string uid) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == uid && temp->User_Status == "Inactive" && temp->User_Role == "Tenant") {
            // adjust the previous node's next pointer
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            else {
                // if the user to be deleted is the head node
                head = temp->next;
            }

            // adjust the next node's previous pointer
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }

            //delete the user
            delete temp;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void deleteUserById(User** head, string User_Id) {
    if (*head == nullptr) {
        return;
    }

    if ((*head)->User_Id == User_Id) {
        User* temp = *head;
        *head = (*head)->next;
        delete temp;
        return;
    }

    User* current = *head;
    while (current->next != nullptr && current->next->User_Id != User_Id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        User* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Function to delete all users and free memory to prevent memory leaks
void deleteAllUsers(User* head) {
    while (head != nullptr) {
        User* temp = head;
        head = head->next;
        delete temp;
    }
}

bool login(User* head, string User_Id, string User_Password, TenantFavList* favorites, Property* properties) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Tenant") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
            tenantDashboard(favorites,properties, loggedUserId);
            return true;
        }
        else if (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Manager") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
            managerDashboard(head,favorites);
            return true;
        }
        else if (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Admin") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
            //reset(temp);
            adminDashboard(head,properties);
            return true;
        }
        temp = temp->next;
    }

    cout << "Login Failed. Invalid credentials or user not active." << endl;
    return false;
}

void logout() {
    if (loggedUserId.empty()) {
        cout << "No user is currently logged in." << endl;
    }
    else {
        cout << "Logged out user: " << loggedUserId << endl;
        loggedUserId = ""; // Reset the logged-in user's User_Id
    }
}

bool changeUserStatus(User* head, string User_Id, string User_Status) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == User_Id) {
            temp->User_Status = User_Status;
            cout << "User Status Changed Successfully." << endl;
            return true;
        }
        temp = temp->next;
    }

    cout << "User with ID " << User_Id << " not found." << endl;
    return false;
}






