#ifndef QUEUE_H
#define QUEUE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
typedef struct {
	char message[100];
	int level;
}LogEntry;
typedef struct {
	LogEntry log[100];
	int head;
	int tail;
	int size;
}LogQueue;
__declspec(dllexport) void initializequeue(LogQueue *q);
__declspec(dllexport) int enqueue(LogQueue *p,const char *message,int level);
__declspec(dllexport) int dequeue(LogQueue *p, LogEntry *entry);
__declspec(dllexport) bool peek(LogQueue *p, LogEntry *etr);
__declspec(dllexport) bool isEmpty(LogQueue *p );
__declspec(dllexport) bool isFull(LogQueue *p );
#endif
