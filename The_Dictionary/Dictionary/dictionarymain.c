#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include"dictionary.h"



int main(){
    FILE*file;
    TList*Syn=NULL,*Ant=NULL;
    BTList *MergedList = NULL;
    CTList *CircularMergedList = NULL;
    TQueue *QueueFromList = NULL;
    TStack *StackFromList = NULL;
    TTree *DictionaryTree = NULL;
    int choice;
    bool running = true;
    const char* filename = "file.txt";

    // --- File Loading ---
    file=fopen(filename,"r");
    if (file == NULL) {
        perror("Error opening file 'file.txt'");
        file = fopen(filename, "w");
        if (file == NULL) {
             perror("Error creating file 'file.txt'");
             return 1;
        }
        fclose(file);
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file 'file.txt' after creation");
            return 1;
        }
        printf("Created empty file '%s'.\n", filename);
    }

    printf("Loading data from %s...\n", filename);
    // Assuming getSynWords and getAntoWords read from the file and populate the lists
    Syn=getSynWords(file);
    if (Syn == NULL && !feof(file)) {
        fprintf(stderr, "Warning: Error or empty content loading synonyms from file.\n");
    }
    rewind(file); // Reset file pointer to the beginning for the next read
    Ant=getAntoWords(file);
     if (Ant == NULL && !feof(file)) {
        fprintf(stderr, "Warning: Error or empty content loading antonyms from file.\n");
    }
    fclose(file); // Close the file after loading
    printf("Data loaded.\n");
    printf("\n");

    // --- Main Menu Loop ---
    while (running) {
        printf("========== Main Dictionary Menu ==========\n");
        printf(" 1. List Operations (Synonyms/Antonyms)\n");
        printf(" 2. Merged List Operations (Doubly/Circular)\n");
        printf(" 3. Stack Operations\n");
        printf(" 4. Queue Operations\n");
        printf(" 5. Tree Operations\n");
        printf(" 6. Recursion Operations\n"); // Added new option
        printf(" 7. Exit\n"); // Updated exit option number
        printf("=========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1: // List Operations
                handleListOperations(Syn, Ant, filename);
                break;
            case 2: // Merged List Operations
                handleMergedListOperations(&MergedList, &CircularMergedList, &QueueFromList, &StackFromList, Syn, Ant);
                break;
            case 3: // Stack Operations
                handleStackOperations(&StackFromList);
                break;
            case 4: // Queue Operations
                handleQueueOperations(&QueueFromList);
                break;
            case 5: // Tree Operations
                handleTreeOperations(&DictionaryTree, filename);
                break;
            case 6: // Recursion Operations - New Case
                handleRecursionOperations();
                break;
            case 7: // Exit - Updated case number
                printf("Exiting program.\n");
                running = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n"); // Updated range
        }
        if (running) {
             printf("\nPress Enter to continue...");
             getchar(); // Wait for user to press Enter
             printf("\n");
        }
    }

    // --- Cleanup Resources ---
    printf("\n--- Cleaning up resources ---\n");
    DestroyList(Syn); // Assuming DestroyList frees nodes
    DestroyList(Ant); // Assuming DestroyList frees nodes
    if (MergedList != NULL) { DestroyBList(MergedList); MergedList = NULL; } // Assuming DestroyBList frees nodes
    if (CircularMergedList != NULL) { DestroyCList(CircularMergedList); CircularMergedList = NULL; } // Assuming DestroyCList frees nodes
    if (QueueFromList != NULL) { DestroyQueue(QueueFromList); QueueFromList = NULL; } // Assuming DestroyQueue frees nodes and its contents
    if (StackFromList != NULL) {
         printf("Cleaning up Stack (if it owns nodes)...\n");
         // Assuming Pop returns a node and DestroyStack frees the stack structure itself.
         // If the stack nodes are the same nodes from MergedList, freeing them here
         // after destroying MergedList would be a double free.
         // Based on the original comment, it seems the stack *owns* nodes,
         // implying they might be copies or transferred ownership.
         // If Pop returns a pointer to the node structure itself, and the stack
         // allocated these nodes, then freeing them here is correct.
         // If the stack just holds pointers to nodes owned elsewhere (like in MergedList),
         // then only the stack structure needs freeing, not the popped nodes.
         // Given the original comment's explicit node freeing loop, we'll keep it,
         // but this highlights a potential memory management ambiguity.
         while (!IsEmptyStack(StackFromList)) {
             BTList* node = Pop(StackFromList);
             if (node != NULL) {
                 // Free the node if the stack owns it.
                 free(node); // This might be incorrect if nodes are shared/owned by MergedList
             }
         }
         free(StackFromList); // Free the stack structure
         StackFromList = NULL;
         printf("Stack and its nodes freed.\n");
    }
     if (DictionaryTree != NULL) {
         printf("Cleaning up Tree...\n");
         DestroyTree(DictionaryTree); // Assuming DestroyTree frees nodes
         DictionaryTree = NULL;
         printf("Tree freed.\n");
     }
    printf("Cleanup complete. Goodbye!\n");

    return 0;
}

