/*============================================================
 * FILE: main.c
 * PURPOSE: Entry point for the Hospital Management System
 *          Shows the main menu and routes to each role.
 *
 * HOW TO COMPILE (in terminal / command prompt):
 *   gcc main.c director.c -o hms
 *
 * HOW TO RUN:
 *   Windows : hms.exe
 *   Linux   : ./hms
 *
 * NOTE FOR YOUR GROUP:
 *   Each person should add their own #include and their own
 *   login/menu call in the switch statement below.
 *   e.g. #include "admin.h", #include "patient.h" etc.
 *============================================================*/

#include <stdio.h>
#include "director.h"

/* TODO (group members): uncomment these when your files are ready */
/* #include "admin.h"   */
/* #include "patient.h" */
/* #include "doctor.h"  */
/* #include "nurse.h"   */

/*------------------------------------------------------------
 * printMainMenu()
 * PURPOSE: Displays the main login menu
 *------------------------------------------------------------*/
void printMainMenu(void) {
    printf("\n");
    printf("============================================\n");
    printf("    HOSPITAL MANAGEMENT SYSTEM (HMS)\n");
    printf("============================================\n");
    printf("  1. Director Login\n");
    printf("  2. Administrator Login\n");
    printf("  3. Patient Login\n");
    printf("  4. Doctor Login\n");
    printf("  5. Nurse Login\n");
    printf("  6. Exit Application\n");
    printf("============================================\n");
    printf("  Enter your choice: ");
}

/*------------------------------------------------------------
 * main()
 * PURPOSE: Program starts here. Shows main menu in a loop.
 *------------------------------------------------------------*/
int main(void) {
    int choice;
    int loginSuccess;

    printf("\n  Welcome to the Hospital Management System\n");

    do {
        printMainMenu();
        scanf("%d", &choice);

        /* clearInputBuffer clears leftover newline from scanf */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {

            case 1:  /* Director */
                loginSuccess = directorLogin();
                if (loginSuccess == 1) {
                    directorMenu();
                }
                break;

            case 2:  /* Administrator */
                /* TODO: Your groupmate's admin module goes here */
                /* loginSuccess = adminLogin();          */
                /* if (loginSuccess) adminMenu();        */
                printf("\n  [Admin module not yet connected]\n");
                break;

            case 3:  /* Patient */
                /* TODO: Your groupmate's patient module goes here */
                printf("\n  [Patient module not yet connected]\n");
                break;

            case 4:  /* Doctor */
                /* TODO: Your groupmate's doctor module goes here */
                printf("\n  [Doctor module not yet connected]\n");
                break;

            case 5:  /* Nurse */
                /* TODO: Your groupmate's nurse module goes here */
                printf("\n  [Nurse module not yet connected]\n");
                break;

            case 6:  /* Exit */
                printf("\n  Thank you for using HMS. Goodbye!\n\n");
                break;

            default:
                printf("\n  Invalid choice. Please enter 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
