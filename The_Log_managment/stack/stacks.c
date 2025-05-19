#include<stdio.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include"stacks.h"

void initializeStack(LogStack *s) {
    s->top = -1;
}
bool isStackEmpty(LogStack *s) {
    return (s->top == -1);
}
bool isStackFull(LogStack *s) {
    return (s->top == 100 - 1);
}
bool pushLog(LogStack *s, const char *message, int level) {
    if (isStackFull(s)) {
        printf("Cannot push because stack is full.\n");
        return false;
    }
    s->top++;
    strncpy(s->log[s->top].message, message, 100);
    s->log[s->top].level = level;
    return true;
}
bool popLog(LogStack *s, LogEntry *removed) {
    if (isStackEmpty(s)) {
        printf(" Nothing to pop because stack is empty.\n");
        return false;
    }
    *removed = s->log[s->top];
    s->top--;
    return true;
}
bool peekLog(LogStack *s, LogEntry *top) {
    if (isStackEmpty(s)) {
        printf("There is nothing to peek.\n");
        return false;
    }
    *top = s->log[s->top];
    return true;
}
const char* checkStackState(LogStack *s) {
    if (isStackEmpty(s)) {
	return "empty";
	}
    if (isStackFull(s)){
	return "full";
	} 
    return "there is space";
}
void insertAtBottom(LogStack *s, LogEntry item) {
    if (isStackEmpty(s)) {
        pushLog(s, item.message, item.level);
    } else {
        LogEntry temp;
        popLog(s, &temp);
        insertAtBottom(s, item);
        pushLog(s, temp.message, temp.level);
    }
}

void reverseStack(LogStack *s) {
    if (!isStackEmpty(s)) {
        LogEntry item;
        popLog(s, &item);
        reverseStack(s);
        insertAtBottom(s, item);
    }
}

void displayLog(LogEntry *entry) {
    printf("Level %d: %s\n", entry->level, entry->message);
}
