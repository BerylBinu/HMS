#ifndef DOCTOR_H
#define DOCTOR_H

// Login
void doctorLogin();

// Menu
void doctorMenu(char doctorID[]);

// Scheduler
void addSchedule(char doctorID[]);
void viewSchedule(char doctorID[]);
void searchSchedule(char doctorID[]);

// Diagnosis
void addDiagnosis();
void viewDiagnosis();
void searchDiagnosis();

#endif
