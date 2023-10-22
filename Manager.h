#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include "Tenant.h"

#include <iostream>
#include <string>
#include <unordered_map> 
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

void managerDashboard(User* head, TenantFavList* favorites);
void summarizeTopFavoriteProperties(TenantFavList* favorites);
void managePayment(TenantFavList* favorites);
void manageTenancyProcess(TenantFavList* favorites);

#endif 
