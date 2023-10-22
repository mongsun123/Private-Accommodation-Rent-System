#include "Admin.h"
#include "User.h"
#include "Properties.h"
void adminDashboard(User* user_head, Property* properties) {
	string choice;

	while (true) {
		User* temp = user_head;
		while (temp->prev != nullptr) {
			temp = temp->prev;
		}
		cout << "-------------ADMIN DASHBOARD-------------" << endl;
		cout << "1. Add Manager User " << endl;
		cout << "2. Change User Status (Active and Inactive) " << endl;
		cout << "3. Display Tenants" << endl;
		cout << "4. Display Property" << endl;
		cout << "5. Logout" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == "1") {
			string user_manager_id, user_manager_password, user_manager_name, user_manager_email;
			cout << "Enter Manager ID: ";
			cin >> user_manager_id;
			cout << "Enter Manager Password: ";
			cin >> user_manager_password;
			cout << "Enter Manager Name: ";
			cin >> user_manager_name;
			cout << "Enter Manager Email: ";
			cin >> user_manager_email;
			while (temp != nullptr) {
				if (temp->User_Id == user_manager_id || temp->User_Email == user_manager_email) {
					cout << "Unsuccessfully. The user ID or Email already been taken!" << endl;
					break;
				}
				else if (temp->next == nullptr && temp->User_Id != user_manager_id && temp->User_Email != user_manager_email) {
					addUser(&user_head, user_manager_id, user_manager_password, user_manager_name, user_manager_email, "Admin", "Active");
					cout << "Add manager successfully!" << endl;
					break;
				}
				temp = temp->next;
			}
		}
		else if (choice == "2") {
			string user_id_status_input, user_status_status_input;
			displayUsers(user_head);
			cout << "Which user you want to change the status?: ";
			cin >> user_id_status_input;
			cout << "You want change to? (Active or Inactive): ";
			cin >> user_status_status_input;
			if (changeUserStatus(user_head, user_id_status_input, user_status_status_input) == true) {
				cout << "Change Successfully" << endl << endl;
			}
			/*else{
				cout << "Wrong User ID" << endl << endl;
			}*/
		}
		else if (choice == "3") {
			displayTenantForAdmin(user_head);
		}
		else if (choice == "4") {
			printPropertiesForFilter(properties);
		}
		else if (choice == "5") {
			logout();
			break;
		}
		else {
			cout << "Wrong Input" << endl;
		}
	}
}