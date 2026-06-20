#include <stdio.h>
#include <string.h>
#include "director.h"

struct Admin {

    char id[20];
    char name[50];
    char password[50];

};

static void prepareAppend(FILE *file) {
    long size;
    int lastChar;

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    if(size <= 0) {
        return;
    }

    fseek(file, -1, SEEK_END);
    lastChar = fgetc(file);
    fseek(file, 0, SEEK_END);

    if(lastChar != '\n') {
        fprintf(file, "\n");
    }
}

// FUNCTION PROTOTYPES
void manageAdministratorMenu();
void staffReportMenu();
void salesReportMenu();

void directorMenu();
void directorLogin();

void addAdministrator();
void searchAdministrator();
void viewAdministrators();

void searchStaffReport();
void directorViewStaffReport();

void searchSalesReport();
void viewSalesReport();


//--------------------------------------ManageAdministrators-------------------------------------------------------
void manageAdministratorMenu(){
    int choice;

    do {

        printf("\n===== MANAGE ADMINISTRATOR =====\n");

        printf("1. Add Administrator\n");
        printf("2. Search Administrator\n");
        printf("3. View Administrators\n");
        printf("0. Back to Director Menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addAdministrator();
                break;
            case 2:
                searchAdministrator();
                break;
            case 3:
                viewAdministrators();
                break;
            case 0:
                printf("Returning to Director Menu...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while(choice != 0);
}

//adding admins
void addAdministrator() {

    FILE *file;

    struct Admin admin;

    file = fopen("admins.txt", "a+");

    if(file == NULL) {

        printf("File Error!\n");

        return;
    }

    printf("\n===== ADD ADMINISTRATOR =====\n");

    printf("Enter Administrator ID: ");
    scanf("%19s", admin.id);

    while(getchar() != '\n');
    
    printf("Enter Administrator Name: ");
    scanf("%s", admin.name);

    printf("Enter Administrator Password: ");
    scanf("%s", admin.password);

    prepareAppend(file);
    fprintf(file,
            "%s %s %s\n",
            admin.id,
            admin.name,
            admin.password);

    fclose(file);

    printf("\nAdministrator Added Successfully!\n");
}

//search admins
void searchAdministrator() {

    FILE *file;

    struct Admin admin;

    char keyword[50];

    int found = 0;

    file = fopen("admins.txt", "r");

    if(file == NULL) {

        printf("No Administrator Records Found.\n");

        return;
    }

    printf("\n===== SEARCH ADMINISTRATOR =====\n");

    printf("Enter Administrator ID or Name to Search: ");

    scanf("%49s", keyword);

    while(fscanf(file,
           "%19s %49s %49s",
           admin.id,
           admin.name,
           admin.password) == 3) {

        if(strcmp(admin.id, keyword) == 0 ||
           strcmp(admin.name, keyword) == 0) {

            printf("\nAdministrator Found!\n");

            printf("ID: %s\n", admin.id);

            printf("Name: %s\n", admin.name);

            found = 1;

            break;
        }
    }

    if(found == 0) {

        printf("\nAdministrator Not Found.\n");
    }

    fclose(file);
}

//view admins
void viewAdministrators() {

    FILE *file;

    struct Admin admin;

    file = fopen("admins.txt", "r");

    if(file == NULL) {

        printf("No Administrator Records Found.\n");

        return;
    }

    printf("\n===== ADMINISTRATOR LIST =====\n");

    while(fscanf(file,
           "%19s %49s %49s",
           admin.id,
           admin.name,
           admin.password) == 3) {

        printf("\nID: %s\n", admin.id);

        printf("Name: %s\n", admin.name);

        printf("--------------------------\n");
    }

    fclose(file);
}

//--------------------------------------------------staffReportMenu()-------------------------------------------------------------
void staffReportMenu() {
    int choice;

    do {

        printf("\n===== STAFF REPORT =====\n");

        printf("1. Search Staff\n");
        printf("2. View All Staff\n");
        printf("0. Back\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {

            case 1:
                searchStaffReport();
                break;

            case 2:
                directorViewStaffReport();
                break;

            case 0:
                printf("Returning to Director Menu...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);
}

//search staff
void searchStaffReport() {

    FILE *file;

    char line[200];

    char keyword[50];

    int found = 0;

    printf("\n===== SEARCH STAFF REPORT =====\n");

    printf("Enter Name or ID to Search: ");

    scanf("%s", keyword);

    // SEARCH ADMINS
    file = fopen("admins.txt", "r");

    if(file != NULL) {

        while(fgets(line, sizeof(line), file)) {

            if(strstr(line, keyword) != NULL) {

                printf("\n[ADMIN] %s", line);

                found = 1;
            }
        }

        fclose(file);
    }

    // SEARCH DOCTORS
    file = fopen("doctors.txt", "r");

    if(file != NULL) {

        while(fgets(line, sizeof(line), file)) {

            if(strstr(line, keyword) != NULL) {

                printf("\n[DOCTOR] %s", line);

                found = 1;
            }
        }

        fclose(file);
    }

    // SEARCH NURSES
    file = fopen("nurses.txt", "r");

    if(file != NULL) {

        while(fgets(line, sizeof(line), file)) {

            if(strstr(line, keyword) != NULL) {

                printf("\n[NURSE] %s", line);

                found = 1;
            }
        }

        fclose(file);
    }

    if(found == 0) {

        printf("\nNo Staff Record Found.\n");
    }
}

//view staff
void directorViewStaffReport(){

    FILE *file;

    char line[200];

    printf("\n===== ALL STAFF REPORT =====\n");

    // ADMINS
    file = fopen("admins.txt", "r");

    if(file != NULL) {

        printf("\n--- ADMINISTRATORS ---\n");

        while(fgets(line, sizeof(line), file)) {

            printf("%s", line);
        }

        fclose(file);
    }

    // DOCTORS
    file = fopen("doctors.txt", "r");

    if(file != NULL) {

        printf("\n--- DOCTORS ---\n");

        while(fgets(line, sizeof(line), file)) {

            printf("%s", line);
        }

        fclose(file);
    }

    // NURSES
    file = fopen("nurses.txt", "r");

    if(file != NULL) {

        printf("\n--- NURSES ---\n");

        while(fgets(line, sizeof(line), file)) {

            printf("%s", line);
        }

        fclose(file);
    }
}
//-------------------------------------------------------salesReportMenu()---------------------------------------
void salesReportMenu(){
    int choice;

    do {

        printf("\n===== SALES REPORT =====\n");

        printf("1. Search Sales Record\n");
        printf("2. View All Sales Records\n");
        printf("0. Back\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {

            case 1:
                searchSalesReport();
                break;

            case 2:
                viewSalesReport();
                break;

            case 0:
                printf("Returning to Director Menu...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);
}

//Search sales
void searchSalesReport() {

    FILE *file;

    char line[200];

    char keyword[50];

    int found = 0;

    file = fopen("payments.txt", "r");

    if(file == NULL) {

        printf("\nNo Sales Records Found.\n");

        return;
    }

    printf("\n===== SEARCH SALES REPORT =====\n");

    printf("Enter Patient ID or Payment Status: ");

    scanf("%s", keyword);

    while(fgets(line, sizeof(line), file)) {

        if(strstr(line, keyword) != NULL) {

            printf("%s", line);

            found = 1;
        }
    }

    if(found == 0) {

        printf("\nNo Matching Sales Record Found.\n");
    }

    fclose(file);
}

//View sales
void viewSalesReport() {

    FILE *file;

    char line[200];

    file = fopen("payments.txt", "r");

    if(file == NULL) {

        printf("\nNo Sales Records Found.\n");

        return;
    }

    printf("\n===== ALL SALES RECORDS =====\n");

    while(fgets(line, sizeof(line), file)) {

        printf("%s", line);
    }

    fclose(file);
}

//--------------------------------------------------------------MAIN MENU-------------------------------------------------------
void directorMenu(){

    int choice;

    do {

        printf("\n===== DIRECTOR MENU =====\n");

        printf("1. Manage Administrator\n");
        printf("2. Staff Report\n");
        printf("3. Sales Report\n");
        printf("0. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {

            case 1:
                manageAdministratorMenu();
                break;

            case 2:
                staffReportMenu();
                break;

            case 3:
                salesReportMenu();
                break;

            case 0:
                printf("Logging out...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);
}

// LOGIN
void directorLogin() {

    FILE *file;

    char savedUsername[50];
    char savedPassword[50];

    char username[50];
    char password[50];

    int found = 0;

    int attempts = 0;

    const int MAX_ATTEMPTS = 3;

    file = fopen("director.txt", "r");

    // FIRST TIME SETUP
    if(file == NULL) {

        printf("\nNo Director Account Found.\n");

        printf("=== Create New Director Account ===\n");

        file = fopen("director.txt", "w");

        if(file == NULL) {

            printf("File Error!\n");

            return;
        }

        printf("Create Username: ");
        scanf("%s", username);

        printf("Create Password: ");
        scanf("%s", password);

        fprintf(file,
                "%s %s\n",
                username,
                password);

        fclose(file);

        printf("\nAccount Created Successfully!\n");

        printf("Restart the program and login again.\n");

        return;
    }

    // LOGIN SYSTEM
    printf("\n===== DIRECTOR LOGIN =====\n");

    while(attempts < MAX_ATTEMPTS && !found) {

        printf("Enter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        rewind(file);

        while(fscanf(file,
               "%s %s",
               savedUsername,
               savedPassword) != EOF) {

            if(strcmp(username, savedUsername) == 0 &&
               strcmp(password, savedPassword) == 0) {

                found = 1;

                break;
            }
        }

        if(!found) {

            attempts++;

            if(attempts < MAX_ATTEMPTS) {

                printf("\nInvalid Username or Password! (%d/%d attempts)\n",
                       attempts,
                       MAX_ATTEMPTS);
            }
        }
    }

    fclose(file);

    if(found) {

        printf("\nLogin Successful!\n");

        directorMenu();
    }
    else {

        printf("\nToo many failed attempts. Access denied.\n");
    }
}
