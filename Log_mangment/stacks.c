#include<stdio.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MAX_SIZE 100
#define MAX_LENGTH 256

typedef struct {
    char message[MAX_LENGTH];
    int level;
} LogEntry;
typedef struct {
    LogEntry log[MAX_SIZE];
    int top;
} LogStack;
void initializeStack(LogStack *s) {
    s->top = -1;
}
bool isStackEmpty(LogStack *s) {
    return (s->top == -1);
}
bool isStackFull(LogStack *s) {
    return (s->top == MAX_SIZE - 1);
}
bool pushLog(LogStack *s, const char *message, int level) {
    if (isStackFull(s)) {
        printf("Cannot push because stack is full.\n");
        return false;
    }
    s->top++;
    strncpy(s->log[s->top].message, message, MAX_LENGTH);
    s->log[s->top].level = level;
    return true;
}
bool popLog(LogStack *s, LogEntry *removed) {
    if (isStackEmpty(s)) {
        printf(" Nothing to pop because stack is empty.\n");
        return false;
    }
    *removed = s->log[s->top];
    s->top--;
    return true;
}
bool peekLog(LogStack *s, LogEntry *top) {
    if (isStackEmpty(s)) {
        printf("There is nothing to peek.\n");
        return false;
    }
    *top = s->log[s->top];
    return true;
}
const char* checkStackState(LogStack *s) {
    if (isStackEmpty(s)) {
	return "empty";
	}
    if (isStackFull(s)){
	return "full";
	} 
    return "there is space";
}
void insertAtBottom(LogStack *s, LogEntry item) {
    if (isStackEmpty(s)) {
        pushLog(s, item.message, item.level);
    } else {
        LogEntry temp;
        popLog(s, &temp);
        insertAtBottom(s, item);
        pushLog(s, temp.message, temp.level);
    }
}

void reverseStack(LogStack *s) {
    if (!isStackEmpty(s)) {
        LogEntry item;
        popLog(s, &item);
        reverseStack(s);
        insertAtBottom(s, item);
    }
}

void displayLog(LogEntry *entry) {
    printf("Level %d: %s\n", entry->level, entry->message);
}

int main() {
    LogStack stack;
    initializeStack(&stack);
    int choice;
    int size, level;
    char message[MAX_LENGTH];
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
                fgets(message, MAX_LENGTH, stdin);
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
                          stack.top + 1, MAX_SIZE);
                } else {
                    printf("Stack has %d/%d logs.\n", 
                          stack.top + 1, MAX_SIZE);
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
                    for (int i = stack.top; i >= 0; i--) {
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

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}




