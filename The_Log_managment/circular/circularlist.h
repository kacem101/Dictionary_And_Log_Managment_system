#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#define FIXED_BUFFER_SIZE 100
#define LOG_STACK_SIZE 100
struct LogEntry {
    int id;                   
    char message[100];        
    struct LogEntry *next;
    char severity[10];        
    char timestamp[50];
};    
typedef struct LogEntry LogEntry;
typedef struct {
    char *message;
    int level;
    char timestamp[50];
} LogEtr;
typedef struct {
    int capacity;
	int size;
	char timestamp[50];
    LogEtr logs[100];
    int top;
} LogStack;  


__declspec(dllexport) bool isStackEmpty(LogStack *s);
__declspec(dllexport) bool isStackFull(LogStack *s);
__declspec(dllexport) void displayLogHeader();
__declspec(dllexport) void displayLogEntryColumn(LogEntry *entry);
__declspec(dllexport) bool isLogListEmpty();
__declspec(dllexport) bool isLogListFull();
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
__declspec(dllexport) void addToFixedBuffer(const char* message, int level);
__declspec(dllexport) bool isFixedBufferEmpty();
__declspec(dllexport) bool isFixedBufferFull();
__declspec(dllexport) bool hasCycle(LogStack* s);
__declspec(dllexport) bool pushLog(LogStack* s, const char* message, int level);
__declspec(dllexport) void insertAtBottom(LogStack* s, LogEntry item);
__declspec(dllexport) void freeFixedBuffer(); // Added function prototype for freeing fixed buffer messages
__declspec(dllexport) bool hasCycle(LogStack* s); // Checks for cycle in the stack array addresses
__declspec(dllexport) void initLogStack(LogStack* s); // Added function prototype for stack initialization
__declspec(dllexport) void freeLogStack(LogStack* s); // Added function prototype for freeing stack memory
__declspec(dllexport) void displayLogStack(LogStack* s);
#endif
