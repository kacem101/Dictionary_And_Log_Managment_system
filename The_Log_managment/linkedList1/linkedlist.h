#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
struct LogEntry {                   
    char message[100];        
    struct LogEntry *next;
    char severity[10];
	int id;        
    char timestamp[50];       
};
typedef struct LogEntry LogEntry;
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
#endif
