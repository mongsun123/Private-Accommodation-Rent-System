#include "Properties.h"
#include "User.h"
#include "Tenant.h"

int main(){
    User* head = new User;
	head = nullptr;
	string choice;
	string uid, upass,uname,email;

    //InitialValue
    addUser(&head, "u123", "password123", "JohnDoe", "john@example.com", "Tenant", "Active");
    addUser(&head, "u456", "securepass", "JaneSmith", "june@example.com", "Admin", "Active");
    addUser(&head, "u789", "12345678", "BobJohnson", "bob@example.com", "Manager", "Active");
	addUser(&head, "x888", "xxx8888", "JayChou", "jay@example.com", "Tenant", "Inactive");
	addUser(&head, "u999", "12345678", "Natalie", "natalie@example.com", "Tenant", "Active");
	addUser(&head, "x000", "xxx8888", "Nash", "nash@example.com", "Tenant", "Active");
	addUser(&head, "u000", "xxx8888", "Dave", "dave@example.com", "Tenant", "Active");

	//Read CSV
	Property* properties = read_csv("c:/users/user/desktop/mudah-apartment-kl-selangor.csv");	

 
	//TenantFavList
	TenantFavList* favourite = new TenantFavList;
	favourite = nullptr;

	addFavoriteProperty(properties, &favourite, 100203973,"u123");
	addFavoriteProperty(properties, &favourite, 100203973, "u999");
	addFavoriteProperty(properties, &favourite, 100203973, "x000");
	addFavoriteProperty(properties, &favourite, 100203973, "u000");
	addFavoriteProperty(properties, &favourite, 97022692, "u123");
	addFavoriteProperty(properties, &favourite, 97022692, "u999");
	addFavoriteProperty(properties, &favourite, 97022692, "x000");
	addFavoriteProperty(properties, &favourite, 87950203, "x000");
	addFavoriteProperty(properties, &favourite, 87950203, "u000");
	addFavoriteProperty(properties, &favourite, 100321976, "u123");
	addFavoriteProperty(properties, &favourite, 100321976, "u000");
	addFavoriteProperty(properties, &favourite, 99492392, "u000");
	addFavoriteProperty(properties, &favourite, 100321850, "u000");
	addFavoriteProperty(properties, &favourite, 99774637, "u000");
	addFavoriteProperty(properties, &favourite, 98990742, "u000");
	addFavoriteProperty(properties, &favourite, 99174282, "u000");
	addFavoriteProperty(properties, &favourite, 100032198, "u000");

	// Main Menu
	while (true) {
		cout << "Welcome To Private Accommodation Rent System" << endl;
		cout << "1. Login" << endl;
		cout << "2. Register Tenant" << endl;
		cout << "3. Exit" << endl;
		cout << "Please enter your choice: ";
		cin >> choice;
		if (choice == "1") {
			cout << "User ID: ";
			cin >> uid;
			cout << "Password: ";
			cin >> upass;
			login(head, uid, upass, favourite, properties);
		}
		else if (choice == "2") {
			cout << "User ID: ";
			cin >> uid;
			cout << "Password: ";
			cin >> upass;
			cout << "Username: ";
			cin >> uname;
			cout << "Email: ";
			cin >> email;
			if (!verifyExisitingUser) {
				addUser(&head, uid, upass, uname, email, "Tenant", "Active");
			}
			else {
				cout << "User ID existed" << endl;
			}

		}
		else if (choice == "3") {
			break;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}