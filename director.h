#ifndef DIRECTOR_H
#define DIRECTOR_H

// LOGIN
void directorLogin();

// MAIN MENU
void directorMenu();

// SUB MENUS
void manageAdministratorMenu();
void staffReportMenu();
void salesReportMenu();

// MANAGE ADMINISTRATOR FUNCTIONS
void addAdministrator();
void searchAdministrator();
void viewAdministrators();

// STAFF REPORT FUNCTIONS
void searchStaffReport();
void directorViewStaffReport();

// SALES REPORT FUNCTIONS
void searchSalesReport();
void viewSalesReport();

#endif
