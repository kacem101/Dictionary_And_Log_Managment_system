#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct BLogEntry {
    int id;                   
    char message[100];        
    struct BLogEntry *next;
    char severity[10];        
    char timestamp[50];
    struct BLogEntry *prev;       
};
typedef struct BLogEntry BLogEntry;

void displayBLogHeader() {
    printf("%-5s | %-32s                    | %-10s | %-100s\n",
           "ID", "Timestamp", "Severity", "Message");
    printf("------|-----------------------------------------------------|------------|----------------------------------------------------------------------\n");
}

void displayBLogEntryColumn(BLogEntry *entry) {
    if (entry==NULL)
    {
        printf("it is Empty \n");
        return;
    }
    printf("%-5d | %-32s | %-10s | %-100s\n",
           entry->id, entry->timestamp, entry->severity, entry->message);
}
void displaySelBLogEntryColumn(BLogEntry *entry) {
    printf("%-5d | %-32s | %-10s | %-100s\n",
           entry->id, entry->timestamp, entry->severity, entry->message);
}
char* BgetCurrentTimeString() {
    time_t current_time;
    struct tm *local_time;
    char buffer[80];
    char* time_string;

    // Get the current time
    current_time = time(NULL);
    if (current_time == (time_t)-1) {
        perror("time");
        return NULL; // Indicate error
    }

    // Convert to local time
    local_time = localtime(&current_time);
    if (local_time == NULL) {
        perror("localtime");
        return NULL; // Indicate error
    }

    // Format the time into a string
    size_t bytes_written = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S %Z", local_time);

    if (bytes_written == 0) {
        fprintf(stderr, "strftime failed or buffer too small\n");
        return NULL; // Indicate error
    }

    // Allocate memory for the string and temp the formatted time
    time_string = (char*)malloc(bytes_written + 1);
    if (time_string == NULL) {
        perror("malloc");
        return NULL; // Indicate error
    }
    strcpy(time_string, buffer);

    return time_string;
}


int ID = 0;

void InsertBLogEntryBI(BLogEntry** L, int pos) {
    int counter = 1;
    BLogEntry* temp = (BLogEntry*)malloc(sizeof(BLogEntry));
    if (temp == NULL) {
        printf("\nMemory Allocation Failed\n");
        return;
    }

    temp->id = ID++;
    temp->next = NULL;
    char msg[100];
    char msg2[100];
    char* temp3 = BgetCurrentTimeString();

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

    if (pos == 1 || *L == NULL) {
        temp->next = *L;
        temp->prev=NULL;
        *L = temp;
        return;
    }

    BLogEntry* current = *L;
    BLogEntry* previous = NULL;

    while (current != NULL && counter < pos) {
        previous = current;
        current = current->next;
        counter++;
    }

    if (counter == pos) {
        temp->next = current;
        temp->prev = previous;
        if (previous != NULL) {
            previous->next = temp;
        }
    } else {
        printf("The position is out of range.\n");
        free(temp);
    }
}

void InsertBLogEntryByPosBI(BLogEntry** L) {
    int pos;
    printf("Enter the position: ");
    scanf("%d", &pos);
    getchar();  // Consume leftover '\n'
    InsertBLogEntryBI(L, pos);
}

void DisplayBLogs(BLogEntry* L,int pos) {
    if (L == NULL) {
        printf("Logs are empty\n");
        return;
    }
    displayBLogHeader();
    int counter=1;
    while (L != NULL) {
        if (pos==counter)
        {
            displaySelBLogEntryColumn(L);
        }
        else
        {
            displayBLogEntryColumn(L);
        }
        L = L->next;
        counter++;
    }
}

void GenLogBI(BLogEntry** L, int size) {
	int i;
    for (i = 0; i < size; i++) {
        InsertBLogEntryByPosBI(L);
        
    }
    DisplayBLogs(*L,1);
}

