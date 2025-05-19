#include"linkedlist.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
	LogEntry* L = NULL;
    int choice;
    int size, id, pos,tar;
    while (1) {
        printf("\n=== Log Management System ===\n");
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
        printf("12. Sort Logs By Sev\n");
        printf("13. Reverse Logs\n");
        printf("14. Serch By Id\n");
        printf("15. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter the number of logs to generate: ");
                scanf("%d", &size);
                getchar();
                GenLog(&L, size);
                break;
            case 2:
                AddLogEntryAtTheBeginning(&L);
                break;
            case 3:
                AddLogEntryAtTheEnd(&L);
                break;
            case 4:
                printf("Enter the position: ");
                scanf("%d", &pos);
                getchar();
                InsertLogEntry(&L, pos);
                break;
            case 5:
                DisplayLogs(L);
                break;
            case 6:
                printf("Enter the ID of the log to delete: ");
                scanf("%d", &id);
                getchar();
                DelLogEntryByID(&L, id);
                break;
            case 7:
                DelLogAtTheBeginning(&L);
                break;
            case 8:
                DelLogAtTheEnd(&L);
                break;
            case 9:
                DelLogByTimeStamp(&L);
                break;
            case 10:
                L=SortLogsById(L, LogSize(L));
                printf("Logs sorted by ID.\n");
                break;
            case 11:
                printf("Number of logs: %d\n", LogSize(L));
                break;
            case 12:
                SortBySeverity(&L);
                break;
            case 13:
                ReverseLogs(&L);
                break;
            case 14:{
			
                printf("enter the target ID \n");
                scanf("%d",&tar);
                getchar();
                LogEntry*target=serchLogById(L,tar);
                break;}
            case 15:{
                while (L != NULL) {
                    LogEntry* temp = L;
                    L = L->next;
                    free(temp);
                }
                printf("Exiting program...\n");
                exit(0);
				break;}
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

