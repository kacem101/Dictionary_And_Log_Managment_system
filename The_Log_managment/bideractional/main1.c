#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include"bilist.h"

int main() {
    BLogEntry* L = NULL;
    int choice, sub_choice;
    int size, id, pos, tar,current=1;

    while (1) {
        // Main menu
        printf("\n=== Log Management System ===\n");
        printf("1. Log Creation\n");
        printf("2. Log Deletion\n");
        printf("3. Log Display & Navigation\n");
        printf("4. Log Sorting\n");
        printf("5. System Operations\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1: // Log Creation
                printf("\n--- Log Creation ---\n");
                printf("1. Generate multiple logs\n");
                printf("2. Add a new log at the beginning\n");
                printf("3. Add a new log at the end\n");
                printf("4. Insert a new log at specific position\n");
                printf("5. Back to main menu\n");
                printf("Enter sub-choice: ");
                
                scanf("%d", &sub_choice);
                while (getchar() != '\n');
                
                switch (sub_choice) {
                    case 1:
                        printf("Enter the number of logs to generate: ");
                        scanf("%d", &size);
                        while (getchar() != '\n');
                        GenLogBI(&L, size);
                        break;
                    case 2:
                        AddBLogEntryAtTheBeginning(&L);
                        break;
                    case 3:
                        AddBLogEntryAtTheEndBI(&L);
                        break;
                    case 4:
                        printf("Enter the position: ");
                        scanf("%d", &pos);
                        while (getchar() != '\n');
                        InsertBLogEntryBI(&L, pos);
                        break;
                    case 5:
                        break;
                    default:
                        printf("Invalid sub-choice!\n");
                }
                break;
                
            case 2: // Log Deletion
                printf("\n--- Log Deletion ---\n");
                printf("1. Delete a log by ID\n");
                printf("2. Delete first log\n");
                printf("3. Delete last log\n");
                printf("4. Delete log by timestamp\n");
                printf("5. Delete log by position\n");
                printf("6. Back to main menu\n");
                printf("Enter sub-choice: ");
                
                scanf("%d", &sub_choice);
                while (getchar() != '\n');
                
                switch (sub_choice) {
                    case 1:
                        printf("Enter the ID of the log to delete: ");
                        scanf("%d", &id);
                        while (getchar() != '\n');
                        DelBLogEntryByID(&L, id);
                        break;
                    case 2:
                        DelBLogAtTheBeginning(&L);
                        break;
                    case 3:
                        DelBLogAtTheEnd(&L);
                        break;
                    case 4:
                        DelBLogByTimeStamp(&L);
                        break;
                    case 5:
                        printf("Enter position to delete: ");
                        scanf("%d", &pos);
                        while (getchar() != '\n');
                        DelBLogByPos(&L, pos);
                        break;
                    case 6:
                        break;
                    default:
                        printf("Invalid sub-choice!\n");
                }
                break;
                
            case 3: // Log Display & Navigation
                printf("\n--- Log Display & Navigation ---\n");
                printf("1. Display all logs\n");
                printf("2. Search log by ID\n");
                printf("3. Navigate forward\n");
                printf("4. Navigate backward\n");
                printf("5. Return to the Begining\n");
                printf("6. Serch By Key Word\n");
                printf("7. Back to main menu\n");
                printf("Enter sub-choice: ");
                
                scanf("%d", &sub_choice);
                while (getchar() != '\n');
                
                switch (sub_choice) {
                    case 1:
                        DisplayBLogs(L, current);
                        break;
                    case 2:
                        printf("Enter the target ID: ");
                        scanf("%d", &tar);
                        while (getchar() != '\n');
                        serchLogById(L, tar);
                        break;
                    case 3:
                        MoveForward(L,&current);
                        break;
                    case 4:
                        MoveBackward(L,&current);
                        break;
                    case 5:
                        ReturnToBegining(L,&current);
                        break;
                    case 6:
                        SerchByKeyWord(L);
                        break;
                    case 7:

                        break;
                    default:
                        printf("Invalid sub-choice!\n");
                }
                break;
                
            case 4: // Log Sorting
                printf("\n--- Log Sorting ---\n");
                printf("1. Sort logs by ID\n");
                printf("2. Sort logs by severity\n");
                printf("3. Reverse logs\n");
                printf("4. Back to main menu\n");
                printf("Enter sub-choice: ");
                
                scanf("%d", &sub_choice);
                while (getchar() != '\n');
                
                switch (sub_choice) {
                    case 1:
                        L=SortLogsByIdBI(L, BLogSize(L));
                        printf("Logs sorted by ID.\n");
                        break;
                    case 2:
                        SortBySeverityBI(&L);
                        printf("Logs sorted by severity.\n");
                        break;
                    case 3:
                        ReverseLogsBI(&L);
                        printf("Logs reversed.\n");
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid sub-choice!\n");
                }
                break;
                
            case 5: // System Operations
                printf("\n--- System Operations ---\n");
                printf("1. Get number of logs\n");
                printf("2. Clear all logs\n");
                printf("3. Back to main menu\n");
                printf("Enter sub-choice: ");
                
                scanf("%d", &sub_choice);
                while (getchar() != '\n');
                
                switch (sub_choice) {
                    case 1:
                        printf("Number of logs: %d\n", BLogSize(L));
                        break;
                    case 2:
                        while (L != NULL) {
                            BLogEntry* temp = L;
                            L = L->next;
                            free(temp);
                        }
                        printf("All logs cleared.\n");
                        break;
                    case 3:
                        break;
                    default:
                        printf("Invalid sub-choice!\n");
                }
                break;
                
            case 6: // Exit
                while (L != NULL) {
                    BLogEntry* temp = L;
                    L = L->next;
                    free(temp);
                }
                printf("Exiting program...\n");
                exit(0);
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
