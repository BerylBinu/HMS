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

    if(strcmp(username, ADMIN_USERNAME) == 0 &&
       strcmp(password, ADMIN_PASSWORD) == 0) {

        printf("\nLogin Successful!\n");
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
        FILE *file = fopen("doctors.txt", "a");
        Doctor d;

        printf("Enter ID: ");
        scanf("%s", d.id);

        printf("Enter Name: ");
        clearInputBuffer();
        fgets(d.name, sizeof(d.name), stdin);
        d.name[strcspn(d.name, "\n")] = '\0';

        printf("Enter Specialty: ");
        scanf("%s", d.specialty);

        printf("Enter Password: ");
        scanf("%s", d.password);

        fprintf(file, "%s|%s|%s|%s\n",
                d.id, d.name, d.specialty, d.password);

        fclose(file);
        printf("Doctor added successfully!\n");
    }

    else if(roleChoice == 2) {
        FILE *file = fopen("nurses.txt", "a");
        Nurse n;

        printf("Enter ID: ");
        scanf("%s", n.id);

        printf("Enter Name: ");
        clearInputBuffer();
        fgets(n.name, sizeof(n.name), stdin);
        n.name[strcspn(n.name, "\n")] = '\0';

        printf("Enter Department: ");
        scanf("%s", n.department);

        printf("Enter Password: ");
        scanf("%s", n.password);

        fprintf(file, "%s|%s|%s|%s\n",
                n.id, n.name, n.department, n.password);

        fclose(file);
        printf("Nurse added successfully!\n");
    }

    else if(roleChoice == 3) {
        FILE *file = fopen("patients.txt", "a");
        Patient p;

        printf("Enter ID: ");
        scanf("%s", p.id);

        printf("Enter Name: ");
        clearInputBuffer();
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';

        printf("Enter Gender: ");
        scanf("%s", p.gender);

        printf("Enter Age: ");
        scanf("%d", &p.age);

        printf("Enter Illness: ");
        scanf("%s", p.illness);

        fprintf(file, "%s|%s|%s|%d|%s\n",
                p.id, p.name, p.gender, p.age, p.illness);

        fclose(file);
        printf("Patient added successfully!\n");
    }

    else {
        printf("Invalid choice!\n");
    }
}

void viewStaffReport() {
    FILE *file;
    Doctor d;
    Nurse n;

    printf("\n===== STAFF REPORT =====\n");

    file = fopen("doctors.txt", "r");
    if(file) {
        printf("\n--- Doctors ---\n");
        while(fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
                     d.id, d.name, d.specialty, d.password) == 4) {
            printf("%s | %s | %s\n", d.id, d.name, d.specialty);
        }
        fclose(file);
    }

    file = fopen("nurses.txt", "r");
    if(file) {
        printf("\n--- Nurses ---\n");
        while(fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
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
    scanf("%s", id);

    FILE *file = fopen("doctors.txt", "r");
    while(file && fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
                         d.id, d.name, d.specialty, d.password) == 4) {
        if(strcmp(d.id, id) == 0) {
            printf("Doctor Found: %s | %s | %s\n", d.id, d.name, d.specialty);
            fclose(file);
            return;
        }
    }
    if(file) fclose(file);

    file = fopen("nurses.txt", "r");
    while(file && fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
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

    while(fscanf(file, "%[^|]|%[^\n]\n",
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
    scanf("%s", id);

    if(!file) {
        printf("No complaints found.\n");
        return;
    }

    while(fscanf(file, "%[^|]|%[^\n]\n",
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
            case 2: viewStaffReport(); break;
            case 3: searchStaff(); break;
            case 4: viewComplaints(); break;
            case 5: searchComplaints(); break;
            case 6: printf("Logging out...\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while(choice != 6);
}
