#ifndef BILIST_H
#define BILIST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

struct BLogEntry {
    int id;
    char message[100];
    struct BLogEntry *next;
    char timestamp[50];
    struct BLogEntry *prev;
    char severity[10];
};
typedef struct BLogEntry BLogEntry;

__declspec(dllexport) void displayBLogHeader();
__declspec(dllexport) void displayBLogEntryColumn(BLogEntry *entry);
__declspec(dllexport) void displaySelBLogEntryColumn(BLogEntry *entry); // Corrected declaration
__declspec(dllexport) char* BgetCurrentTimeString(); // Corrected function name
__declspec(dllexport) void InsertBLogEntryBI(BLogEntry** L, int pos);
__declspec(dllexport) void InsertBLogEntryByPosBI(BLogEntry** L);
__declspec(dllexport) void DisplayBLogs(BLogEntry* L,int pos); // Corrected function name
__declspec(dllexport) void GenLogBI(BLogEntry** L, int size);
__declspec(dllexport) void DelBLogEntryByID(BLogEntry**L,int ID);
__declspec(dllexport) BLogEntry* CreateBLogEntryBI(); // Corrected function name
__declspec(dllexport) bool IsBLogsEmpty(BLogEntry*L); // Corrected function name
__declspec(dllexport) void AddBLogEntryAtTheBeginning(BLogEntry**L);
__declspec(dllexport) void AddBLogEntryAtTheEndBI(BLogEntry**L);
__declspec(dllexport) void DelBLogAtTheBeginning(BLogEntry**L); // Corrected function name
__declspec(dllexport) void DelBLogAtTheEnd(BLogEntry**L); // Corrected function name
__declspec(dllexport) int BLogSize(BLogEntry*L); // Corrected function name
__declspec(dllexport) bool isValidDateTimeB(int year, int month, int day,int hour, int minutes, int seconds); // Corrected function name
__declspec(dllexport) void DelBLogByTimeStamp(BLogEntry** L) ; // Corrected function name
__declspec(dllexport) BLogEntry* merge2ListBI(BLogEntry* h1, int size1, BLogEntry* h2, int size2) ;
__declspec(dllexport) BLogEntry* SortLogsByIdBI(BLogEntry*head,int size);
__declspec(dllexport) BLogEntry* CopySingleBLogEntry(const BLogEntry* original);
__declspec(dllexport) void ReverseLogsBI(BLogEntry**H);
__declspec(dllexport) void SortBySeverityBI(BLogEntry** head);
__declspec(dllexport) BLogEntry* serchLogById(BLogEntry*L,int ID);
__declspec(dllexport) void MoveForward(BLogEntry*L,int* pos);
__declspec(dllexport) void MoveBackward(BLogEntry*L,int* pos);
__declspec(dllexport) void ReturnToBegining(BLogEntry*L,int*pos);
__declspec(dllexport) void DelBLogByPos(BLogEntry** L, int pos); // Corrected function name
__declspec(dllexport) void SerchByKeyWord(BLogEntry*H);

#endif
