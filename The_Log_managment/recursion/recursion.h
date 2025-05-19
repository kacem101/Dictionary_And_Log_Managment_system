#ifndef RECURSION_H
#define RECURSION_H
struct LogEntry {
    int id;                   
    char message[100];        
    struct LogEntry *next;
    char severity[10];        
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
__declspec(dllexport) void DelLogByTimeStamp(LogEntry** L);
__declspec(dllexport) LogEntry* merge2List(LogEntry* h1, int size1, LogEntry* h2, int size2);
__declspec(dllexport) LogEntry* SortLogsById(LogEntry*head,int size);
__declspec(dllexport) LogEntry* CopySingleLogEntry(const LogEntry* original);
__declspec(dllexport) void ReverseLogs(LogEntry**H);
__declspec(dllexport) void SortBySeverity(LogEntry** head);
__declspec(dllexport) LogEntry* serchLogById(LogEntry*L,int ID);
__declspec(dllexport) int factorial(int n);
__declspec(dllexport) int fibonachiSeries(int n);
__declspec(dllexport) void ReverseWithRecursion(LogEntry**L);
__declspec(dllexport) int FindMAxLogId(LogEntry*L);
__declspec(dllexport) int isOperator(char c);
__declspec(dllexport) int precedence(char op);
__declspec(dllexport) void skip_whitespace(char* infix, int* i);
__declspec(dllexport) void parse_expression(char* infix, char* postfix, int* i, int* j);
__declspec(dllexport) void parse_term(char* infix, char* postfix, int* i, int* j);
__declspec(dllexport) void parse_factor(char* infix, char* postfix, int* i, int* j);
__declspec(dllexport) void convert(char* infix, char* postfix, int* i, int* j);
#endif

