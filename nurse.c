#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nurse.h"

typedef struct
{
    int nurseID;
    char name[50];
    char department[50];
    char password[30];

} Nurse;

typedef struct
{
    int doctorID;
    char day[20];
    char timing[30];

} Schedule;

typedef struct
{
    char item[50];
    int quantity;

} Inventory;

typedef struct
{
    long patientID;
    char note[200];

} DailyNote;


/* ================= LOGIN ================= */

void nurseLogin()
{
    FILE *fp;
    Nurse nurse;

    int id;
    char password[30];
    int found = 0;

    printf("\n===== NURSE LOGIN =====\n");

    printf("Enter Nurse ID: ");
    scanf("%d", &id);

    printf("Enter Password: ");
    scanf("%s", password);

    fp = fopen("nurses.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open nurses.txt\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %s",
                  &nurse.nurseID,
                  nurse.name,
                  nurse.department,
                  nurse.password) != EOF)
    {
        if (nurse.nurseID == id &&
            strcmp(nurse.password, password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
    {
        printf("Login Successful!\n");
        nurseMenu();
    }
    else
    {
        printf("Invalid ID or Password.\n");
    }
}


/* ================= MENU ================= */

void nurseMenu()
{
    int choice;

    do
    {
        printf("\n===== NURSE MENU =====\n");
        printf("1. View Doctor Schedule\n");
        printf("2. Add Inventory\n");
        printf("3. View Inventory\n");
        printf("4. Search Inventory\n");
        printf("5. Add Daily Note\n");
        printf("6. View Daily Notes\n");
        printf("7. Search Daily Notes\n");
        printf("0. Logout\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewDoctorSchedule();
                break;

            case 2:
                addInventory();
                break;

            case 3:
                viewInventory();
                break;

            case 4:
                searchInventory();
                break;

            case 5:
                addDailyNote();
                break;

            case 6:
                viewDailyNotes();
                break;

            case 7:
                searchDailyNotes();
                break;

            case 0:
                printf("Logged Out.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while (choice != 0);
}


/* ================= SCHEDULE ================= */

void viewDoctorSchedule()
{
    FILE *fp;
    Schedule schedule;
    int found = 0;

    fp = fopen("schedules.txt", "r");

    if (fp == NULL)
    {
        printf("No doctor schedule file found.\n");
        return;
    }

    printf("\n===== DOCTOR SCHEDULES =====\n");

    while (fscanf(fp, "%d %s %s",
                  &schedule.doctorID,
                  schedule.day,
                  schedule.timing) == 3)
    {
        printf("-----------------------------\n");
        printf("Doctor ID : %d\n", schedule.doctorID);
        printf("Day       : %s\n", schedule.day);
        printf("Time      : %s\n", schedule.timing);

        found = 1;
    }

    if (found == 0)
    {
        printf("No doctor schedules available.\n");
    }

    printf("-----------------------------\n");

    fclose(fp);
}


/* ================= INVENTORY ================= */

void addInventory()
{
    FILE *fp;
    Inventory item;

    fp = fopen("inventory.txt", "a");

    if (fp == NULL)
    {
        printf("Unable to open inventory.txt\n");
        return;
    }

    printf("\n===== ADD INVENTORY =====\n");

    printf("Enter Item Name: ");
    scanf("%s", item.item);

    do
    {
        printf("Enter Quantity: ");
        scanf("%d", &item.quantity);

        if (item.quantity < 0)
        {
            printf("Quantity cannot be negative.\n");
        }

    } while (item.quantity < 0);

    fprintf(fp, "%s %d\n", item.item, item.quantity);

    fclose(fp);

    printf("\nInventory Added Successfully.\n");
    printf("Item Name : %s\n", item.item);
    printf("Quantity  : %d\n", item.quantity);

    if (item.quantity <= 5)
    {
        printf("Status    : Low Stock\n");
    }
    else
    {
        printf("Status    : Available\n");
    }
}

void viewInventory()
{
    FILE *fp;
    Inventory item;
    int found = 0;

    fp = fopen("inventory.txt", "r");

    if (fp == NULL)
    {
        printf("No inventory file found.\n");
        return;
    }

    printf("\n===== MEDICAL AND SUPPLIES INVENTORY =====\n");

    while (fscanf(fp, "%s %d",
                  item.item,
                  &item.quantity) == 2)
    {
        printf("-----------------------------\n");
        printf("Item Name : %s\n", item.item);
        printf("Quantity  : %d\n", item.quantity);

        if (item.quantity <= 5)
        {
            printf("Status    : Low Stock\n");
        }
        else
        {
            printf("Status    : Available\n");
        }

        found = 1;
    }

    if (found == 0)
    {
        printf("No inventory items available.\n");
    }

    printf("-----------------------------\n");

    fclose(fp);
}

void searchInventory()
{
    FILE *fp;
    Inventory item;

    char searchItem[50];
    int found = 0;

    printf("Enter Item Name: ");
    scanf("%s", searchItem);

    fp = fopen("inventory.txt", "r");

    if (fp == NULL)
    {
        printf("No inventory file found.\n");
        return;
    }

    printf("\n===== INVENTORY SEARCH RESULT =====\n");

    while (fscanf(fp, "%s %d",
                  item.item,
                  &item.quantity) == 2)
    {
        if (strcmp(item.item, searchItem) == 0)
        {
            printf("-----------------------------\n");
            printf("Item Name : %s\n", item.item);
            printf("Quantity  : %d\n", item.quantity);

            if (item.quantity <= 5)
            {
                printf("Status    : Low Stock\n");
            }
            else
            {
                printf("Status    : Available\n");
            }

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("Item Not Found.\n");
    }

    printf("-----------------------------\n");

    fclose(fp);
}


/* ================= DAILY NOTES ================= */

void addDailyNote()
{
    FILE *fp;
    DailyNote note;

    fp = fopen("dailynotes.txt", "a");

    if (fp == NULL)
    {
        printf("Unable to open dailynotes.txt\n");
        return;
    }

    printf("\n===== ADD DAILY NOTE =====\n");

    do
    {
        printf("Enter Patient ID: ");
        scanf("%ld", &note.patientID);

        if (note.patientID <= 0)
        {
            printf("Patient ID must be greater than 0.\n");
        }

    } while (note.patientID <= 0);

    getchar();

    do
    {
        printf("Enter Note: ");
        fgets(note.note, sizeof(note.note), stdin);

        note.note[strcspn(note.note, "\n")] = '\0';

        if (strlen(note.note) == 0)
        {
            printf("Note cannot be empty.\n");
        }

    } while (strlen(note.note) == 0);

    fprintf(fp, "%ld|%s\n", note.patientID, note.note);

    fclose(fp);

    printf("\nDaily Note Added Successfully.\n");
    printf("Patient ID : %ld\n", note.patientID);
    printf("Note       : %s\n", note.note);
}

void viewDailyNotes()
{
    FILE *fp;
    DailyNote note;

    fp = fopen("dailynotes.txt", "r");

    if (fp == NULL)
    {
        printf("No daily notes file found yet.\n");
        return;
    }

    printf("\n===== DAILY NOTES =====\n");

    while (fscanf(fp, "%ld|%[^\n]\n",
                  &note.patientID,
                  note.note) == 2)
    {
        printf("-----------------------------\n");
        printf("Patient ID : %ld\n", note.patientID);
        printf("Note       : %s\n", note.note);
    }

    printf("-----------------------------\n");

    fclose(fp);
}


void searchDailyNotes()
{
    FILE *fp;
    DailyNote note;

    long searchID;
    int found = 0;

    printf("\n===== SEARCH DAILY NOTES =====\n");

    do
    {
        printf("Enter Patient ID: ");
        scanf("%ld", &searchID);

        if (searchID <= 0)
        {
            printf("Patient ID must be greater than 0.\n");
        }

    } while (searchID <= 0);

    fp = fopen("dailynotes.txt", "r");

    if (fp == NULL)
    {
        printf("No daily notes file found yet.\n");
        return;
    }

    printf("\n===== SEARCH RESULTS =====\n");

    while (fscanf(fp, "%ld|%[^\n]\n",
                  &note.patientID,
                  note.note) == 2)
    {
        if (note.patientID == searchID)
        {
            printf("-----------------------------\n");
            printf("Patient ID : %ld\n", note.patientID);
            printf("Note       : %s\n", note.note);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No notes found for Patient ID %ld.\n", searchID);
    }

    printf("-----------------------------\n");

    fclose(fp);
}