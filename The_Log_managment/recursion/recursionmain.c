#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include<ctype.h>
#include"recursion.h" // Assuming convert function is declared here

// The function signature for infix to postfix conversion (should be in recursion.h)
// void convert(char* infix, char* postfix, int* i, int* j);

int main() {
    LogEntry* L = NULL;
    int choice;
    int size, id, pos,tar;

    while (1) {
        printf("\n=== Log Management System ===\n");
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
        printf("12. Sort Logs By Sev\n");
        printf("13. Reverse Logs\n");
        printf("14. Reverse using recursion\n");
        printf("15. Serch By Id\n");
        printf("16. Find the max Id\n");
        printf("17. Free logs (was part of old 18)\n"); // Updated menu text for old case 17
        printf("18. Turn infix to postfix\n"); // New menu item
        printf("19. Exit\n"); // Updated menu item (was 18)
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter the number of logs to generate: ");
                scanf("%d", &size);
                getchar();
                GenLog(&L, size);
                break;
            case 2:
                AddLogEntryAtTheBeginning(&L);
                break;
            case 3:
                AddLogEntryAtTheEnd(&L);
                break;
            case 4:
                printf("Enter the position: ");
                scanf("%d", &pos);
                getchar();
                InsertLogEntry(&L, pos);
                break;
            case 5:
                DisplayLogs(L);
                break;
            case 6:
                printf("Enter the ID of the log to delete: ");
                scanf("%d", &id);
                getchar();
                DelLogEntryByID(&L, id);
                break;
            case 7:
                DelLogAtTheBeginning(&L);
                break;
            case 8:
                DelLogAtTheEnd(&L);
                break;
            case 9:
                DelLogByTimeStamp(&L);
                break;
            case 10:
                L=SortLogsById(L, LogSize(L));
                printf("Logs sorted by ID.\n");
                break;
            case 11:
                printf("Number of logs: %d\n", LogSize(L));
                break;
            case 12:
                SortBySeverity(&L);
                break;
            case 13:
                ReverseLogs(&L);
                break;
            case 14:
                ReverseWithRecursion(&L);
                break;
            case 15:
                printf("enter the target ID \n");
                scanf("%d",&tar);
                getchar();
                LogEntry*target=serchLogById(L,tar);
                if (target != NULL) {
                    // Assuming there's a function to print a single log entry
                    // printLogEntry(target);
                    printf("Log found with ID %d\n", tar); // Placeholder output
                } else {
                    printf("Log with ID %d not found.\n", tar);
                }
                break;
            case 16:
                int MAX=FindMAxLogId(L);
                printf("MAX LogId : %d \n",MAX);
                break;
            case 17: // This was part of the old case 18 (Exit logic)
                 while (L != NULL) {
                     LogEntry* temp = L;
                     L = L->next;
                     free(temp); // Assuming LogEntry is dynamically allocated
                 }
                 printf("All logs freed.\n");
                 break;

            case 18: // New case for infix to postfix conversion
                { // Use a block to declare variables
                    char infix_expr[100]; // Adjust size as needed
                    char postfix_expr[100]; // Adjust size as needed
                    int i_idx = 0;
                    int j_idx = 0;

                    printf("Enter infix expression: ");
                    // Use fgets to safely read the input string, including spaces
                    fgets(infix_expr, sizeof(infix_expr), stdin);
                    // Remove the newline character that fgets might read
                    infix_expr[strcspn(infix_expr, "\n")] = '\0';

                    // Ensure postfix_expr is null-terminated initially
                    postfix_expr[0] = '\0';

                    // Call the convert function
                    // The actual logic for conversion needs to be implemented in the convert function
                    convert(infix_expr, postfix_expr, &i_idx, &j_idx);

                    printf("Postfix expression: %s\n", postfix_expr);
                }
                break;

            case 19: // Updated from 18 (Exit)
                // You might want to add a check here if logs were freed by case 17
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
