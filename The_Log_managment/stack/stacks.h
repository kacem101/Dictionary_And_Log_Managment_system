#ifndef STACK_H
#define STACK_H
typedef struct {
    char message[100];
    int level;
} LogEntry;
typedef struct {
    LogEntry log[100];
    int top;
} LogStack;

__declspec(dllexport) void initializeStack(LogStack *s);
__declspec(dllexport) bool isStackEmpty(LogStack *s);
__declspec(dllexport) bool isStackFull(LogStack *s);
__declspec(dllexport) bool pushLog(LogStack *s, const char *message, int level);
__declspec(dllexport) bool popLog(LogStack *s, LogEntry *removed) ;
__declspec(dllexport) bool peekLog(LogStack *s, LogEntry *top);
__declspec(dllexport) const char* checkStackState(LogStack *s);
__declspec(dllexport) void insertAtBottom(LogStack *s, LogEntry item);
__declspec(dllexport) void reverseStack(LogStack *s);
__declspec(dllexport) void displayLog(LogEntry *entry);
#endif
