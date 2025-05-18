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
struct BsTLogEntry
{
    struct BsTLogEntry *left;
    int id;                   
    char message[100];        
    struct BsTLogEntry *right;
    char severity[10];        
    char timestamp[50];   
};
typedef struct BsTLogEntry BsTLogEntry;
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
    if (p==NULL)
    {
        return;
    }
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

    else if ((*L)->next==NULL)
    {
        free((*L));
        (*L)=NULL;
        return;
    }
    
    else
    {
        LogEntry*Tem=(*L);
        while (Tem->next->next!=NULL)
        {
            Tem=Tem->next;
        }
        LogEntry*fre=Tem->next;
        Tem->next=NULL;
        free(fre);
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
BsTLogEntry*CreateBstLogEntry(){
    BsTLogEntry* temp = (BsTLogEntry*)malloc(sizeof(BsTLogEntry));
    if (temp == NULL) {
        printf("\nMemory Allocation Failed\n");
        return NULL;
    }

    temp->id = ID++;
    temp->right = NULL;
    temp->left =NULL;
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
void ADDNode(BsTLogEntry* B,BsTLogEntry*New) {
    if (B==NULL)
    {
        return;
    }
    
    if (strcmp(New->timestamp,B->timestamp)>=0) {
        if (B->right == NULL) {
            B->right = New;
            return;
        } else {
            ADDNode((B->right),New);
        }
    } else {
        if (B->left == NULL) {
            B->left = New;
            return;
        } else {
            ADDNode((B->left),New);
        }
    }
}

void AddLogEntryToBst(BsTLogEntry**root,BsTLogEntry*new){
    if (*root==NULL)
    {
        *root=new;
        return ;
    }
    ADDNode(*root,new);
}
void displayBsTLogEntryColumn(BsTLogEntry *entry) {
    printf("%-5d | %-32s | %-10s | %-100s\n",
           entry->id, entry->timestamp, entry->severity, entry->message);
}

BsTLogEntry* findMinBstNode(BsTLogEntry* node) {
    BsTLogEntry* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

BsTLogEntry* DelBsTLogEntryNodeRecursive(BsTLogEntry* root, char target_timestamp[]) {

    if (root == NULL) {
        printf("Node with timestamp '%s' not found.\n", target_timestamp);
        return root;
    }
    int cmp = strcmp(target_timestamp, root->timestamp);
    if (cmp < 0) {
        root->left = DelBsTLogEntryNodeRecursive(root->left, target_timestamp);
    }
    else if (cmp > 0) {
        root->right = DelBsTLogEntryNodeRecursive(root->right, target_timestamp);
    }

    else {

        if (root->left == NULL) {
            BsTLogEntry* temp = root->right;
            free(root); 
            printf("Node with timestamp '%s' deleted.\n", target_timestamp);
            return temp; 
        } else if (root->right == NULL) {
            BsTLogEntry* temp = root->left;
            free(root);
            printf("Node with timestamp '%s' deleted.\n", target_timestamp);
            return temp; 
        }

        BsTLogEntry* temp = findMinBstNode(root->right);
        root->id = temp->id;
        strncpy(root->message, temp->message, sizeof(root->message) - 1);
        root->message[sizeof(root->message) - 1] = '\0';
        strncpy(root->severity, temp->severity, sizeof(root->severity) - 1);
        root->severity[sizeof(root->severity) - 1] = '\0';
        strncpy(root->timestamp, temp->timestamp, sizeof(root->timestamp) - 1);
        root->timestamp[sizeof(root->timestamp) - 1] = '\0';
        root->right = DelBsTLogEntryNodeRecursive(root->right, temp->timestamp);

    }
    return root;
}

void DelBsTLogEntryNode(BsTLogEntry** root, char target_timestamp[]) {
    if (*root == NULL) {
        printf("BST is empty. Cannot delete.\n");
        return;
    }
    *root = DelBsTLogEntryNodeRecursive(*root, target_timestamp);
}
void PrintBsTLogEntryInOrder(BsTLogEntry*B){
    if (B==NULL)
    {
        return;
    }
    PrintBsTLogEntryInOrder(B->left);
    displayBsTLogEntryColumn(B);
    PrintBsTLogEntryInOrder(B->right);
}
void PrintBsTLogEntryPreOrder(BsTLogEntry*B){
    if (B==NULL)
    {
        return;
    }
    displayBsTLogEntryColumn(B);
    PrintBsTLogEntryPreOrder(B->left);
    PrintBsTLogEntryPreOrder(B->right);
}
void PrintBsTLogEntryPostOrder(BsTLogEntry*B){
    if (B==NULL)
    {
        return;   
    }
    PrintBsTLogEntryPostOrder(B->left);
    PrintBsTLogEntryPostOrder(B->right);
    displayBsTLogEntryColumn(B);
}
BsTLogEntry*CreateNodeCpyToBst(LogEntry*original){
    if (original==NULL)
    {
        return NULL;
    }
    BsTLogEntry*root=malloc(sizeof(BsTLogEntry));
    if (root==NULL)
    {
        return root;
    }
    
    root->id=original->id;
    root->left=NULL;
    root->right=NULL;
    strncpy(root->timestamp,original->timestamp,sizeof(root->timestamp)-1);
    root->timestamp[sizeof(root->timestamp)-1]='\0';
    strncpy(root->severity,original->severity,sizeof(root->severity)-1);
    root->severity[sizeof(root->severity)-1]='\0';
    strncpy(root->message,original->message,sizeof(root->message)-1);
    root->message[sizeof(root->timestamp)-1]='\0';
    return root ;
}
BsTLogEntry*convertLogEntryToBst(LogEntry*H){
    if (H==NULL)
    {
        return NULL;
    }
    else
    {   
        BsTLogEntry*root=NULL;
        while (H!=NULL)
        {
            BsTLogEntry*New=CreateNodeCpyToBst(H);
            AddLogEntryToBst(&root,New);
            H=H->next;
        }
        return root;
    }
}
typedef struct node
{
    BsTLogEntry*val;
    struct node *next;
}node;
typedef struct Queue{
    node*front;
    node*rear;
}Queue;
Queue*createQueue(){
    Queue *Q =malloc(sizeof(Queue));
    Q->front=NULL;
    Q->rear=NULL;
    return Q;
}
void EnQueue(Queue*Q,BsTLogEntry*value){
    node *Temp=NULL;
    if (value==NULL)
    {
        return;
    }
    
    Temp=malloc(sizeof(node));
    if(Temp==NULL){
        return ;
    } 
    Temp->next=NULL;
    Temp->val=value;
    if(Q->front==NULL){
        Q->front=Temp;
            Q->rear=Temp;
        }
        else{
            Q->rear->next=Temp;
            Q->rear=Temp;
        }
}
BsTLogEntry* DeQueue(Queue*Q){
        if(Q->front==NULL){
            return NULL;
        }
        else if(Q->front->next==NULL){
            BsTLogEntry* val=Q->front->val;
            free(Q->front);
            Q->front=NULL;
            Q->rear=NULL;
            return val;
        }
        else{
            BsTLogEntry *val=Q->front->val;
            node * Temp =Q->front->next;
            free(Q->front);
            Q->front=Temp;
            return val;
        }
}
BsTLogEntry* findMinBstNodeAndDel(BsTLogEntry* node) {
    BsTLogEntry* current = node,*prev=NULL;

    while (current && current->left != NULL) {
        prev=current;
        current = current->left;
    }
    prev->left=NULL;
    return current;
}
bool isEmptyQueue(Queue*Q){
    return(Q->front==NULL&&Q->rear==NULL);
}
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
                    printf("Enter the timestamp of the log to delete from BST (e.g., 2023-12-25 15:30:45 W. Central Africa Standard Time):\n");
                    if (fgets(target_timestamp, sizeof(target_timestamp), stdin) == NULL) {
                        printf("Error reading input.\n");
                    } else {
                        size_t len = strlen(target_timestamp);
                        if (len > 0 && target_timestamp[len - 1] == '\n') {
                            target_timestamp[len - 1] = '\0';
                        }
                        // The recursive function prints deletion success/failure for a node
                        DelBsTLogEntryNode(&log_bst, target_timestamp);
                    }
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