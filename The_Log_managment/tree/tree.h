#ifndef TREE_H
#define TREE_H
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
typedef struct BsTLogEntry {
    int id;
    char timestamp[50];
    struct BsTLogEntry *left;
    char severity[10];
    struct BsTLogEntry *right;
    char message[100];
} BsTLogEntry;

typedef struct node {
    BsTLogEntry* val;
    struct node *next;
} node;

typedef struct Queue {
    node* front;
    node* rear;
} Queue;
__declspec(dllexport) void displayLogHeader();
__declspec(dllexport) void displayLogEntryColumn(LogEntry *entry);
__declspec(dllexport) char* getCurrentTimeString();
__declspec(dllexport) void InsertLogEntry(LogEntry** L, int pos);
__declspec(dllexport) void InsertLogEntryByPos(LogEntry** L);
__declspec(dllexport) void DisplayLogs(LogEntry* L);
__declspec(dllexport) void GenLog(LogEntry** L, int size);
__declspec(dllexport) void DelLogEntryByID(LogEntry**L,int ID);
__declspec(dllexport) LogEntry*CreateLogEntry();
__declspec(dllexport) bool IsLogsEmpty(LogEntry*L);
__declspec(dllexport) void AddLogEntryAtTheBeginning(LogEntry**L);
__declspec(dllexport) void AddLogEntryAtTheEnd(LogEntry**L);
__declspec(dllexport) void DelLogAtTheBeginning(LogEntry**L);
__declspec(dllexport) void DelLogAtTheEnd(LogEntry**L);
__declspec(dllexport) int LogSize(LogEntry*L);
__declspec(dllexport) bool isValidDateTime(int year, int month, int day,int hour, int minutes, int seconds);
__declspec(dllexport) void DelLogByTimeStamp(LogEntry** L);
__declspec(dllexport) LogEntry* merge2List(LogEntry* h1, int size1, LogEntry* h2, int size2);
__declspec(dllexport) LogEntry* SortLogsById(LogEntry*head,int size);
__declspec(dllexport) LogEntry* CopySingleLogEntry(const LogEntry* original);
__declspec(dllexport) void ReverseLogs(LogEntry**H);
__declspec(dllexport) void SortBySeverity(LogEntry** head);
__declspec(dllexport) LogEntry* serchLogById(LogEntry*L,int ID);
__declspec(dllexport) BsTLogEntry* CreateBstLogEntry();

__declspec(dllexport) void AddLogEntryToBst(BsTLogEntry** root, BsTLogEntry* new_node);

__declspec(dllexport) void DelBsTLogEntryNode(BsTLogEntry** root, char target_timestamp[]);

__declspec(dllexport) void displayBsTLogEntryColumn(BsTLogEntry *entry);

__declspec(dllexport) void PrintBsTLogEntryInOrder(BsTLogEntry* root);
__declspec(dllexport) void PrintBsTLogEntryPreOrder(BsTLogEntry* root);
__declspec(dllexport) void PrintBsTLogEntryPostOrder(BsTLogEntry* root);

__declspec(dllexport) BsTLogEntry* CreateNodeCpyToBst(LogEntry* original);

__declspec(dllexport) BsTLogEntry* convertLogEntryToBst(LogEntry* H);

__declspec(dllexport) Queue* createQueue();

__declspec(dllexport) void EnQueue(Queue* Q, BsTLogEntry* value);

__declspec(dllexport) BsTLogEntry* DeQueue(Queue* Q);
#endif










