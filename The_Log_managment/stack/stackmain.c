#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "stacks.h"

int main() {
    LogStack stack;
    initializeStack(&stack);
    int choice;
    int size, level;
    char message[100];
    LogEntry entry;

    while (1) {
        printf("\n=== Log Stack Management System ===\n");
        printf("1. Push New Log Entry\n");
        printf("2. Pop Log Entry\n");
        printf("3. Peek Top Log Entry\n");
        printf("4. Check Stack Status\n");
        printf("5. Reverse Stack\n");
        printf("6. Display All Logs\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: 
                printf("Enter log message: ");
                fgets(message, 100, stdin);
                message[strcspn(message, "\n")] = '\0';
                
                printf("Enter log level (1-10): ");
                scanf("%d", &level);
                getchar();
                
                if (pushLog(&stack, message, level)) {
                    printf("Log pushed successfully.\n");
                } else {
                    printf("Failed to push log.\n");
                }
                break;

            case 2:
                if (popLog(&stack, &entry)) {
                    printf("Popped log: Level %d - %s\n", 
                          entry.level, entry.message);
                }
                break;

            case 3: 
                if (peekLog(&stack, &entry)) {
                    printf("Top log: Level %d - %s\n", 
                          entry.level, entry.message);
                }
                break;

            case 4: 
                if (isStackEmpty(&stack)) {
                    printf("Stack is empty.\n");
                } else if (isStackFull(&stack)) {
                    printf("Stack is full (%d/%d logs).\n", 
                          stack.top + 1, 100);
                } else {
                    printf("Stack has %d/%d logs.\n", 
                          stack.top + 1, 100);
                }
                break;

            case 5: 
                if (isStackEmpty(&stack)) {
                    printf("Stack is empty - nothing to reverse.\n");
                } else {
                    reverseStack(&stack);
                    printf("Stack reversed successfully.\n");
                }
                break;

            case 6: 
                if (isStackEmpty(&stack)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("\n=== All Logs (Top to Bottom) ===\n");
                    int i;
                    for (i = stack.top; i >= 0; i--) {
                        printf("%d. Level %d: %s\n", 
                              stack.top - i + 1,
                              stack.log[i].level,
                              stack.log[i].message);
                    }
                }
                break;

            case 7:
                printf("Clearing stack and exiting...\n");
                while (!isStackEmpty(&stack)) {
                    popLog(&stack, &entry); 
                }
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
