#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include"queue.h"

int main() {
	LogQueue *queue = (LogQueue *)malloc(sizeof(LogQueue));
    initializequeue(queue);
    LogEntry *entry = (LogEntry*)malloc(sizeof(LogEntry));
    if (entry == NULL) {
        printf("Memory allocation failed for entry.\n");
        return 1;
    }
    int choice;
    int level;
    char message[100];

    while (1) {
        printf("\n=== Log Queue Management System ===\n");
        printf("1. Enqueue New Log Entry\n");
        printf("2. Dequeue Log Entry\n");
        printf("3. Peek Front Log Entry\n");
        printf("4. Check Queue Status\n");
        printf("5. Display All Logs\n");
        printf("6. Exit\n");
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
                
                if (enqueue(queue, message, level)) {
                    printf("Log enqueued successfully.\n");
                } else {
                    printf("Failed to enqueue log.\n");
                }
                break;

            case 2:
                if (dequeue(queue, entry)) {
                    printf("Dequeued log: Level %d - %s\n", 
                          entry->level, entry->message);
                }
                break;

            case 3: 
                if (peek(queue, entry)) {
                    printf("Front log: Level %d - %s\n", 
                          entry->level, entry->message);
                }
                break;

            case 4: 
                if (isEmpty(queue)) {
                    printf("Queue is empty.\n");
                } else if (isFull(queue)) {
                    printf("Queue is full (%d/%d logs).\n", 
                          queue->size, 100);
                } else {
                    printf("Queue has %d/%d logs.\n", 
                          queue->size, 100);
                }
                break;

            case 5: 
                if (isEmpty(queue)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("\n=== All Logs (Front to Rear) ===\n");
                    int i, count;
                    for (i = queue->head, count = 0; count < queue->size; 
                         i = (i + 1) % 100, count++) {
                        printf("%d. Level %d: %s\n",count + 1,queue->log[i].level,queue->log[i].message);
                    }
                }
                break;

            case 6:
                printf("Clearing queue and exiting...\n");
                while (!isEmpty(queue)) {
                    dequeue(queue, entry); 
                }
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

