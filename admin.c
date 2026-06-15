#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

void clearInputBuffer() {
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}

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


void adminLogin() {
    FILE *file;
    Admin admin;
    char id[20], password[20];
    int found = 0;

    printf("===== ADMIN LOGIN =====\n");
    printf("Admin ID: ");
    scanf("%19s", id);
    printf("Password: ");
    scanf("%19s", password);

    file = fopen("admins.txt", "r");

    if(file == NULL) {
        printf("\nNo administrator records found.\n");
        return;
    }

    while(fscanf(file, "%19s %49s %19s",
                 admin.id, admin.name, admin.password) == 3) {
        if(strcmp(id, admin.id) == 0 &&
           strcmp(password, admin.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if(found) {
        printf("\nLogin Successful!\n");
        printf("Welcome %s\n", admin.name);
        adminMenu();
    } else {
        printf("\nInvalid Login Credentials!\n");
    }
}


void registerUser() {
    int roleChoice;

    printf("\n===== REGISTER USER =====\n");
    printf("1. Doctor\n2. Nurse\n3. Patient\n");
    printf("Enter choice: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 1) {
        FILE *file = fopen("doctors.txt", "a+");
        Doctor d;

        if(file == NULL) {
            printf("File error.\n");
            return;
        }

        printf("Enter ID: ");
        scanf("%19s", d.id);

        printf("Enter Name: ");
        scanf("%49s", d.name);

        printf("Enter Specialty: ");
        scanf("%49s", d.specialty);

        printf("Enter Password: ");
        scanf("%19s", d.password);

        prepareAppend(file);
        fprintf(file, "%s %s %s %s\n",
                d.id, d.name, d.specialty, d.password);

        fclose(file);
        printf("Doctor added successfully!\n");
    }

    else if(roleChoice == 2) {
        FILE *file = fopen("nurses.txt", "a+");
        Nurse n;

        if(file == NULL) {
            printf("File error.\n");
            return;
        }

        printf("Enter ID: ");
        scanf("%19s", n.id);

        printf("Enter Name: ");
        scanf("%49s", n.name);

        printf("Enter Department: ");
        scanf("%49s", n.department);

        printf("Enter Password: ");
        scanf("%19s", n.password);

        prepareAppend(file);
        fprintf(file, "%s %s %s %s\n",
                n.id, n.name, n.department, n.password);

        fclose(file);
        printf("Nurse added successfully!\n");
    }

    else if(roleChoice == 3) {
        FILE *file = fopen("patients.txt", "a+");
        Patient p;

        if(file == NULL) {
            printf("File error.\n");
            return;
        }

        printf("Enter ID: ");
        scanf("%19s", p.id);

        printf("Enter Name: ");
        scanf("%49s", p.name);

        printf("Enter Gender: ");
        scanf("%9s", p.gender);

        printf("Enter Age: ");
        scanf("%d", &p.age);

        printf("Enter Illness: ");
        scanf("%49s", p.illness);

        prepareAppend(file);
        fprintf(file, "%s %s %s %d %s\n",
                p.id, p.name, p.gender, p.age, p.illness);

        fclose(file);
        printf("Patient added successfully!\n");
    }

    else {
        printf("Invalid choice!\n");
    }
}

void adminViewStaffReport(){
    FILE *file;
    Doctor d;
    Nurse n;

    printf("\n===== STAFF REPORT =====\n");

    file = fopen("doctors.txt", "r");
    if(file) {
        printf("\n--- Doctors ---\n");
        while(fscanf(file, "%19s %49s %49s %19s",
                     d.id, d.name, d.specialty, d.password) == 4) {
            printf("%s | %s | %s\n", d.id, d.name, d.specialty);
        }
        fclose(file);
    }

    file = fopen("nurses.txt", "r");
    if(file) {
        printf("\n--- Nurses ---\n");
        while(fscanf(file, "%19s %49s %49s %19s",
                     n.id, n.name, n.department, n.password) == 4) {
            printf("%s | %s | %s\n", n.id, n.name, n.department);
        }
        fclose(file);
    }
}

void searchStaff() {
    char id[20];
    Doctor d;
    Nurse n;

    printf("Enter Staff ID: ");
    scanf("%19s", id);

    FILE *file = fopen("doctors.txt", "r");
    while(file && fscanf(file, "%19s %49s %49s %19s",
                         d.id, d.name, d.specialty, d.password) == 4) {
        if(strcmp(d.id, id) == 0) {
            printf("Doctor Found: %s | %s | %s\n", d.id, d.name, d.specialty);
            fclose(file);
            return;
        }
    }
    if(file) fclose(file);

    file = fopen("nurses.txt", "r");
    while(file && fscanf(file, "%19s %49s %49s %19s",
                         n.id, n.name, n.department, n.password) == 4) {
        if(strcmp(n.id, id) == 0) {
            printf("Nurse Found: %s | %s | %s\n", n.id, n.name, n.department);
            fclose(file);
            return;
        }
    }
    if(file) fclose(file);

    printf("Staff not found.\n");
}

void viewComplaints() {
    FILE *file = fopen("complaints.txt", "r");
    Complaint c;

    printf("\n===== COMPLAINTS =====\n");

    if(!file) {
        printf("No complaints found.\n");
        return;
    }

    while(fscanf(file, "%19s %99s",
                 c.patientID, c.complaintText) == 2) {
        printf("%s | %s\n", c.patientID, c.complaintText);
    }

    fclose(file);
}

void searchComplaints() {
    FILE *file = fopen("complaints.txt", "r");
    Complaint c;
    char id[20];
    int found = 0;

    printf("Enter Patient ID: ");
    scanf("%19s", id);

    if(!file) {
        printf("No complaints found.\n");
        return;
    }

    while(fscanf(file, "%19s %99s",
                 c.patientID, c.complaintText) == 2) {
        if(strcmp(c.patientID, id) == 0) {
            printf("Complaint: %s\n", c.complaintText);
            found = 1;
        }
    }

    fclose(file);

    if(!found) {
        printf("No complaint found.\n");
    }
}


void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Register User\n");
        printf("2. View Staff\n");
        printf("3. Search Staff\n");
        printf("4. View Complaints\n");
        printf("5. Search Complaints\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerUser(); break;
            case 2: adminViewStaffReport(); break;
            case 3: searchStaff(); break;
            case 4: viewComplaints(); break;
            case 5: searchComplaints(); break;
            case 6: printf("Logging out...\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while(choice != 6);
}
