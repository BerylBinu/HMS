#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"

struct Doctor {
    int doctorID;
    char name[50];
    char specialty[50];
    char password[30];
};

void doctorMenu(int doctorID);
void addSchedule(int doctorID);
void viewSchedule(int doctorID);
void searchSchedule(int doctorID);
void addDiagnosis();
void viewDiagnosis();
void searchDiagnosis();

void doctorLogin() {

    FILE *file;

    int inputID;
    int doctorID;

    char password[50];
    char savedPassword[50];

    char name[50];
    char specialty[50];

    int found = 0;
    int attempts = 0;

    const int MAX_ATTEMPTS = 3;

    file = fopen("doctors.txt", "r");

    if(file == NULL) {

        printf("Doctors file not found.\n");
        return;
    }

    printf("\n===== DOCTOR LOGIN =====\n");

    while(attempts < MAX_ATTEMPTS && !found) {

        printf("Enter Doctor ID: ");
        scanf("%d", &inputID);

        printf("Enter Password: ");
        scanf("%s", password);

        rewind(file);

        while(fscanf(file,
                     "%d %s %s %s",
                     &doctorID,
                     name,
                     specialty,
                     savedPassword) != EOF) {

            if(inputID == doctorID &&
               strcmp(password, savedPassword) == 0) {

                found = 1;
                break;
            }
        }

        if(!found) {

            attempts++;

            if(attempts < MAX_ATTEMPTS) {

                printf("Invalid ID or Password! (%d/%d attempts)\n",
                       attempts,
                       MAX_ATTEMPTS);
            }
        }
    }

    fclose(file);

    if(found) {

        printf("\nLogin Successful!\n");
        printf("Welcome Dr. %s (%s)\n",
               name,
               specialty);

        doctorMenu(inputID);
    }
    else {

        printf("\nToo many failed attempts. Access denied.\n");
    }
}

void doctorMenu(int doctorID) {
    int choice;

    do {
        printf("\n===== DOCTOR MENU =====\n");
        printf("1. Add Schedule\n");
        printf("2. View Schedule\n");
        printf("3. Search Schedule\n");
        printf("4. Add Diagnosis\n");
        printf("5. View Diagnosis Report\n");
        printf("6. Search Diagnosis Report\n");
        printf("0. Logout\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addSchedule(doctorID);
                break;

            case 2:
                viewSchedule(doctorID);
                break;

            case 3:
                searchSchedule(doctorID);
                break;

            case 4:
                addDiagnosis();
                break;

            case 5:
                viewDiagnosis();
                break;

            case 6:
                searchDiagnosis();
                break;

            case 0:
                printf("Logged out successfully.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 0);
}

void addSchedule(int doctorID) {
    FILE *fp;
    char day[20];
    char timing[30];

    fp = fopen("schedules.txt", "a");

    if(fp == NULL) {
        printf("File error.\n");
        return;
    }

    printf("\nEnter Day: ");
    scanf("%s", day);

    printf("Enter Timing (Example 9AM-1PM): ");
    scanf("%s", timing);

    fprintf(fp, "%d %s %s\n",
            doctorID,
            day,
            timing);

    fclose(fp);

    printf("Schedule added successfully.\n");
}

void viewSchedule(int doctorID) {
    FILE *fp;
    int id;
    char day[20];
    char timing[30];

    fp = fopen("schedules.txt", "r");

    if(fp == NULL) {
        printf("No schedules found.\n");
        return;
    }

    printf("\n===== MY SCHEDULES =====\n");

    while(fscanf(fp, "%d %s %s",
                 &id,
                 day,
                 timing) != EOF) {

        if(id == doctorID) {
            printf("Day: %-10s Time: %s\n",
                   day,
                   timing);
        }
    }

    fclose(fp);
}

void searchSchedule(int doctorID) {
    FILE *fp;
    int id;
    char day[20];
    char timing[30];
    char searchDay[20];
    int found = 0;

    printf("Enter day to search: ");
    scanf("%s", searchDay);

    fp = fopen("schedules.txt", "r");

    if(fp == NULL) {
        printf("File not found.\n");
        return;
    }

    while(fscanf(fp, "%d %s %s",
                 &id,
                 day,
                 timing) != EOF) {

        if(id == doctorID &&
           strcmp(day, searchDay) == 0) {

            printf("Found: %s %s\n",
                   day,
                   timing);

            found = 1;
        }
    }

    fclose(fp);

    if(!found) {
        printf("Schedule not found.\n");
    }
}

void addDiagnosis() {
    FILE *fp;
    int patientID;
    char diagnosis[100];
    char treatment[100];

    fp = fopen("diagnosis.txt", "a");

    if(fp == NULL) {
        printf("File error.\n");
        return;
    }

    printf("Patient ID: ");
    scanf("%d", &patientID);

    printf("Diagnosis: ");
    scanf("%s", diagnosis);

    printf("Treatment: ");
    scanf("%s", treatment);

    fprintf(fp,
            "%d %s %s\n",
            patientID,
            diagnosis,
            treatment);

    fclose(fp);

    printf("Diagnosis recorded successfully.\n");
}

void viewDiagnosis() {
    FILE *fp;
    int patientID;
    char diagnosis[100];
    char treatment[100];

    fp = fopen("diagnosis.txt", "r");

    if(fp == NULL) {
        printf("No diagnosis records found.\n");
        return;
    }

    printf("\n===== DIAGNOSIS REPORT =====\n");

    while(fscanf(fp,
                 "%d %s %s",
                 &patientID,
                 diagnosis,
                 treatment) != EOF) {

        printf("Patient ID: %d\n",
               patientID);

        printf("Diagnosis : %s\n",
               diagnosis);

        printf("Treatment : %s\n\n",
               treatment);
    }

    fclose(fp);
}

void searchDiagnosis() {
    FILE *fp;
    int patientID;
    int searchID;
    char diagnosis[100];
    char treatment[100];
    int found = 0;

    printf("Enter Patient ID: ");
    scanf("%d", &searchID);

    fp = fopen("diagnosis.txt", "r");

    if(fp == NULL) {
        printf("File error.\n");
        return;
    }

    while(fscanf(fp,
                 "%d %s %s",
                 &patientID,
                 diagnosis,
                 treatment) != EOF) {

        if(patientID == searchID) {

            printf("\nPatient ID: %d\n",
                   patientID);

            printf("Diagnosis : %s\n",
                   diagnosis);

            printf("Treatment : %s\n",
                   treatment);

            found = 1;
        }
    }

    fclose(fp);

    if(!found) {
        printf("No record found.\n");
    }
}