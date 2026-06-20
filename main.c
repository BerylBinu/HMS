#include <stdio.h>
#include "director.h"
#include "admin.h"
#include "doctor.h"
#include "nurse.h"
#include "patient.h"



int main() {
    int choice;

    do {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Director\n");
        printf("2. Administrator\n");
        printf("3. Doctor\n");
        printf("4. Nurse\n");
        printf("5. Patient\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                directorLogin();
                break;

            case 2:
                adminLogin();
                break;

            case 3:
                doctorLogin();
                break;

            case 4:
                nurseLogin();
                break;

            case 5:
                patientLogin();
                break;

            case 0:
                printf("Exiting system...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}
