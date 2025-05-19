#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include"tree.h"
int main() {
    LogEntry* log_list = NULL; // Linked List root
    BsTLogEntry* log_bst = NULL; // BST root
    int choice;
    int size, id, pos, tar_id;
    char target_timestamp[50];


    while (1) {
        printf("\n=== Log Management System ===\n");
        printf("--- Linked List Operations ---\n");
        printf("1. Generate multiple logs\n");
        printf("2. Add a new log at the beginning\n");
        printf("3. Add a new log at the end\n");
        printf("4. Insert a new log at specific position\n");
        printf("5. Display all logs\n");
        printf("6. Delete a log by ID\n");
        printf("7. Delete first log\n");
        printf("8. Delete last log\n");
        printf("9. Delete log by timestamp\n");
        printf("10. Sort logs by ID\n");
        printf("11. Get number of logs\n");
        printf("12. Sort Logs By Severity\n");
        printf("13. Reverse Logs\n");
        printf("14. Search By Id\n");
        printf("--- Binary Search BsTLogEntry Operations (Timestamp as Key) ---\n");
        printf("15. Convert Linked List to BST\n");
        printf("16. Add a new log directly to BST\n");
        printf("17. Display BST (In-Order Traversal - Sorted by Timestamp)\n");
        printf("18. Display BST (Pre-Order Traversal)\n");
        printf("19. Display BST (Post-Order Traversal)\n");
        printf("20. Delete from BST by Timestamp\n");
        printf("21. Exit\n");
        printf("Enter your choice: ");

        // Input validation for choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue; // Go back to the beginning of the loop
        }
        getchar(); // Consume leftover '\n'

        switch (choice) {
            case 1:
                printf("Enter the number of logs to generate: ");
                 if (scanf("%d", &size) != 1) {
                    printf("Invalid input. Please enter an integer.\n");
                    while (getchar() != '\n');
                    break;
                }
                getchar(); // Consume leftover '\n'
                GenLog(&log_list, size);
                break;
            case 2:
                AddLogEntryAtTheBeginning(&log_list);
                break;
            case 3:
                AddLogEntryAtTheEnd(&log_list);
                break;
            case 4:
                InsertLogEntryByPos(&log_list);
                break;
            case 5:
                DisplayLogs(log_list);
                break;
            case 6:
                printf("Enter the ID of the log to delete: ");
                 if (scanf("%d", &id) != 1) {
                    printf("Invalid input. Please enter an integer for ID.\n");
                     while (getchar() != '\n');
                    break;
                }
                getchar(); // Consume leftover '\n'
                DelLogEntryByID(&log_list, id);
                break;
            case 7:
                DelLogAtTheBeginning(&log_list);
                break;
            case 8:
                DelLogAtTheEnd(&log_list);
                break;
            case 9:
                DelLogByTimeStamp(&log_list);
                break;
            case 10:
                 if (IsLogsEmpty(log_list)) {
                    printf("Log list is empty, nothing to sort by ID.\n");
                } else {
                    // LogSize needs to be called outside SortLogsById because SortLogsById modifies the list structure during sorting
                    int current_size = LogSize(log_list);
                    log_list = SortLogsById(log_list,current_size);
                    printf("Logs sorted by ID.\n");
                }
                break;
            case 11:
                printf("Number of logs: %d\n", LogSize(log_list));
                break;
             case 12:
                SortBySeverity(&log_list);
                break;
            case 13:
                ReverseLogs(&log_list);
                break;
            case 14:
                printf("Enter the target ID to search: ");
                if (scanf("%d", &tar_id) != 1) {
                    printf("Invalid input. Please enter an integer for ID.\n");
                     while (getchar() != '\n');
                    break;
                }
                getchar(); // Consume leftover '\n'
                serchLogById(log_list, tar_id);
                break;
            case 15:
                 if (log_bst != NULL) {
                    printf("BST already exists. Freeing existing BST before conversion.\n");
                }
                log_bst = convertLogEntryToBst(log_list);
                // convertLogEntryToBst already prints success/failure messages
                break;
            case 16:
                 AddLogEntryToBst(&log_bst,CreateBstLogEntry());
                 break;
            case 17:
                 if (log_bst == NULL) {
                    printf("BST is empty.\n");
                } else {
                     printf("\nBST (In-Order Traversal):\n");
                     displayLogHeader(); // Use the same header format
                     PrintBsTLogEntryInOrder(log_bst);
                }
                break;
            case 18:
                if (log_bst == NULL) {
                    printf("BST is empty.\n");
                } else {
                    printf("\nBST (Pre-Order Traversal):\n");
                    displayLogHeader(); // Use the same header format
                    PrintBsTLogEntryPreOrder(log_bst);
                }
                break;
            case 19:
                 if (log_bst == NULL) {
                    printf("BST is empty.\n");
                } else {
                    printf("\nBST (Post-Order Traversal):\n");
                     displayLogHeader(); // Use the same header format
                    PrintBsTLogEntryPostOrder(log_bst);
                }
                break;
             case 20:
                if (log_bst == NULL) {
                    printf("BST is empty, cannot delete.\n");
                } else {
                        int year,month,day,hour,minutes,seconds;
    					char tryAgain;
    					char temp [50];
    					printf("Enter the TimeStamp in this format: 2023-12-25 15:30:45 W. Central Africa Standard Time\n");
    					do {
        					printf("Enter date and time (YYYY MM DD mm ss): ");
        					scanf("%d %d %d %d %d %d", &year, &month, &day,&hour, &minutes, &seconds);
        
        					// Clear input buffer
        					while(getchar() != '\n');
        
        					if (!isValidDateTime(year, month, day,hour, minutes, seconds)) {
            				printf("Invalid input! Please try again.\n");
            				continue;
        					}
        
        					printf("\nYou entered: %04d-%02d-%02d %02d:%02d:%02d\n", 
               						year, month, day,hour, minutes, seconds);
        
        					printf("Do you want to enter another date? (y/n): ");
        					scanf(" %c", &tryAgain);
        
        					// Clear input buffer
        					while(getchar() != '\n');
        
    					} while (tryAgain == 'y' || tryAgain == 'Y');

    					sprintf(temp,"%04d-%02d-%02d %02d:%02d:%02d",year, month, day,hour, minutes, seconds);

                        DelBsTLogEntryNode(&log_bst, temp);
                    }
                
                break;
            case 21:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
