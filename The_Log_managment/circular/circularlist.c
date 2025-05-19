#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include"circularlist.h"
bool isStackEmpty(LogStack *s) {
    return (s->top == -1);
}
bool isStackFull(LogStack *s) {
    return (s->top >= LOG_STACK_SIZE - 1);
}
 void displayLogHeader() {
    printf("%-5s | %-32s                    | %-10s | %-100s\n",
           "ID", "Timestamp", "Severity", "Message");
    printf("------|-----------------------------------------------------|------------|----------------------------------------------------------------------\n");
}

void displayLogEntryColumn(LogEntry *entry) {
    printf("%-5d | %-32s | %-10s | %-100s\n",
           entry->id, entry->timestamp, entry->severity, entry->message);
}

char* getCurrentTimeString() {
    time_t current_time;
    struct tm *local_time;
    char buffer[80];
    char* time_string;

    current_time = time(NULL);
    if (current_time == (time_t)-1) {
        perror("time");
        return NULL;
    }

    local_time = localtime(&current_time);
    if (local_time == NULL) {
        perror("localtime");
        return NULL;
    }

    size_t bytes_written = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S %Z", local_time);

    if (bytes_written == 0) {
        fprintf(stderr, "strftime failed or buffer too small\n");
        return NULL;
    }

    time_string = (char*)malloc(bytes_written + 1);
    if (time_string == NULL) {
        perror("malloc");
        return NULL;
    }
    strcpy(time_string, buffer);

    return time_string;
}

int ID = 0;

void InsertLogEntry(LogEntry** L, int pos) {
    int counter = 1;
    LogEntry* temp = (LogEntry*)malloc(sizeof(LogEntry));
    if (temp == NULL) {
        printf("\nMemory Allocation Failed\n");
        return;
    }

    temp->id = ID++;
    temp->next = NULL;
    char msg[100];
    char msg2[100];
    char* temp3 = getCurrentTimeString();

    if (temp3) {
        strcpy(temp->timestamp, temp3);
        free(temp3);
    } else {
        strcpy(temp->timestamp, "ERROR");
    }

    printf("\nWhat is the message?\n");
    fgets(msg2, sizeof(msg2), stdin);
    size_t len = strlen(msg2);
    if (len > 0 && msg2[len - 1] == '\n') {
        msg2[len - 1] = '\0';
    }
    strcpy(temp->message, msg2);

    do {
        printf("What is the level of severity (INFO, WARNING, ERROR)?\n");
        if (fgets(msg, sizeof(msg), stdin) != NULL) {
            size_t len = strlen(msg);
            if (len > 0 && msg[len - 1] == '\n') {
                msg[len - 1] = '\0';
            }
            strcpy(temp->severity, msg);
        } else {
            printf("Error reading severity level.\n");
            free(temp);
            return;
        }
    } while (strcmp(temp->severity, "INFO") != 0 && strcmp(temp->severity, "WARNING") != 0 && strcmp(temp->severity, "ERROR") != 0);

    if (*L == NULL) {
        *L = temp;
        temp->next = *L; // Make it circular
        return;
    }

    if (pos == 1) {
        LogEntry* last = *L;
        while (last->next != *L) {
            last = last->next;
        }
        temp->next = *L;
        *L = temp;
        last->next = *L; // Update last node's next to new head
        return;
    }

    LogEntry* current = *L;
    LogEntry* previous = NULL;
    int count = 1;

    do {
        if (count == pos) {
            temp->next = current;
            if (previous != NULL) {
                previous->next = temp;
            }
            return;
        }
        previous = current;
        current = current->next;
        count++;
    } while (current != *L && count <= pos);

    if (count == pos) {
        temp->next = *L;
        previous->next = temp;
    } else {
        printf("The position is out of range.\n");
        free(temp);
    }
}

void InsertLogEntryByPos(LogEntry** L) {
    int pos;
    printf("Enter the position: ");
    scanf("%d", &pos);
    getchar();
    InsertLogEntry(L, pos);
}

void DisplayLogs(LogEntry* L) {
    if (L == NULL) {
        printf("Logs are empty\n");
        return;
    }
    displayLogHeader();
    LogEntry* current = L;
    do {
        displayLogEntryColumn(current);
        current = current->next;
    } while (current != L);
}

