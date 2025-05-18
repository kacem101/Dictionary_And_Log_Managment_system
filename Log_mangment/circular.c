#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct LogEntry {
    int id;                   
    char message[100];        
    struct LogEntry *next;
    char severity[10];        
    char timestamp[50];       
};
typedef struct LogEntry LogEntry;

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
bool isValidDateTime(int year, int month, int day,int hour, int minutes, int seconds) {
    // Validate year (assuming reasonable range)
    if (year < 1900 || year > 2100) return false;
    
    // Validate month
    if (month < 1 || month > 12) return false;
    
    // Validate day
    if (day < 1 || day > 31) return false;
    
    // Check months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (hour>=24||hour<0)
    {
        return false;
    }
    
    // Check February (ignoring leap years for simplicity)
    if (month == 2 && day > 28) return false;
    
    // Validate minutes and seconds
    if (minutes < 0 || minutes > 59) return false;
    if (seconds < 0 || seconds > 59) return false;
    
    return true;
}

void DelLogByTimeStamp(BLogEntry** L) {

    if (*L == NULL) {
        printf("Log list is empty!\n");
        return;
    }
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

    BLogEntry *current = *L;
    BLogEntry *previous = NULL;

    if (strstr(current->timestamp, temp) != NULL) {
        *L = current->next;
        free(current);
        printf("Log with timestamp '%s W. Central Africa Standard Time' deleted.\n", temp);
        return;
    }

    do {
        if (strstr(current->timestamp, temp) != NULL) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *L);

    if (strstr(current->timestamp, temp) == NULL) {
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
    for (int i = 0; i < mid - 1; i++) {
        temp = temp->next;
    }
    temp->next = NULL;

    temp = r2;
    for (int i = 0; i < size - mid - 1; i++) {
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
void addToFixedBuffer(const char* message, int level) {
    if (!bufferInitialized) {
        for (int i = 0; i < FIXED_BUFFER_SIZE; i++) {
            fixedBuffer[i].message = NULL;
        }
        bufferInitialized = true;
    }
    if (fixedBuffer[bufferIndex].message != NULL) {
        free(fixedBuffer[bufferIndex].message);
    fixedBuffer[bufferIndex].message = strdup(message);
    fixedBuffer[bufferIndex].level = level;
    getCurrentTimestamp(fixedBuffer[bufferIndex].timestamp);
    
    bufferIndex = (bufferIndex + 1) % FIXED_BUFFER_SIZE;
}
bool hasCycle(LogStack* s) {
    if (isStackEmpty(s) || s->size == 1) {
        return false;
    }
    LogEntry** visited = (LogEntry**)malloc(s->size * sizeof(LogEntry*));
    if (!visited) return false;

    bool hasCycle = false;
    int current = s->top;
    int visitCount = 0;

    while (current >= 0) {
        for (int i = 0; i < visitCount; i++) {
            if (visited[i] == &s->logs[current]) {
                hasCycle = true;
                goto cleanup;
            }
        }
        visited[visitCount++] = &s->logs[current];
        current--;
    }

cleanup:
    free(visited);
    return hasCycle;
}

bool pushLog(LogStack* s, const char* message, int level) {

    addToFixedBuffer(message, level);
    if (isStackFull(s)) {
        int newCapacity = s->capacity * 3 / 2;
        if (!resizeStack(s, newCapacity)) {
            return false;
        }
    }

    s->top++;
    s->size++;
    
    s->logs[s->top].message = strdup(message);
    if (s->logs[s->top].message == NULL) {
        fprintf(stderr, "Failed to allocate message\n");
        return false;
    }
    
    s->logs[s->top].level = level;
    getCurrentTimestamp(s->logs[s->top].timestamp);
    if (hasCycle(s)) {
        fprintf(stderr, "Warning: Cycle detected in log stack!\n");
       
    }
    
    return true;
}
static void insertAtBottom(LogStack* s, LogEntry item) {
    if (isStackEmpty(s)) {
        pushLog(s, item.message, item.level);
    } else {
        LogEntry temp;
        popLog(s, &temp);
        insertAtBottom(s, item);
        pushLog(s, temp.message, temp.level);
    }
    free(item.message);
}


int main() {
    LogEntry* L = NULL;
    int choice;
    int size, id, pos, tar;

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
        printf("14. Serch By Id\n");
        printf("15. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

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
                L = SortLogsById(L, LogSize(L));
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
                printf("enter the target ID \n");
                scanf("%d", &tar);
                getchar();
                LogEntry* target = serchLogById(L, tar);
                break;
            case 15:
                if (L != NULL) {
                    LogEntry* current = L->next;
                    while (current != L) {
                        LogEntry* temp = current;
                        current = current->next;
                        free(temp);
                    }
                    free(L);
                }
                printf("Exiting program...\n");
                exit(0);
                 case 16: {
                
                if (!bufferInitialized || bufferIndex == 0) {
                    printf("Fixed buffer is empty.\n");
                    break;
                }
                
                printf("\n=== Fixed Buffer Contents (Most Recent %d Logs) ===\n", FIXED_BUFFER_SIZE);
                int count = 0;
                int idx = bufferIndex;
                
                do {
                    idx = (idx - 1 + FIXED_BUFFER_SIZE) % FIXED_BUFFER_SIZE;
                    if (fixedBuffer[idx].message != NULL) {
                        printf("%d. [%s] Level %d: %s\n", 
                               ++count,
                               fixedBuffer[idx].timestamp,
                               fixedBuffer[idx].level,
                               fixedBuffer[idx].message);
                    }
                } while (idx != bufferIndex && count < FIXED_BUFFER_SIZE);
                break;
            }
            case 17:
                if (L != NULL) {
                    LogEntry* current = L;
                    do {
                        LogEntry* temp = current;
                        current = current->next;
                        free(temp->message);
                        free(temp);
                    } while (current != L && current != NULL);
                }
                
                for (int i = 0; i < FIXED_BUFFER_SIZE; i++) {
                    if (fixedBuffer[i].message != NULL) {
                        free(fixedBuffer[i].message);
                    }
                }
                
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

