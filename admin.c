#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

void clearInputBuffer() {
    while(getchar() != '\n');
}

void adminLogin() {
    char username[20], password[20];

    printf("===== ADMIN LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if(strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("\nLogin Successful!\n");
        adminMenu();
    } else {
        printf("\nInvalid Login Credentials!\n");
    }
}

void registerUser() {
    FILE *file = fopen("users.txt", "a");
    User user;

    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n===== REGISTER NEW USER =====\n");
    printf("Enter Role (Patient/Doctor/Nurse): ");
    scanf("%s", user.role);

    printf("Enter ID: ");
    scanf("%s", user.id);

    printf("Enter Name: ");
    clearInputBuffer();
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &user.age);

    printf("Enter Gender: ");
    scanf("%s", user.gender);

    printf("Enter Contact: ");
    scanf("%s", user.contact);

    fprintf(file, "%s|%s|%s|%d|%s|%s\n",
            user.role,
            user.id,
            user.name,
            user.age,
            user.gender,
            user.contact);

    fclose(file);

    printf("\nUser Registered Successfully!\n");
}

void viewStaffReport() {
    FILE *file = fopen("users.txt", "r");
    User user;

    if(file == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n===== DOCTOR & NURSE STAFF REPORT =====\n");

    while(fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^\n]\n",
                 user.role,
                 user.id,
                 user.name,
                 &user.age,
                 user.gender,
                 user.contact) != EOF) {

        if(strcmp(user.role, "Doctor") == 0 || strcmp(user.role, "Nurse") == 0) {
            printf("\nRole: %s\nID: %s\nName: %s\nAge: %d\nGender: %s\nContact: %s\n",
                   user.role, user.id, user.name, user.age, user.gender, user.contact);
        }
    }

    fclose(file);
}

void searchStaff() {
    FILE *file = fopen("users.txt", "r");
    User user;
    char searchID[20];
    int found = 0;

    if(file == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Staff ID to Search: ");
    scanf("%s", searchID);

    while(fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^\n]\n",
                 user.role,
                 user.id,
                 user.name,
                 &user.age,
                 user.gender,
                 user.contact) != EOF) {

        if((strcmp(user.role, "Doctor") == 0 || strcmp(user.role, "Nurse") == 0)
            && strcmp(user.id, searchID) == 0) {

            printf("\nStaff Found:\n");
            printf("Role: %s\nID: %s\nName: %s\nAge: %d\nGender: %s\nContact: %s\n",
                   user.role, user.id, user.name, user.age, user.gender, user.contact);

            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Staff not found.\n");
    }

    fclose(file);
}

void viewComplaints() {
    FILE *file = fopen("complaints.txt", "r");
    Complaint complaint;

    if(file == NULL) {
        printf("No complaints found.\n");
        return;
    }

    printf("\n===== PATIENT COMPLAINT REPORT =====\n");

    while(fscanf(file, "%[^|]|%[^|]|%[^\n]\n",
                 complaint.complaintID,
                 complaint.patientID,
                 complaint.complaintText) != EOF) {

        printf("\nComplaint ID: %s\nPatient ID: %s\nComplaint: %s\n",
               complaint.complaintID,
               complaint.patientID,
               complaint.complaintText);
    }

    fclose(file);
}

void searchComplaints() {
    FILE *file = fopen("complaints.txt", "r");
    Complaint complaint;
    char patientID[20];
    int found = 0;

    if(file == NULL) {
        printf("No complaints found.\n");
        return;
    }

    printf("Enter Patient ID to Search Complaint: ");
    scanf("%s", patientID);

    while(fscanf(file, "%[^|]|%[^|]|%[^\n]\n",
                 complaint.complaintID,
                 complaint.patientID,
                 complaint.complaintText) != EOF) {

        if(strcmp(complaint.patientID, patientID) == 0) {
            printf("\nComplaint Found:\n");
            printf("Complaint ID: %s\nPatient ID: %s\nComplaint: %s\n",
                   complaint.complaintID,
                   complaint.patientID,
                   complaint.complaintText);

            found = 1;
        }
    }

    if(!found) {
        printf("No complaint found for this patient.\n");
    }

    fclose(file);
}

void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Register New User\n");
        printf("2. View Doctor & Nurse Staff Report\n");
        printf("3. Search Staff\n");
        printf("4. View Patient Complaints\n");
        printf("5. Search Patient Complaints\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                registerUser();
                break;
            case 2:
                viewStaffReport();
                break;
            case 3:
                searchStaff();
                break;
            case 4:
                viewComplaints();
                break;
            case 5:
                searchComplaints();
                break;
            case 6:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 6);
}

int main() {
    adminLogin();
    return 0;
}