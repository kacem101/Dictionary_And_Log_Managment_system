#include<stdio.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include"queue.h"

void initializequeue(LogQueue *p){
	p->head=0;
	p->tail=-1;
	p->size=0;
}
int enqueue(LogQueue* p,const char *message,int level){
	if (p->size==100)
	{
		printf("U cannot add new elements because it is full.\n");
	}
	p->tail = (p->tail + 1) % 100;
    strncpy(p->log[p->tail].message, message, 100 - 1);
    p->log[p->tail].message[100 - 1] = '\0';
    p->log[p->tail].level = level;
    p->size++;
    return 1;
}
int dequeue(LogQueue *p, LogEntry *entry) {
    if (p->size == 0) {
        printf("Cannot dequeue because it is empty.\n");
        return 0; 
    }
    *entry = p->log[p->head];
    p->head = (p->head + 1) % 100;
    p->size--;

    return 1;
}
bool peek(LogQueue *p, LogEntry *etr){
	if (p->size == 0) {
        printf("there is nothing to peek because it is empty.\n");
        return false;
    }
     *etr = p->log[p->head];
    return true; 
}
bool isEmpty(LogQueue *p ){
	if (p->size == 0) {
        printf("Queue is empty.\n");
        return true; 
    }
    else{
    	return false;
	}
}
bool isFull(LogQueue *p ){
	if (p->size == 100) {
        printf("Queue is full.\n");
        return true; 
    }
    else{
    	return false;
	}
}
