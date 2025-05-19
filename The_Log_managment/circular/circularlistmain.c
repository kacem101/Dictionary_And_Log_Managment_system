#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "circularlist.h"

int main() {
    LogEntry* logList = NULL; // Circular linked list
    LogStack logStack;         // Array-based stack (static array)
    initLogStack(&logStack); // Initialize the log stack (no capacity parameter needed)

    int choice;
    int size, id, pos, tar;
    char message[100];
    int level;

    while (1) {
        printf("\n=== Log Management System ===\n");
        printf("1. Generate multiple logs (Linked List)\n");
        printf("2. Add a new log at the beginning (Linked List)\n");
        printf("3. Add a new log at the end (Linked List)\n");
        printf("4. Insert a new log at specific position (Linked List)\n");
        printf("5. Display all logs (Linked List)\n");
        printf("6. Delete a log by ID (Linked List)\n");
        printf("7. Delete first log (Linked List)\n");
        printf("8. Delete last log (Linked List)\n");
        printf("9. Delete log by timestamp (Linked List)\n");
        printf("10. Sort logs by ID (Linked List)\n");
        printf("11. Get number of logs (Linked List)\n");
        printf("12. Sort Logs By Severity (Linked List)\n");
        printf("13. Reverse Logs (Linked List)\n");
        printf("14. Search By Id (Linked List)\n");
        printf("15. Push log onto LogStack\n"); // Option for stack
        printf("16. Display LogStack\n");       // Option for stack
        printf("17. Check for 'Cycle' in LogStack Array\n"); // Option for stack cycle check
        printf("18. Add log to Fixed Buffer\n"); // Option for fixed buffer
        printf("19. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter the number of logs to generate: ");
                scanf("%d", &size);
                getchar();
                GenLog(&logList, size);
                break;
            case 2:
                AddLogEntryAtTheBeginning(&logList);
                break;
            case 3:
                AddLogEntryAtTheEnd(&logList);
                break;
            case 4:
                InsertLogEntryByPos(&logList);
                break;
            case 5:
                DisplayLogs(logList);
                break;
            case 6:
                printf("Enter the ID of the log to delete: ");
                scanf("%d", &id);
                getchar();
                DelLogEntryByID(&logList, id);
                break;
            case 7:
                DelLogAtTheBeginning(&logList);
                break;
            case 8:
                DelLogAtTheEnd(&logList);
                break;
            case 9:
                DelLogByTimeStamp(&logList);
                break;
            case 10:
                logList = SortLogsById(logList, LogSize(logList));
                printf("Logs sorted by ID.\n");
                break;
            case 11:
                printf("Number of logs: %d\n", LogSize(logList));
                break;
            case 12:
                SortBySeverity(&logList);
                printf("Logs sorted by severity.\n");
                break;
            case 13:
                ReverseLogs(&logList);
                printf("Logs reversed.\n");
                break;
            case 14:
                printf("Enter the target ID: ");
                scanf("%d", &tar);
                getchar();
                LogEntry* target = serchLogById(logList, tar);
                // You can use the returned 'target' pointer here if needed
                break;
            case 15: // Push log onto LogStack
                printf("Enter message for LogStack: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; // Remove newline
                printf("Enter level for LogStack (integer): ");
                scanf("%d", &level);
                getchar();
                if (pushLog(&logStack, message, level)) {
                    printf("Log pushed onto LogStack.\n");
                } else {
                    printf("Failed to push log onto LogStack (Stack might be full).\n");
                }
                break;
            case 16: // Display LogStack
                displayLogStack(&logStack);
                break;
            case 17: // Check for 'Cycle' in LogStack Array
                if (hasCycle(&logStack)) {
                    printf("LogStack array contains a 'cycle' (revisited memory address).\n");
                } else {
                    printf("LogStack array does not contain a 'cycle'.\n");
                }
                break;
            case 18: // Add log to Fixed Buffer
                 printf("Enter message for Fixed Buffer: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; // Remove newline
                printf("Enter level for Fixed Buffer (integer): ");
                scanf("%d", &level);
                getchar();
                addToFixedBuffer(message, level);
                printf("Log added to fixed buffer.\n");
                break;
            case 19: // Exit

                freeLogList(logList);

                freeFixedBuffer();

                printf("Exiting program and freeing memory...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

