#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient.h"

/* ================= UTIL ================= */

void clearBuffer() {
    while (getchar() != '\n');
}

/* ================= LOGIN ================= */
/* File: patients.txt (admin created accounts assumed) */

int patientLogin(char patientID[]) {
    FILE *fp = fopen(FILE_PATIENTS, "r");

    if (!fp) {
        printf("Error opening patients file!\n");
        return 0;
    }

    char fileID[10], name[50], gender[10], illness[50];
    int age;
    char inputID[10];

    printf("Enter Patient ID: ");
    scanf("%s", inputID);

    while (fscanf(fp, "%s %s %s %d %s",
                  fileID, name, gender, &age, illness) != EOF) {

        if (strcmp(fileID, inputID) == 0) {
            strcpy(patientID, fileID);
            fclose(fp);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Login failed!\n");
    return 0;
}

/* ================= MENU ================= */

void patientMenu(char patientID[]) {
    int choice;

    do {
        printf("\n===== PATIENT MENU (%s) =====\n", patientID);
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Reschedule Appointment\n");
        printf("4. Cancel Appointment\n");
        printf("5. Add Payment\n");
        printf("6. View Payments\n");
        printf("7. Search Payments\n");
        printf("8. Add Complaint\n");
        printf("9. View Complaints\n");
        printf("10. Search Complaints\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: bookAppointment(patientID); break;
            case 2: viewAppointments(patientID); break;
            case 3: rescheduleAppointment(patientID); break;
            case 4: cancelAppointment(patientID); break;
            case 5: addPayment(patientID); break;
            case 6: viewPayments(patientID); break;
            case 7: searchPayments(patientID); break;
            case 8: addComplaint(patientID); break;
            case 9: viewComplaints(patientID); break;
            case 10: searchComplaints(patientID); break;
            case 0: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 0);
}

/* ================= APPOINTMENTS ================= */
/* Format: patientID doctorID date time */

void bookAppointment(char patientID[]) {
    FILE *fp = fopen(FILE_APPOINTMENTS, "a");

    if (fp == NULL) {
    printf("Error opening appointments file!\n");
    return;
}

    char doctorID[10], date[20], time[10];

    printf("Enter Doctor ID: ");
    scanf("%s", doctorID);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", date);

    printf("Enter Time (e.g. 3PM): ");
    scanf("%s", time);

    fprintf(fp, "%s %s %s %s\n",
            patientID, doctorID, date, time);

    fclose(fp);

    printf("Appointment booked successfully!\n");
}

/* ================= VIEW APPOINTMENTS ================= */

void viewAppointments(char patientID[]) {
    FILE *fp = fopen(FILE_APPOINTMENTS, "r");
    Appointment app;
    int found = 0;

    if (fp == NULL) {
        printf("No appointments found!\n");
        return;
    }

    printf("\n--- YOUR APPOINTMENTS ---\n");

    while (fscanf(fp, "%s %s %s %s",
                  app.patientID, app.doctorID, app.date, app.time) != EOF) {

        if (strcmp(app.patientID, patientID) == 0) {
            printf("Doctor: %s | Date: %s | Time: %s\n",
                   app.doctorID, app.date, app.time);
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("No appointments found.\n");
    }
}

/* ================= PAYMENTS ================= */
/* Format: patientID amount status */

void viewPayments(char patientID[]) {
    FILE *fp = fopen(FILE_PAYMENTS, "r");

    char pID[10], status[10];
    float amount;

    printf("\n--- YOUR PAYMENTS ---\n");

    while (fscanf(fp, "%s %f %s",
                  pID, &amount, status) != EOF) {

        if (strcmp(pID, patientID) == 0) {
            printf("Amount: %.2f | Status: %s\n",
                   amount, status);
        }
    }

    fclose(fp);
}

/* ================= COMPLAINTS ================= */
/* Format: patientID complaint */

void addComplaint(char patientID[]) {
    FILE *fp = fopen(FILE_COMPLAINTS, "a");

    char complaint[200];

    printf("Enter Complaint: ");
    clearBuffer();
    fgets(complaint, sizeof(complaint), stdin);

    complaint[strcspn(complaint, "\n")] = 0;

    fprintf(fp, "%s %s\n", patientID, complaint);

    fclose(fp);

    printf("Complaint submitted!\n");
}

void viewComplaints(char patientID[]) {
    FILE *fp = fopen(FILE_COMPLAINTS, "r");

    char pID[10];
    char complaint[200];

    printf("\n--- YOUR COMPLAINTS ---\n");

    while (fscanf(fp, "%s %[^\n]",
                  pID, complaint) != EOF) {

        if (strcmp(pID, patientID) == 0) {
            printf("%s\n", complaint);
        }
    }

    fclose(fp);
}


/* ================= RESCHEDULE APPOINTMENTS================= */

void rescheduleAppointment(char patientID[]) {
    FILE *fp = fopen(FILE_APPOINTMENTS, "r");
    FILE *temp = fopen("temp.txt", "w");

    char pID[10], dID[10], date[20], time[10];
    char oldDate[20], oldTime[10];
    char newDate[20], newTime[10];
    int found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter appointment date to reschedule: ");
    scanf("%s", oldDate);

    printf("Enter appointment time to reschedule: ");
    scanf("%s", oldTime);

    while (fscanf(fp, "%s %s %s %s", pID, dID, date, time) != EOF) {
        if (strcmp(pID, patientID) == 0 &&
            strcmp(date, oldDate) == 0 &&
            strcmp(time, oldTime) == 0) {

            printf("Enter new date: ");
            scanf("%s", newDate);

            printf("Enter new time: ");
            scanf("%s", newTime);

            fprintf(temp, "%s %s %s %s\n", pID, dID, newDate, newTime);
            found = 1;
        } else {
            fprintf(temp, "%s %s %s %s\n", pID, dID, date, time);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_APPOINTMENTS);
    rename("temp.txt", FILE_APPOINTMENTS);

    if (found) {
        printf("Appointment rescheduled successfully!\n");
    } else {
        printf("Appointment not found!\n");
    }
}

/* ================= CANCEL APPOINTMENTS================= */

void cancelAppointment(char patientID[]) {
    FILE *fp = fopen(FILE_APPOINTMENTS, "r");
    FILE *temp = fopen("temp.txt", "w");

    char pID[10], dID[10], date[20], time[10];
    char cancelDate[20], cancelTime[10];
    int found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter appointment date to cancel: ");
    scanf("%s", cancelDate);

    printf("Enter appointment time to cancel: ");
    scanf("%s", cancelTime);

    while (fscanf(fp, "%s %s %s %s", pID, dID, date, time) != EOF) {
        if (strcmp(pID, patientID) == 0 &&
            strcmp(date, cancelDate) == 0 &&
            strcmp(time, cancelTime) == 0) {

            found = 1;
        } else {
            fprintf(temp, "%s %s %s %s\n", pID, dID, date, time);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_APPOINTMENTS);
    rename("temp.txt", FILE_APPOINTMENTS);

    if (found) {
        printf("Appointment cancelled successfully!\n");
    } else {
        printf("Appointment not found!\n");
    }
}

/* ================= ADD PAYMENT ================= */

void addPayment(char patientID[]) {
    FILE *fp = fopen(FILE_PAYMENTS, "a");

    float amount;

    if (fp == NULL) {
        printf("Error opening payments file!\n");
        return;
    }

    printf("Enter payment amount: ");
    scanf("%f", &amount);

    fprintf(fp, "%s %.2f PAID\n", patientID, amount);

    fclose(fp);

    printf("Payment added successfully!\n");
}



void searchPayments(char patientID[]) {
    FILE *fp = fopen(FILE_PAYMENTS, "r");

    char pID[10], status[10];
    float amount;
    float searchAmount;
    int found = 0;

    if (fp == NULL) {
        printf("No payments found!\n");
        return;
    }

    printf("Enter amount to search: ");
    scanf("%f", &searchAmount);

    while (fscanf(fp, "%s %f %s", pID, &amount, status) != EOF) {
        if (strcmp(pID, patientID) == 0 && amount == searchAmount) {
            printf("Amount: %.2f | Status: %s\n", amount, status);
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Payment not found!\n");
    }
}

void searchComplaints(char patientID[]) {
    FILE *fp = fopen(FILE_COMPLAINTS, "r");

    char pID[10];
    char complaint[200];
    char keyword[50];
    int found = 0;

    if (fp == NULL) {
        printf("No complaints found!\n");
        return;
    }

    printf("Enter complaint keyword to search: ");
    scanf("%s", keyword);

    while (fscanf(fp, "%s %[^\n]", pID, complaint) != EOF) {
        if (strcmp(pID, patientID) == 0 && strstr(complaint, keyword) != NULL) {
            printf("%s\n", complaint);
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Complaint not found!\n");
    }
}


