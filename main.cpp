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

// For User Login
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

// Function to display all users in the linked list
void displayUsers(User* head) {
    User* temp = head;
    while (temp != nullptr) {
        cout << "User ID: " << temp->User_Id << endl;
        cout << "Name: " << temp->User_Name << endl;
        cout << "Email: " << temp->User_Email << endl;
        cout << "Role: " << temp->User_Role << endl;
        cout << "Status: " << temp->User_Status << endl;
        cout << "----------------------" << endl;
        temp = temp->next;
    }
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

bool login(User* head, string User_Id, string User_Password) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Tenant") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
            return true;
        }elseif (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Manager") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
            return true;
        }elseif (temp->User_Id == User_Id && temp->User_Password == User_Password && temp->User_Status == "Active" && temp->User_Role == "Admin") {
            cout << "Login Successful!" << endl;
            loggedUserId = User_Id; // Set the logged-in user's User_Id
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

int main() {
    User* head = new User;
    head = nullptr;

    string user_id_input;
    string user_password_input;
    
    // Example usage:
    addUser(&head, "u123", "password123", "John Doe", "john@example.com", "Tenant", "Active");
    addUser(&head, "u456", "securepass", "Jane Smith", "june@example.com", "Admin", "Active");
    addUser(&head, "u789", "12345678", "Bob Johnson", "bob@example.com", "Manager", "Inactive");
    
    cout << "Enter Username: ";
    cin >> user_id_input;
    cout << "Enter Password: ";
    cin >> user_password_input;

    login(user_id_input, user_password_input);
    logout();

    cout << "Before deletion:" << endl;
    displayUsers(head);

    // Example usage of deleting a specific user by User_Id
    deleteUserById(&head, "u456");

    // Example usage of changing user status
    changeUserStatus(head, "u123", "Inactive"); // This should display "User Status Changed Successfully."


    cout << "After deletion:" << endl;
    displayUsers(head);

    // Example usage of login function
    login(head, "u123", "password123"); // This should display "Login Successful!"
    login(head, "u456", "wrongpass");   // This should display "Login Failed."


    // Don't forget to free the memory after you're done using the linked list
    deleteAllUsers(head);

   // return 0;
}
