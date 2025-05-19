#ifndef DICTIONARY_H
#define DICTIONARY_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
struct TList
{
    char word [20];
    struct TList* next;
    char  word2[20];
    int indicator;
    int Chars;
    int Consonants;
    int Vowels;
};
typedef struct TList TList;
struct BTList
{
    char word [20];
    struct BTList* next;
    char  ant[20];
    struct BTList* prev;
    char  syn[20];
    int Chars;
    int Consonants;
    int Vowels;
};
typedef struct BTList BTList;
struct CTList
{
    char word [20];
    struct CTList* next;
    char  ant[20];
    int Chars;
    char  syn[20];
    int Consonants;
    int Vowels;
};
typedef struct CTList CTList;
struct TQueue
{
    BTList*head;
    BTList*tail;
};
typedef struct TQueue TQueue;
struct TStack
{
    BTList*top;
};
typedef struct TStack TStack;
struct TTree
{
    char word [20];
    struct TTree* right;
    char  ant[20];
    struct TTree* left;
    char  syn[20];
    int Chars;
    int Consonants;
    int Vowels;
};
typedef struct TTree TTree;
__declspec(dllexport) bool isCharacter(char C);
__declspec(dllexport) bool IsEmpty(TList*L);
__declspec(dllexport) int ListSize(TList*L);
__declspec(dllexport) void countVowelsConsonants(char str[], int* vowels, int* consonants);
__declspec(dllexport) TList* CreateNode();
__declspec(dllexport) BTList* BCreateNode();
__declspec(dllexport) TQueue* createQueue();
__declspec(dllexport) CTList* CCreateNode();
__declspec(dllexport) TTree* TCreateNode();
__declspec(dllexport) TList* getSynWords(FILE *file_name);
__declspec(dllexport) TList* getAntoWords(FILE *file_name);
__declspec(dllexport) void DisplayHeaderSyn();
__declspec(dllexport) void DisplayheaderAnt();
__declspec(dllexport) void printList(TList* head);
__declspec(dllexport) void DestroyList(TList*T);
__declspec(dllexport) void getInfWord(TList *syn, TList *ant, char *word);
__declspec(dllexport) TList* merge2List1(TList* h1, int size1, TList* h2, int size2);
__declspec(dllexport) TList* sortWord(TList *syn,int size);
__declspec(dllexport) TList* merge2List2(TList* h1, int size1, TList* h2, int size2);
__declspec(dllexport) TList* sortWord2(TList *syn,int size);
__declspec(dllexport) TList* merge2List3(TList* h1, int size1, TList* h2, int size2);
__declspec(dllexport) TList* sortWord3(TList *syn,int size);
__declspec(dllexport) TList* CreateNodeCpy(TList*original);
__declspec(dllexport) BTList* CreateBNodeCpy(BTList*original);
__declspec(dllexport) TList* countWord(TList *syn, char *prt);
__declspec(dllexport) bool isPalindrom(char str[]);
__declspec(dllexport) void InsertWithRespectToSort(TList**L,TList*new);
__declspec(dllexport) TList* palindromWord(TList *syn);
__declspec(dllexport) float CalculateRate(char str1[],char str2[]);
__declspec(dllexport) TList* similarWord(TList *syn, char *word, float rate);
__declspec(dllexport) void updateWordInFile(const char* word, const char* syne, const char* anton);
__declspec(dllexport) void updateWord(TList *syn, TList *ant, char *word, char *syne, char *anton);
__declspec(dllexport) BTList* merge(TList *syn, TList *ant);
__declspec(dllexport) CTList* merge2(TList *syn, TList *ant);
__declspec(dllexport) TList* addWord(TList *syn, TList *ant, char *word, char *syne, char *anton);
__declspec(dllexport) void DisplayHeader();
__declspec(dllexport) void printBList(BTList* head);
__declspec(dllexport) void DestroyBList(BTList*T);
__declspec(dllexport) void printCList(CTList* head);
__declspec(dllexport) void DestroyCList(CTList*T);
__declspec(dllexport) void EnQueue(TQueue**Q,BTList*value);
__declspec(dllexport) TQueue* toQueue(BTList*merged);
__declspec(dllexport) TStack* createStack();
__declspec(dllexport) void Push(TStack*stk,BTList*New);
__declspec(dllexport) bool IsEmptyStack(TStack*stk);
__declspec(dllexport) BTList* Pop(TStack*stk);
__declspec(dllexport) TStack* toStack(BTList *merged);
__declspec(dllexport) void getInfWordStack(TStack *stk, char *word);
__declspec(dllexport) void DestroyQueue(TQueue* Q);
__declspec(dllexport) void DestroyStack(TStack* S);
__declspec(dllexport) BTList* merge2ListB(BTList* h1, int size1, BTList* h2, int size2);
__declspec(dllexport) BTList* sortWordB(BTList *syn,int size);
__declspec(dllexport) int BTListSize(BTList*B);
__declspec(dllexport) TStack* sortWordStack(TStack *syn);
__declspec(dllexport) TStack* deleteWordStack(TStack *stk, char *word);
__declspec(dllexport) TStack* updateWordStack(TStack *stk, char *word, char *syne, char *anton);
__declspec(dllexport) BTList* DeQueue(TQueue*Q);
__declspec(dllexport) TQueue* stackToQueue(TStack *stk);
__declspec(dllexport) BTList* StacktoList(TStack *Stk);
__declspec(dllexport) BTList* Peek(TStack*stk);
__declspec(dllexport) TStack* addWordStack(TStack *stk, char *word, char *syne, char *anton);
__declspec(dllexport) bool isPalyndromeStack(char *word);
__declspec(dllexport) char* getSmallest(TStack *stk);
__declspec(dllexport) TStack* StackRev(TStack *stk);
__declspec(dllexport) void AddNodeToExistingTree(TTree*root,TTree*new);
__declspec(dllexport) void AddNodeToTree(TTree**root,TTree*New);
__declspec(dllexport) TTree* CpyBTListToTTree(BTList*original);
__declspec(dllexport) TTree* toTree(TStack *stk);
__declspec(dllexport) void PrintSingleColunm(TTree*root);
__declspec(dllexport) void printTreeInOrder(TTree*R);
__declspec(dllexport) void printTreePostOrder(TTree*R);
__declspec(dllexport) void printTreePreOrder(TTree*R);
__declspec(dllexport) TTree* fillTree(FILE *file_name);
__declspec(dllexport) void DestroyTree(TTree*R);
__declspec(dllexport) TTree* SerchInBst(TTree*root,char*word,int size);
__declspec(dllexport) TTree* getInfWordTree(TTree *root, char *word);
__declspec(dllexport) bool isMirrorS(TTree*l,TTree*r);
__declspec(dllexport) int height(TTree*R);
__declspec(dllexport) bool isBalencedBST(TTree *tr);
__declspec(dllexport) TTree* LowestCommonAncestor(TTree *root, char *word1, char *word2);
__declspec(dllexport) int CountNodesRanges(TTree *tr, int l, int h);
__declspec(dllexport) TTree* findSmallest(TTree*root);
__declspec(dllexport) TTree* deleteWordBST(TTree *tr, char *word);
__declspec(dllexport) void swapC(char* c, char* b);
__declspec(dllexport) void permutations(char str[], char* head);
__declspec(dllexport) void printSub(char str[]);
__declspec(dllexport) int countWordOccurence(FILE* file_name, char* word);
__declspec(dllexport) void DeleateWordInFile(FILE* original_file, char* word);
__declspec(dllexport) FILE* removeWordOccurence(FILE* f, char* word);
__declspec(dllexport) void updateWordItselfInFile(const char* word, const char* syne);
__declspec(dllexport) int countWordOccurenceInWord(FILE* file_name, char* word);
__declspec(dllexport) FILE* replaceWordOccurence(FILE* f, char* word, char* rep);
__declspec(dllexport) bool isPalindromWord(char* word, int size);
__declspec(dllexport) int distinctSubseqWord(char* word);
__declspec(dllexport) void handleListOperations(TList* syn, TList* ant, const char* filename);
__declspec(dllexport) void handleMergedListOperations(BTList** mergedList, CTList** circularMergedList, TQueue** queueFromList, TStack** stackFromList, TList* syn, TList* ant);
__declspec(dllexport) void handleStackOperations(TStack** stackFromList);
__declspec(dllexport) void handleQueueOperations(TQueue** queueFromList);
__declspec(dllexport) void handleTreeOperations(TTree** dictionaryTree, const char* filename);
__declspec(dllexport) void handleRecursionOperations();
#endif
