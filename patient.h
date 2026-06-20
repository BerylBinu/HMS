#ifndef PATIENT_H
#define PATIENT_H

#define MAX 100

/* ===== FILES ===== */
#define FILE_PATIENTS "patients.txt"
#define FILE_APPOINTMENTS "appointments.txt"
#define FILE_PAYMENTS "payments.txt"
#define FILE_COMPLAINTS "complaints.txt"

/* ===== STRUCTURES ===== */

typedef struct {
    char patientID[10];
    char name[50];
    char gender[10];
    int age;
    char illness[50];
    char password[20];
} PatientRecord;

typedef struct {
    char patientID[10];
    char doctorID[10];
    char date[20];
    char time[10];
} Appointment;

typedef struct {
    char patientID[10];
    float amount;
    char status[10];
} PaymentRecord;

typedef struct {
    char patientID[10];
    char complaint[200];
} PatientComplaint;

/* ===== LOGIN AND MENU ===== */
void patientLogin();
void patientMenu(char patientID[]);

/* ===== APPOINTMENTS ===== */
void bookAppointment(char patientID[]);
void viewAppointments(char patientID[]);
void rescheduleAppointment(char patientID[]);
void cancelAppointment(char patientID[]);

/* ===== PAYMENTS ===== */
void addPayment(char patientID[]);
void viewPayments(char patientID[]);
void searchPayments(char patientID[]);

/* ===== COMPLAINTS ===== */
void addComplaint(char patientID[]);
void patientViewComplaints(char patientID[]);
void patientSearchComplaints(char patientID[]);

/* ===== UTIL ===== */
void clearBuffer();

#endif