void DelBLogEntryByID(BLogEntry**L,int ID){
    BLogEntry *p;
    BLogEntry *q;
    p=*L;
    if(p->id==ID){
        free((*L));
        (*L)=p->next;
        return;
    }
    while(p->next!=NULL){
        if(p->next->id==ID){
        q=p->next;
        p->next=p->next->next;
        free(q);
        return ;
        }
        p=p->next;
    }
    printf("\nID NOT found\n");
}
BLogEntry*CreateBLogEntryBI(){
    BLogEntry* temp = (BLogEntry*)malloc(sizeof(BLogEntry));
    if (temp == NULL) {
        printf("\nMemory Allocation Failed\n");
        return NULL;
    }

    temp->id = ID++;
    temp->next = NULL;
    temp->prev = NULL;
    char msg[100];
    char msg2[100];
    char* temp3 = BgetCurrentTimeString();

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

bool IsBLogsEmpty(BLogEntry*L){
    return(L==NULL);
}

void AddBLogEntryAtTheBeginning(BLogEntry**L){

    bool v=IsBLogsEmpty(*L);

    BLogEntry*temp=CreateBLogEntryBI();

    if (temp==NULL)
    {
        printf("Allocation of Mem failed\n");
        return;
    }

    if (v)
    {
        (*L)=temp;
        return;
    }
    else
    {
        temp->next=(*L);
        (*L)=temp;
        return;
    }
    
    
}

void AddBLogEntryAtTheEndBI(BLogEntry**L){
    bool v=IsBLogsEmpty(*L);

    BLogEntry*temp=CreateBLogEntryBI();

    if (temp==NULL)
    {
        printf("Addition Failed\n");
        return;
    }

    if (v)
    {
        (*L)=temp;
    }

    else
    {
        BLogEntry*Tem=(*L);
        while (Tem->next!=NULL)
        {
            Tem=Tem->next;
        }
        Tem->next=temp;
        temp->prev=Tem;
        return;
    }
    
}

void DelBLogAtTheBeginning(BLogEntry**L){

    bool v=IsBLogsEmpty(*L);

    if (v)
    {
        printf("They Are empty\n");
        return;
    }

    else
    {
        BLogEntry*temp=(*L);
        (*L)=(*L)->next;
        free(temp);
        return;
    }
}

void DelBLogAtTheEnd(BLogEntry**L){

    bool v=IsBLogsEmpty(*L);

    if (v)
    {
        printf("They Are empty\n");
        return;
    }

    else if ((*L)->next=NULL)
    {
        free((*L));
        (*L)=NULL;
        return;
    }
    
    else
    {
        BLogEntry*Tem=(*L);
        while (Tem->next->next!=NULL)
        {
            Tem=Tem->next;
        }
        BLogEntry*fre=Tem->next;
        Tem->next=NULL;
        free(fre);
        return;
    }
}
int BLogSize(BLogEntry*L){

    bool v=IsBLogsEmpty(L);

    if (v)
    {
        return 0;
    }
    else
    {
        int counter=0;
        while (L!=NULL)
        {
            counter++;
            L=L->next;
        }
        return counter;
    }
    
}
bool isValidDateTimeB(int year, int month, int day,int hour, int minutes, int seconds) {
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

void DelBLogByTimeStamp(BLogEntry** L) {

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
        
        if (!isValidDateTimeB(year, month, day,hour, minutes, seconds)) {
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

    while (current != NULL) {
        if (strstr(current->timestamp, temp) != NULL) {
            if (previous != NULL) {
                previous->next = current->next;
            }
            free(current);
            printf("Log with timestamp '%s W. Central Africa Standard Time' deleted.\n", temp);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("No log found with timestamp '%s'\n", temp);
}

BLogEntry* merge2ListBI(BLogEntry* h1, int size1, BLogEntry* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    BLogEntry*dummy = malloc(sizeof(BLogEntry));  
    if (dummy==NULL)
    {
        printf("Memory Allocation Failed\n ");
        getchar();
        return NULL;
    }
    
    BLogEntry* tail = dummy;
    dummy->next = NULL;
    dummy->prev= NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
        if (h1->id > h2->id) {
            tail->next = h2;
            h2->prev=tail;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1->prev=tail;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1->prev=tail;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        h2->prev=tail;
        tail = tail->next;
        count2++;
    }

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    BLogEntry* result = dummy->next;
    free(dummy);
    if (result!=NULL)
    {
        result->prev=NULL;
    }
    return result;
}

BLogEntry* SortLogsByIdBI(BLogEntry*head,int size){
    if(size<=1){
        return head;
    }
    int mid=size/2,counter=0;
    BLogEntry* p1=head,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
    while(counter<mid-1){
        p1=p1->next;
        counter++;
    }
    p2=p1->next;
    t=p1;
    p1=p1->next;
    if (t!=NULL)
    {
        t->next=NULL;
    }
    else
    {
        if (p1->next==NULL)
        {
            p2=NULL;
        }
        else
        {
            p2=p1->next;
        }
    }
    r1=SortLogsByIdBI(head,mid);
    r2=SortLogsByIdBI(p2,size-mid);
    head=merge2ListBI(r1,mid,r2,size-mid);
    return head;
}
BLogEntry* CopySingleBLogEntry(const BLogEntry* original) {
    if (original == NULL) {
        return NULL;
    }

    // Allocate memory for new node
    BLogEntry* copy = malloc(sizeof(BLogEntry));
    if (copy == NULL) {
        perror("Failed to allocate memory for log entry copy");
        return NULL;
    }

    // Copy all data fields
    copy->id = original->id;
    
    // Copy strings with buffer size protection
    strncpy(copy->message, original->message, sizeof(copy->message));
    strncpy(copy->severity, original->severity, sizeof(copy->severity));
    strncpy(copy->timestamp, original->timestamp, sizeof(copy->timestamp));
    
    // Ensure null-termination
    copy->message[sizeof(copy->message) - 1] = '\0';
    copy->severity[sizeof(copy->severity) - 1] = '\0';
    copy->timestamp[sizeof(copy->timestamp) - 1] = '\0';
    
    // Explicitly set next to NULL (isolated copy)
    copy->next = NULL;
    copy->prev = NULL;

    return copy;
}
void ReverseLogsBI(BLogEntry**H){
    if (IsBLogsEmpty(*H)||(*H)->next==NULL)
    {
        return;
    }

    BLogEntry*T1;
    BLogEntry*L=*H;

    while (L!=NULL)
    {
        T1=L->next;
        L->next=L->prev;
        L->prev=T1;
        *H=L;
        L=L->prev;
    }
}
void SortBySeverityBI(BLogEntry** head) {
    if (*head == NULL) return;
    // temp1 = info_head, temp2 = info_tail
    // temp3 = warn_head, temp4 = warn_tail
    // temp5 = error_head, temp6 = error_tail
    BLogEntry *temp1 = NULL, *temp2 = NULL;
    BLogEntry *temp3 = NULL, *temp4 = NULL;
    BLogEntry *temp5 = NULL, *temp6 = NULL;

    BLogEntry* current = *head;
    while (current != NULL) {
        BLogEntry* next = current->next;
        current->next = NULL;
        if (strcmp(current->severity, "INFO") == 0) {
            if (temp1 == NULL) {
                temp1 = current;
                temp2 = current;
            } else {
                temp2->next = current;
                current->prev=temp2;
                temp2 = current;
            }
        }
        else if (strcmp(current->severity, "WARNING") == 0) {
            if (temp3 == NULL) {
                temp3 = current;
                temp4 = current;
            } else {
                temp4->next = current;
                current->prev=temp4;
                temp4 = current;
            }
        }
        else { // ERROR
            if (temp5 == NULL) {
                temp5 = current;
                temp6 = current;
            } else {
                temp6->next = current;
                current->prev=temp6;
                temp6 = current;
            }
        }

        current = next;
    }
    BLogEntry* new_head = NULL;
    BLogEntry* new_tail = NULL;

    if (temp1) {  
        new_head = temp1;
        new_tail = temp2;
    }

    if (temp3) {  
        if (new_head == NULL) {
            new_head = temp3;
        } else {
            new_tail->next = temp3;
            temp3->prev = new_tail;
        }
        new_tail = temp4;
    }

    if (temp5) {  
        if (new_head == NULL) {
            new_head = temp5;
        } else {
            new_tail->next = temp5;
            temp5->prev = new_tail;
        }
        new_tail = temp6;
    }

    *head = new_head;
}

BLogEntry* serchLogById(BLogEntry*L,int ID){
    if (L==NULL)
    {   
        printf("it is empty\n");
        return NULL;
    }
    while (L!=NULL)
    {
        if (L->id==ID)
        {   
            printf("it was found\n");
            printf("%-5d | %-32s | %-10s | %-100s\n",L->id, L->timestamp, L->severity, L->message);
            return L;
        }
        L=L->next;
    }
    printf("Not found \n");
    getchar();
    return NULL;
}
void MoveForward(BLogEntry*L,int* pos){
    if ((*pos)<=0||(*pos)>BLogSize(L))
    {
        return;
    }
    (*pos)++;
}
void MoveBackward(BLogEntry*L,int* pos){
    if ((*pos)<=0||(*pos)>BLogSize(L))
    {
        return;
    }
    (*pos)--;
}
void ReturnToBegining(BLogEntry*L,int*pos){
    if ((*pos)<=0||(*pos)>BLogSize(L))
    {
        return;
    }
    (*pos)==0;
}
void DelBLogByPos(BLogEntry** L, int pos) {
    // Check for empty list
    if (*L == NULL) {
        printf("List is empty!\n");
        return;
    }

    int list_size = BLogSize(*L);
    
    // Validate position
    if (pos < 1 || pos > list_size) {
        printf("Position %d is out of range (1-%d)\n", pos, list_size);
        return;
    }

    // Handle special cases
    if (pos == 1) {
        DelBLogAtTheBeginning(L);
        return;
    }
    if (pos == list_size) {
        DelBLogAtTheEnd(L);
        return;
    }

    // General case: delete node in the middle
    BLogEntry* current = *L;
    int counter = 1;
    
    // Traverse to the node before the one to delete
    while (current != NULL && counter < pos - 1) {
        current = current->next;
        counter++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Error: Invalid position reached\n");
        return;
    }

    BLogEntry* node_to_delete = current->next;
    
    // Update next pointer of previous node
    current->next = node_to_delete->next;
    
    // Update prev pointer of next node (if exists)
    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = current;
    }

    // Free the node
    free(node_to_delete);
}
void SerchByKeyWord(BLogEntry*H){
    BLogEntry*L=H;
    if (L==NULL)
    {   
        printf("LIST is empty ");
        return ;
    }

    int counter=1;
    char Buffer[100];
    char Target[100];
    printf("\nWhat is the message?\n");
    fgets(Buffer, sizeof(Buffer), stdin);
    size_t len = strlen(Buffer);
    strcpy(Target,Buffer);
    if (len > 0 && Buffer[len - 1] == '\n') {
        Target[len - 1] = '\0';
    }
    printf("target :%s\nThe List Of All Logs containing The key word\n",Target);
    displayBLogHeader();
    while (L!=NULL)
    {   
        if (strstr(L->message,Target)!=NULL)
        {
            displayBLogEntryColumn(L);
        }
        L=L->next;
        counter++;
    }
    return ;
}
