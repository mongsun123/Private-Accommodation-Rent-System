#ifndef TENANT_H
#define TENANT_H

#include "Properties.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

struct TenantFavList {
    string User_Id;
    int Ads_Id;
    string Prop_Name;
    string Size;
    string Monthly_Rent;
    string Completion_year;
    string Location;
    string Property_Type;
    string Payment_Status;
    TenantFavList* back;
    TenantFavList* next;
};

void saveFavoriteProperty(Property* properties, TenantFavList** head, TenantFavList* favorite, int ads_id, string userid);
void displayFavList(TenantFavList* favorites, string userid);
void addToRentFromFav(TenantFavList* favorites, string userid);
void tenantDashboard(TenantFavList* favorites, Property* properties, string userid);
void addFavoriteProperty(Property* properties, TenantFavList** head, int ads_id, string userid);
void displayRentHistory(TenantFavList* favorites, string User_Id);
#endif