void GenLog(LogEntry** L, int size) {
    int i;
    for (i = 0; i < size; i++) {
        InsertLogEntryByPos(L);
    }
    DisplayLogs(*L);
}

void DelLogEntryByID(LogEntry** L, int ID) {
    if (*L == NULL) {
        printf("\nList is empty\n");
        return;
    }

    LogEntry *current = *L, *prev = NULL;
    LogEntry *last = *L;
    while (last->next != *L) {
        last = last->next;
    }

    // Find the node to delete
    do {
        if (current->id == ID) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *L);

    if (current->id != ID) {
        printf("\nID NOT found\n");
        return;
    }

    // If only one node
    if (current->next == *L && prev == NULL) {
        free(*L);
        *L = NULL;
        return;
    }

    // If first node
    if (current == *L) {
        last->next = current->next;
        *L = (*L)->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

LogEntry* CreateLogEntry() {
    LogEntry* temp = (LogEntry*)malloc(sizeof(LogEntry));
    if (temp == NULL) {
        printf("\nMemory Allocation Failed\n");
        return NULL;
    }

    temp->id = ID++;
    temp->next = NULL;
    char msg[100];
    char msg2[100];
    char* temp3 = getCurrentTimeString();

    if (temp3) {
        strcpy(temp->timestamp, temp3);
        free(temp3);
    } else {
        strcpy(temp->timestamp, "ERROR");
    }

    printf("\nWhat is the message?\n");
    fgets(msg2, sizeof(msg2), stdin);
    size_t len = strlen(msg2);
    if (len > 0 && msg2[len - 1] == '\n') {
        msg2[len - 1] = '\0';
    }
    strcpy(temp->message, msg2);

    do {
        printf("What is the level of severity (INFO, WARNING, ERROR)?\n");
        if (fgets(msg, sizeof(msg), stdin) != NULL) {
            size_t len = strlen(msg);
            if (len > 0 && msg[len - 1] == '\n') {
                msg[len - 1] = '\0';
            }
            strcpy(temp->severity, msg);
        } else {
            printf("Error reading severity level.\n");
            free(temp);
            return NULL;
        }
    } while (strcmp(temp->severity, "INFO") != 0 && strcmp(temp->severity, "WARNING") != 0 && strcmp(temp->severity, "ERROR") != 0);
    return temp;
}

bool IsLogsEmpty(LogEntry* L) {
    return (L == NULL);
}

void AddLogEntryAtTheBeginning(LogEntry** L) {
    bool v = IsLogsEmpty(*L);
    LogEntry* temp = CreateLogEntry();

    if (temp == NULL) {
        printf("Allocation of Mem failed\n");
        return;
    }

    if (v) {
        *L = temp;
        temp->next = temp; // Make it circular
    } else {
        LogEntry* last = *L;
        while (last->next != *L) {
            last = last->next;
        }
        temp->next = *L;
        *L = temp;
        last->next = *L; // Update last node's next to new head
    }
}

void AddLogEntryAtTheEnd(LogEntry** L) {
    bool v = IsLogsEmpty(*L);
    LogEntry* temp = CreateLogEntry();

    if (temp == NULL) {
        printf("Addition Failed\n");
        return;
    }

    if (v) {
        *L = temp;
        temp->next = temp; // Make it circular
    } else {
        LogEntry* last = *L;
        while (last->next != *L) {
            last = last->next;
        }
        last->next = temp;
        temp->next = *L;
    }
}

void DelLogAtTheBeginning(LogEntry** L) {
    bool v = IsLogsEmpty(*L);

    if (v) {
        printf("They Are empty\n");
        return;
    }

    LogEntry* temp = *L;
    if (temp->next == *L) { // Only one node
        free(temp);
        *L = NULL;
    } else {
        LogEntry* last = *L;
        while (last->next != *L) {
            last = last->next;
        }
        *L = (*L)->next;
        last->next = *L;
        free(temp);
    }
}

void DelLogAtTheEnd(LogEntry** L) {
    bool v = IsLogsEmpty(*L);

    if (v) {
        printf("They Are empty\n");
        return;
    }

    LogEntry* temp = *L;
    LogEntry* prev = NULL;

    if (temp->next == *L) { // Only one node
        free(temp);
        *L = NULL;
        return;
    }

    while (temp->next != *L) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = *L;
    free(temp);
}

int LogSize(LogEntry* L) {
    bool v = IsLogsEmpty(L);

    if (v) {
        return 0;
    }

    int counter = 0;
    LogEntry* current = L;
    do {
        counter++;
        current = current->next;
    } while (current != L);

    return counter;
}

void DelLogByTimeStamp(LogEntry** L) {
    if (*L == NULL) {
        printf("Log list is empty!\n");
        return;
    }

    printf("Enter the TimeStamp in this format: 2023-12-25 15:30:45 W. Central Africa Standard Time\n");
    
    char temp[100];
    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        printf("Error reading input.\n");
        return;
    }

    size_t len = strlen(temp);
    if (len > 0 && temp[len - 1] == '\n') {
        temp[len - 1] = '\0';
    }

    LogEntry *current = *L;
    LogEntry *prev = NULL;
    LogEntry *last = *L;
    while (last->next != *L) {
        last = last->next;
    }

    // Find the node to delete
    do {
        if (strcmp(current->timestamp, temp) == 0) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *L);

    if (strcmp(current->timestamp, temp) != 0) {
        printf("No log found with timestamp '%s'\n", temp);
        return;
    }

    // If only one node
    if (current->next == *L && prev == NULL) {
        free(*L);
        *L = NULL;
        printf("Log with timestamp '%s' deleted.\n", temp);
        return;
    }

    // If first node
    if (current == *L) {
        last->next = current->next;
        *L = (*L)->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Log with timestamp '%s' deleted.\n", temp);
}

LogEntry* merge2List(LogEntry* h1, int size1, LogEntry* h2, int size2) {
    if (h1 == NULL && h2 == NULL) return NULL;

    LogEntry* dummy = malloc(sizeof(LogEntry));  
    LogEntry* tail = dummy;
    dummy->next = NULL;

    int count1 = 0, count2 = 0;

    while (count1 < size1 && count2 < size2 && h1 != NULL && h2 != NULL) {
        if (h1->id > h2->id) {
            tail->next = h2;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        tail = tail->next;
        count2++;
    }

    tail->next = NULL; // Break the circular reference for merging
    LogEntry* result = dummy->next;
    free(dummy);
    return result;
}

LogEntry* SortLogsById(LogEntry* head, int size) {
    if (size <= 1) {
        return head;
    }

    int mid = size / 2, counter = 0;
    LogEntry* p1 = head;
    LogEntry* p2 = NULL;
    LogEntry* t = NULL;

    // Split the list
    while (counter < mid - 1) {
        p1 = p1->next;
        counter++;
    }
    p2 = p1->next;
    p1->next = head; // Maintain circularity of first half
    p1 = p2;

    // Find the end of second half
    counter = 0;
    while (counter < size - mid - 1) {
        p1 = p1->next;
        counter++;
    }
    p1->next = p2; // Maintain circularity of second half

    LogEntry* r1 = SortLogsById(head, mid);
    LogEntry* r2 = SortLogsById(p2, size - mid);
    
    // Break circularity for merging
    LogEntry* temp = r1;
    int i;
    for ( i = 0; i < mid - 1; i++) {
        temp = temp->next;
    }
    temp->next = NULL;

    temp = r2;
    for ( i = 0; i < size - mid - 1; i++) {
        temp = temp->next;
    }
    temp->next = NULL;

    head = merge2List(r1, mid, r2, size - mid);

    // Make the merged list circular again
    if (head != NULL) {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = head;
    }

    return head;
}

LogEntry* CopySingleLogEntry(const LogEntry* original) {
    if (original == NULL) {
        return NULL;
    }

    LogEntry* copy = malloc(sizeof(LogEntry));
    if (copy == NULL) {
        perror("Failed to allocate memory for log entry copy");
        return NULL;
    }

    copy->id = original->id;
    strncpy(copy->message, original->message, sizeof(copy->message));
    strncpy(copy->severity, original->severity, sizeof(copy->severity));
    strncpy(copy->timestamp, original->timestamp, sizeof(copy->timestamp));
    copy->message[sizeof(copy->message) - 1] = '\0';
    copy->severity[sizeof(copy->severity) - 1] = '\0';
    copy->timestamp[sizeof(copy->timestamp) - 1] = '\0';
    copy->next = NULL;

    return copy;
}

void ReverseLogs(LogEntry** H) {
    if (IsLogsEmpty(*H) || (*H)->next == *H) {
        return;
    }

    LogEntry* prev = *H;
    LogEntry* current = (*H)->next;
    LogEntry* next = NULL;

    while (current != *H) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    (*H)->next = prev;
    *H = prev;
}

void SortBySeverity(LogEntry** head) {
    if (*head == NULL) return;

    LogEntry *info_head = NULL, *info_tail = NULL;
    LogEntry *warn_head = NULL, *warn_tail = NULL;
    LogEntry *error_head = NULL, *error_tail = NULL;

    LogEntry* current = *head;
    LogEntry* next = NULL;

    do {
        next = current->next;
        current->next = current; // Temporarily make it self-circular

        if (strcmp(current->severity, "INFO") == 0) {
            if (info_head == NULL) {
                info_head = current;
                info_tail = current;
            } else {
                info_tail->next = current;
                info_tail = current;
            }
        }
        else if (strcmp(current->severity, "WARNING") == 0) {
            if (warn_head == NULL) {
                warn_head = current;
                warn_tail = current;
            } else {
                warn_tail->next = current;
                warn_tail = current;
            }
        }
        else { // ERROR
            if (error_head == NULL) {
                error_head = current;
                error_tail = current;
            } else {
                error_tail->next = current;
                error_tail = current;
            }
        }

        current = next;
    } while (current != *head);

    *head = NULL;
    LogEntry* new_tail = NULL;

    if (info_head) {
        *head = info_head;
        new_tail = info_tail;
    }
    if (warn_head) {
        if (*head == NULL) {
            *head = warn_head;
        } else {
            new_tail->next = warn_head;
        }
        new_tail = warn_tail;
    }
    if (error_head) {
        if (*head == NULL) {
            *head = error_head;
        } else {
            new_tail->next = error_head;
        }
        new_tail = error_tail;
    }

    if (new_tail) {
        new_tail->next = *head; // Make it circular
    }
}

LogEntry* serchLogById(LogEntry* L, int ID) {
    if (L == NULL) {   
        printf("it is empty\n");
        return NULL;
    }

    LogEntry* current = L;
    do {
        if (current->id == ID) {   
            printf("it was found\n");
            printf("%-5d | %-32s | %-10s | %-100s\n", current->id, current->timestamp, current->severity, current->message);
            return current;
        }
        current = current->next;
    } while (current != L);

    printf("Not found \n");
    getchar();
    return NULL;
}
typedef struct {
    char* message;
    int level;
    char timestamp[20];
} FixedLogEntry;

 
FixedLogEntry fixedBuffer[FIXED_BUFFER_SIZE];
bool bufferInitialized = false;
int bufferIndex = 0;
void addToFixedBuffer(const char* message, int level) {
    if (!bufferInitialized) {
    	int i;
        for ( i = 0; i < 100; i++) {
            fixedBuffer[i].message = NULL;
        }
        bufferInitialized = true;
    }
    if (fixedBuffer[bufferIndex].message != NULL) {
        free(fixedBuffer[bufferIndex].message);
    fixedBuffer[bufferIndex].message = strdup(message);
    fixedBuffer[bufferIndex].level = level;
    char *temp=getCurrentTimeString();
    strcpy(fixedBuffer[bufferIndex].timestamp,temp);
    
    bufferIndex = (bufferIndex + 1) % 100;
}
}
bool hasCycle(LogStack* s) {
    if (isStackEmpty(s) || s->size <= 1) {
        return false; // A cycle in this context needs at least two elements
    }

    LogEtr** visited_entries = (LogEtr**)malloc(s->size * sizeof(LogEtr*));
    if (!visited_entries) {
        perror("Failed to allocate memory for visited_entries in hasCycle");
        return false;
    }

    bool cycle_detected = false;
    int visited_count = 0;

    // Iterate from the bottom of the stack (index 0) to the top (s->top)
    for (int i = 0; i <= s->top; ++i) {
        // Check if the address of the current log entry in the stack's array has been visited before
        for (int j = 0; j < visited_count; ++j) {
            // Compare the address of the current LogEtr in the stack's array
            // Casting to void* to avoid "comparison of distinct pointer types lacks a cast" warning
            if ((void*)&(s->logs[i]) == (void*)visited_entries[j]) {
                cycle_detected = true;
                
            }
        }
		if(cycle_detected){
			break;
		}
        visited_entries[visited_count++] = &(s->logs[i]);
    }

	
    free(visited_entries);
    return cycle_detected;
}


void initLogStack(LogStack* s) {
    if (s == NULL) {
        fprintf(stderr, "LogStack pointer is NULL in initLogStack.\n");
        return;
    }
    s->top = -1;
    s->size = 0;

}

bool pushLog(LogStack* s, const char* message, int level) {
     if (s == NULL) {
        fprintf(stderr, "LogStack is not initialized.\n");
        return false;
    }

    addToFixedBuffer(message, level);

    if (isStackFull(s)) {
        fprintf(stderr, "Failed to push log: LogStack is full (max %d elements).\n", LOG_STACK_SIZE);
        return false; // Cannot push if the static array is full
    }

    s->top++;
    s->size++;

  
    strncpy(s->logs[s->top].message, message, sizeof(s->logs[s->top].message) - 1);
    s->logs[s->top].message[sizeof(s->logs[s->top].message) - 1] = '\0';

    s->logs[s->top].level = level;

    char* timestamp_str = getCurrentTimeString();
    if (timestamp_str) {
        strncpy(s->logs[s->top].timestamp, timestamp_str, sizeof(s->logs[s->top].timestamp) - 1);
        s->logs[s->top].timestamp[sizeof(s->logs[s->top].timestamp) - 1] = '\0';
        free(timestamp_str);
    } else {
         strncpy(s->logs[s->top].timestamp, "ERROR_TIME", sizeof(s->logs[s->top].timestamp) - 1);
         s->logs[s->top].timestamp[sizeof(s->logs[s->top].timestamp) - 1] = '\0';
    }


    // Check for a "cycle" in the array after pushing (as per original logic)
    // Note: This checks for revisiting the same memory location within the 'logs' array,
    // not for linked-list cycles via 'next' pointers.
    if (hasCycle(s)) {
        printf("Warning: 'Cycle' detected in LogStack array after pushing log (Level: %d).\n", s->logs[s->top].level);
        // Depending on requirements, you might want to handle this, e.g., pop the last element
    }

    return true;
}

// Function to display LogStack contents
void displayLogStack(LogStack* s) {
    if (s == NULL || isStackEmpty(s)) {
        printf("LogStack is empty or not initialized.\n");
        return;
    }

    printf("\n=== LogStack Contents (Top to Bottom) ===\n");
    printf("%-10s | %-32s | %-100s\n", "Level", "Timestamp", "Message");
    printf("-----------|-----------------------------------------------------|----------------------------------------------------------------------\n");

    for (int i = s->top; i >= 0; --i) {
        printf("%-10d | %-32s | %-100s\n",
               s->logs[i].level,
               s->logs[i].timestamp,
               s->logs[i].message);
    }
     printf("Stack Size: %d, Stack Capacity: %d\n", s->size, LOG_STACK_SIZE); // Display fixed capacity
}

// Function to free the circular linked list
void freeLogList(LogEntry* head) {
    if (head == NULL) {
        return;
    }

    LogEntry* current = head;
    LogEntry* next_node;

    // Break the circular link
    LogEntry* last = head;
    while (last->next != head) {
        last = last->next;
    }
    last->next = NULL;

    // Traverse and free each node
    current = head;
    while (current != NULL) {
        next_node = current->next;
        // Free dynamically allocated members within LogEntry if any (message, severity, timestamp are fixed size arrays here)
        // Based on your CreateLogEntry, timestamp was dynamically allocated, but then copied to a fixed array.
        // If you change LogEntry to have char* members, free them here.
        free(current);
        current = next_node;
    }
}


void freeFixedBuffer() {
    if (bufferInitialized) {
        for (int i = 0; i < FIXED_BUFFER_SIZE; i++) {
            if (fixedBuffer[i].message != NULL) {
                free(fixedBuffer[i].message);
                fixedBuffer[i].message = NULL;
            }
        }
        bufferInitialized = false; // Reset initialization flag
    }
}
