#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include<ctype.h>
#include"recursion.h"
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

    if (pos == 1 || *L == NULL) {
        temp->next = *L;
        *L = temp;
        return;
    }

    LogEntry* current = *L;
    LogEntry* previous = NULL;

    while (current != NULL && counter < pos) {
        previous = current;
        current = current->next;
        counter++;
    }

    if (counter == pos) {
        temp->next = current;
        if (previous != NULL) {
            previous->next = temp;
        }
    } else {
        printf("The position is out of range.\n");
        free(temp);
    }
}

void InsertLogEntryByPos(LogEntry** L) {
    int pos;
    printf("Enter the position: ");
    scanf("%d", &pos);
    getchar();  // Consume leftover '\n'
    InsertLogEntry(L, pos);
}

void DisplayLogs(LogEntry* L) {
    if (L == NULL) {
        printf("Logs are empty\n");
        return;
    }
    displayLogHeader();
    while (L != NULL) {
        displayLogEntryColumn(L);
        L = L->next;
    }
}

void GenLog(LogEntry** L, int size) {
	int i;
    for (i = 0; i < size; i++) {
        InsertLogEntryByPos(L);
        
    }
    DisplayLogs(*L);
}

void DelLogEntryByID(LogEntry**L,int ID){
    LogEntry *p;
    LogEntry *q;
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
LogEntry*CreateLogEntry(){
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

bool IsLogsEmpty(LogEntry*L){
    return(L==NULL);
}

void AddLogEntryAtTheBeginning(LogEntry**L){

    bool v=IsLogsEmpty(*L);

    LogEntry*temp=CreateLogEntry();

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

void AddLogEntryAtTheEnd(LogEntry**L){
    bool v=IsLogsEmpty(*L);

    LogEntry*temp=CreateLogEntry();

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
        LogEntry*Tem=(*L);
        while (Tem->next!=NULL)
        {
            Tem=Tem->next;
        }
        Tem->next=temp;
        return;
    }
    
}

void DelLogAtTheBeginning(LogEntry**L){

    bool v=IsLogsEmpty(*L);

    if (v)
    {
        printf("They Are empty\n");
        return;
    }

    else
    {
        LogEntry*temp=(*L);
        (*L)=(*L)->next;
        free(temp);
        return;
    }
}

void DelLogAtTheEnd(LogEntry**L){

    bool v=IsLogsEmpty(*L);

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
        LogEntry*Tem=(*L);
        while (Tem->next!=NULL)
        {
            Tem=Tem->next;
        }
        free(Tem);
        return;
    }
    
}
int LogSize(LogEntry*L){

    bool v=IsLogsEmpty(L);

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
    LogEntry *previous = NULL;

    if (strcmp(current->timestamp, temp) == 0) {
        *L = current->next;
        free(current);
        printf("Log with timestamp '%s' deleted.\n", temp);
        return;
    }

    while (current != NULL) {
        if (strcmp(current->timestamp, temp) == 0) {
            if (previous != NULL) {
                previous->next = current->next;
            }
            free(current);
            printf("Log with timestamp '%s' deleted.\n", temp);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("No log found with timestamp '%s'\n", temp);
}

LogEntry* merge2List(LogEntry* h1, int size1, LogEntry* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    LogEntry*dummy = malloc(sizeof(LogEntry));  
    LogEntry* tail = dummy;
    dummy->next = NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
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

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    LogEntry* result = dummy->next;
    free(dummy);
    return result;
}

LogEntry* SortLogsById(LogEntry*head,int size){
    if(size<=1){
        return head;
    }
    int mid=size/2,counter=0;
    LogEntry* p1=head,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
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
    r1=SortLogsById(head,mid);
    r2=SortLogsById(p2,size-mid);
    head=merge2List(r1,mid,r2,size-mid);
    return head;
}
LogEntry* CopySingleLogEntry(const LogEntry* original) {
    if (original == NULL) {
        return NULL;
    }

    // Allocate memory for new node
    LogEntry* copy = malloc(sizeof(LogEntry));
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

    return copy;
}
void ReverseLogs(LogEntry**H){
    if (IsLogsEmpty(*H)||(*H)->next==NULL)
    {
        return;
    }

    LogEntry*L1=*H;
    LogEntry*L2=L1->next;
    L1->next=NULL;
    LogEntry*L3=L2->next;
    while (L2!=NULL)
    {   
        L3=L2->next;
        L2->next=L1;
        L1=L2;
        L2=L3;
    }
    *H=L1;
}
void SortBySeverity(LogEntry** head) {
    if (*head == NULL) return;
    // temp1 = info_head, temp2 = info_tail
    // temp3 = warn_head, temp4 = warn_tail
    // temp5 = error_head, temp6 = error_tail
    LogEntry *temp1 = NULL, *temp2 = NULL;
    LogEntry *temp3 = NULL, *temp4 = NULL;
    LogEntry *temp5 = NULL, *temp6 = NULL;

    LogEntry* current = *head;
    while (current != NULL) {
        LogEntry* next = current->next;
        current->next = NULL;
        if (strcmp(current->severity, "INFO") == 0) {
            if (temp1 == NULL) {
                temp1 = current;
                temp2 = current;
            } else {
                temp2->next = current;
                temp2 = current;
            }
        }
        else if (strcmp(current->severity, "WARNING") == 0) {
            if (temp3 == NULL) {
                temp3 = current;
                temp4 = current;
            } else {
                temp4->next = current;
                temp4 = current;
            }
        }
        else { // ERROR
            if (temp5 == NULL) {
                temp5 = current;
                temp6 = current;
            } else {
                temp6->next = current;
                temp6 = current;
            }
        }

        current = next;
    }

    *head = NULL;
    LogEntry** tail = head; 
    
    if (temp1) {
        *tail = temp1;
        tail = &temp2->next;
    }
    if (temp3) {
        *tail = temp3;
        tail = &temp4->next;
    }
    if (temp5) {
        *tail = temp5;
    }
}
LogEntry* serchLogById(LogEntry*L,int ID){
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
int factorial(int n){
    if (n<0)
    {
        return -1;
    }
    if (n==0)
    {
        return 1;
    }
    return n*factorial(n-1);
}
int fibonachiSeries(int n){
    if (n<0)
    {
        return -1;
    }
    
    if (n==0)
    {
        return 0;
    }
    if (n==1)
    {
        return 1;
    }
    return fibonachiSeries(n-1)+fibonachiSeries(n-2);
}
LogEntry*ReverseSubFunction(LogEntry*L,LogEntry**New){
    if(L->next==NULL){
        *New=L;
        return L;
    }
    ReverseSubFunction(L->next,New)->next=L;
    L->next=NULL;
    return L;
}
void ReverseWithRecursion(LogEntry**L){
    LogEntry*Temp;
    ReverseSubFunction(*L,&Temp);
    *L=Temp;
}
int FindMAxLogId(LogEntry*L){
    if (IsLogsEmpty(L))
    {
        return -1;
    }
    if(L->next==NULL){
        return L->id;
    }
    return FindMAxLogId(L->next)>L->id ? FindMAxLogId(L->next) : L->id;
}
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
void skip_whitespace(char* infix, int* i) {
    while (infix[*i] != '\0' && isspace(infix[*i])) {
        (*i)++;
    }
}
void parse_factor(char* infix, char* postfix, int* i, int* j) {
    skip_whitespace(infix, i); // Skip leading whitespace

    if (infix[*i] == '(') {
        (*i)++; // Consume '('
        parse_expression(infix, postfix, i, j); // Recursively parse the expression inside parentheses
        skip_whitespace(infix, i); // Skip whitespace before ')'
        if (infix[*i] == ')') {
            (*i)++; // Consume ')'
        } else {
            // Error: Mismatched parentheses
            printf("Error: Missing closing parenthesis at index %d\n", *i);
            // In a real application, you'd likely want a more robust error handling mechanism
            // and stop processing. For simplicity, we just print the error.
        }
    } else if (isalnum(infix[*i])) {
        // If it's an operand (letter or digit)
        postfix[(*j)++] = infix[*i]; // Append the operand to postfix
        (*i)++; // Consume the operand from infix
    } else {
        // Error: Unexpected character
        if (infix[*i] != '\0') {
             fprintf(stderr, "Error: Unexpected character '%c' at index %d\n", infix[*i], *i);
        } else {
             fprintf(stderr, "Error: Unexpected end of string in factor at index %d\n", *i);
        }
        // Handle error appropriately (e.g., set an error flag)
    }

     // Handle exponents (right-associative) after parsing the base factor
     skip_whitespace(infix, i);
     while (infix[*i] != '\0' && infix[*i] == '^') {
         char op = infix[*i];
         (*i)++; // Consume '^'
         parse_factor(infix, postfix, i, j); // Recursively parse the exponent (which is a factor)
         postfix[(*j)++] = op; // Append the operator after the base and exponent
         skip_whitespace(infix, i);
     }
}


void parse_term(char* infix, char* postfix, int* i, int* j) {
    // A term starts with a factor
    parse_factor(infix, postfix, i, j);

    skip_whitespace(infix, i); // Skip whitespace after the first factor

    // While we see '*' or '/', parse the next factor and append the operator
    while (infix[*i] != '\0' && (infix[*i] == '*' || infix[*i] == '/')) {
        char op = infix[*i];
        (*i)++; // Consume the operator
        parse_factor(infix, postfix, i, j); // Parse the next factor (right operand)
        postfix[(*j)++] = op; // Append the operator after the two factors
        skip_whitespace(infix, i); // Skip whitespace
    }
}

// Function to parse an expression (terms connected by + or -)
// Consumes input from infix starting at index *i and writes to postfix starting at index *j
// Updates *i and *j
void parse_expression(char* infix, char* postfix, int* i, int* j) {
    // An expression starts with a term
    parse_term(infix, postfix, i, j);

    skip_whitespace(infix, i); // Skip whitespace after the first term

    // While we see '+' or '-', parse the next term and append the operator
    while (infix[*i] != '\0' && (infix[*i] == '+' || infix[*i] == '-')) {
        char op = infix[*i];
        (*i)++; // Consume the operator
        parse_term(infix, postfix, i, j); // Parse the next term (right operand)
        postfix[(*j)++] = op; // Append the operator after the two terms
        skip_whitespace(infix, i); // Skip whitespace
    }
}

void convert(char* infix, char* postfix, int* i, int* j) {
   
    *i = 0; // Start reading from the beginning of the infix string
    *j = 0; // Start writing to the beginning of the postfix string

    parse_expression(infix, postfix, i, j);

    postfix[*j] = '\0';

    skip_whitespace(infix, i);
}

