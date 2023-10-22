#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Tenant.h"
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

void addUser(User** head, string User_Id, string User_Password, string User_Name, string User_Email, string User_Role, string User_Status);
bool verifyExisitingUser(User* head, string User_Id);
void displayUsers(User* head);
void displayAllTenant(User* head);
int displayAllInactiveTenant(User* head);
bool searchTenant(User* head, string uid);
bool deleteTenantByStatus(User* head, string uid);
void deleteUserById(User** head, string User_Id);
void deleteAllUsers(User * head);
bool login(User* head, string User_Id, string User_Password, TenantFavList* favorites, Property* properties);
void logout();
bool changeUserStatus(User* head, string User_Id, string User_Status);
void displayTenantForAdmin(User* head);

#endif