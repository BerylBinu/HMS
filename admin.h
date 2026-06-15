#ifndef ADMIN_H
#define ADMIN_H

#define MAX 100
typedef struct {
    char id[20];
    char name[50];
    char password[20];
} Admin;

typedef struct {
    char id[20];
    char name[50];
    char specialty[50];
    char password[20];
} Doctor;

typedef struct {
    char id[20];
    char name[50];
    char department[50];
    char password[20];
} Nurse;

typedef struct {
    char id[20];
    char name[50];
    char gender[10];
    int age;
    char illness[50];
} Patient;

typedef struct {
    char patientID[20];
    char complaintText[100];
} Complaint;

/* Function Prototypes */
void clearInputBuffer();
void adminLogin();
void registerUser();
void adminViewStaffReport();
void searchStaff();
void viewComplaints();
void searchComplaints();
void adminMenu();

#endif
