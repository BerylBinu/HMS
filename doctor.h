#ifndef DOCTOR_H
#define DOCTOR_H

// Login
void doctorLogin();

// Menu
void doctorMenu(int doctorID);

// Scheduler
void addSchedule(int doctorID);
void viewSchedule(int doctorID);
void searchSchedule(int doctorID);

// Diagnosis
void addDiagnosis();
void viewDiagnosis();
void searchDiagnosis();

#endif
