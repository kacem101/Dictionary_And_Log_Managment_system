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
bool isCharacter(char C){
    return (C<=90&&C>=65)||(C>=97&&C<=122);
}
bool IsEmpty(TList*L){
    return (L==NULL);
}
int ListSize(TList*L){

    bool v=IsEmpty(L);

    if (v)
    {
        return 0;
    }
    else
    {
        int counter=0;
        while (L!=NULL)
        {
            counter++;
            L=L->next;
        }
        return counter;
    }
    
}
void countVowelsConsonants(char str[], int* vowels, int* consonants){
	int i,l;
	bool v;
	l=strlen(str);
	*vowels=0;
	*consonants=0;
	for(i=0;i<l;i++){
		v=isCharacter(str[i]);
		if(v){
			if(str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='y'||str[i]=='e'||str[i]=='a'||
                str[i]=='I'||str[i]=='O'||str[i]=='U'||str[i]=='Y'||str[i]=='E'||str[i]=='A'){
				*vowels=* vowels+1;
			}
			else{
				*consonants= *consonants+1;
			}
		}
	}
}
TList*CreateNode(){
    TList *T=malloc(sizeof(TList));
    if (T==NULL)
    {
        return NULL;
    }
    T->next=NULL;
    T->word[0]='\0';
    T->word2[0]='\0';
    T->indicator=-1;
    T->Chars=0;
    T->Consonants=0;
    T->Vowels=0;
    return T;
}
BTList*BCreateNode(){
    BTList *T=malloc(sizeof(BTList));
    if (T==NULL)
    {
        return NULL;
    }
    T->next=NULL;
    T->prev=NULL;
    T->word[0]='\0';
    T->syn[0]='\0';
    T->ant[0]='\0';
    T->Chars=0;
    T->Consonants=0;
    T->Vowels=0;
    return T;
}
TQueue*createQueue(){
    TQueue*Q=malloc(sizeof(TQueue));
    Q->head=BCreateNode();
    Q->tail=Q->head;
    return Q;
}
CTList*CCreateNode(){
    CTList *T=malloc(sizeof(CTList));
    if (T==NULL)
    {
        return NULL;
    }
    T->next=NULL;
    T->word[0]='\0';
    T->syn[0]='\0';
    T->ant[0]='\0';
    T->Chars=0;
    T->Consonants=0;
    T->Vowels=0;
    return T;
}
TTree*TCreateNode(){
    TTree *T=malloc(sizeof(TTree));
    if (T==NULL)
    {
        return NULL;
    }
    T->right=NULL;
    T->left=NULL;
    T->word[0]='\0';
    T->syn[0]='\0';
    T->ant[0]='\0';
    T->Chars=0;
    T->Consonants=0;
    T->Vowels=0;
    return T;
}
TList *getSynWords(FILE *file_name){
    char buffer[100]; 
    int checker;
    TList*T=NULL,*Temp=NULL,*Tail=NULL;
    while (fgets(buffer, sizeof(buffer), file_name)!=NULL)
        {
            char word[20];
            char syn[20];
            checker=sscanf(buffer, "%19[^=]=%19[^#]", word, syn);
            if (checker==2)
            {
                printf("word: %s, syn: %s\n", word, syn);
                if (T==NULL)
                {
                    T=CreateNode();

                    if (T==NULL)
                    {
                        return T;
                    }
                    
                    strncpy(T->word,word,sizeof(T->word)-1);

                    T->word[sizeof(T->word)-1]='\0';

                    strncpy(T->word2,syn,sizeof(T->word2)-1);

                    T->word2[sizeof(T->word2)-1]='\0';

                    T->indicator=0;

                    countVowelsConsonants(T->word,&(T->Vowels),&(T->Consonants));

                    T->Chars=T->Vowels+T->Consonants;

                    Tail=T;
                }
                else
                {   
                    Temp=CreateNode();

                    strncpy(Temp->word,word,sizeof(Temp->word)-1);

                    Temp->word[sizeof(Temp->word)-1]='\0';

                    strncpy(Temp->word2,syn,sizeof(Temp->word2)-1);

                    Temp->word2[sizeof(Temp->word2)-1]='\0';

                    Temp->indicator=0;

                    countVowelsConsonants(Temp->word,&(Temp->Vowels),&(Temp->Consonants));

                    Temp->Chars=Temp->Vowels+Temp->Consonants;
                    
                    Tail->next=Temp;

                    Tail=Tail->next;
                }
            }
            else
            {
                printf("Error in reading\n");
                return T;
            }
        }
        return T;
}
TList *getAntoWords(FILE *file_name){
    char buffer[100]; 
    int checker;
    TList*T=NULL,*Temp=NULL,*Tail=NULL;
    while (fgets(buffer, sizeof(buffer), file_name)!=NULL)
        {
            char word[20];
            char ant[20];
            char syn[20];
            checker=sscanf(buffer, "%19[^=]=%*19[^#]#%19[^\n]",word,ant);
            if (checker==2)
            {
                printf("word: %s, syn: %s\n", word, ant);
                if (T==NULL)
                {
                    T=CreateNode();

                    if (T==NULL)
                    {
                        return T;
                    }
                    
                    strncpy(T->word,word,sizeof(T->word)-1);

                    T->word[sizeof(T->word)-1]='\0';

                    strncpy(T->word2,ant,sizeof(T->word2)-1);

                    T->word2[sizeof(T->word2)-1]='\0';

                    T->indicator=1;

                    countVowelsConsonants(T->word,&(T->Vowels),&(T->Consonants));

                    T->Chars=T->Vowels+T->Consonants;

                    Tail=T;
                }
                else
                {   
                    Temp=CreateNode();

                    strncpy(Temp->word,word,sizeof(Temp->word)-1);

                    Temp->word[sizeof(Temp->word)-1]='\0';

                    strncpy(Temp->word2,ant,sizeof(Temp->word2)-1);

                    Temp->word2[sizeof(Temp->word2)-1]='\0';

                    Temp->indicator=1;

                    countVowelsConsonants(Temp->word,&(Temp->Vowels),&(Temp->Consonants));

                    Temp->Chars=Temp->Vowels+Temp->Consonants;
                    
                    Tail->next=Temp;

                    Tail=Tail->next;
                }
            }
            else
            {
                printf("Error in reading\n");
                return T;
            }
        }
        return T;
}
void DisplayHeaderSyn(){
    printf("  %-20s | %-20s | %-8s | %-10s | %-10s | \n","Synonym", "Type", "Vowels", "Consonants", "Chars");
    printf("  ---------------------|----------------------|----------|----------|------------|-------------\n");
}
void DisplayheaderAnt(){
    printf("  %-20s | %-20s | %-8s | %-10s | %-10s | \n","Antonym", "Type", "Vowels", "Consonants", "Chars");
    printf("  ---------------------|----------------------|----------|----------|------------|-------------\n");
}
void printList(TList* head) {
    TList* current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Contents of the list:\n");
    head->indicator==0 ? DisplayHeaderSyn() : DisplayheaderAnt();
    while (current != NULL) {
        if (current->indicator==0)
        {
            printf("  %-20s = %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->word2,current->Vowels,current->Consonants,current->Chars);
        }
        else if (current->indicator==1)
        {
            printf("  %-20s # %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->word2,current->Vowels,current->Consonants,current->Chars);
        }
        else
        {
            printf("it is empty or an error in indicator settings\n");
        }

        current = current->next;
    }
}
void DestroyList(TList*T){
    printf("Freeing list memory...\n");
    if (T==NULL)
    {
        return;
    }
    TList*Current=T;
    while (T!=NULL)
    {
        Current=T;
        T=T->next;
        free(Current);
    }
    printf("List memory freed.\n");
}
void getInfWord(TList *syn, TList *ant, char *word){
    char TSyn[20];
    char TAnt[20];
    bool FoundAnt=false,CheckSyn=true;
    bool FoundSyn=false,CheckAnt=true;
    int Vow=0,Cons=0,Cha=0;
    if (syn==NULL||syn->indicator==1)
    {
        CheckSyn=false;
    }
    if (ant==NULL||syn->indicator==0)
    {
        CheckAnt=false;
    }
    countVowelsConsonants(word,&Vow,&Cons);
    printf("Word : %-20s Vowles : %d Consonants %d \n",word,Vow,Cons,Vow+Cons);
    printf("--------------------\n");


        printf("Synonymes of this word \n");
        printf("--------------------\n");
        while (syn!=NULL)
        {
            if (strcmp(word,syn->word)==0)
            {
                printf("-%-20s\n",syn->word2);
                printf("--------------------\n");
            }
            if (strcmp(word,syn->word2)==0)
            {
                printf("-%-20s\n",syn->word);
                printf("--------------------\n");
            }
            
            syn=syn->next;
        }    
    
        printf("Antonymes of this word \n");
        printf("--------------------\n");
        while (ant!=NULL)
        {
            if (strcmp(word,ant->word)==0)
            {
                printf("-%-20s\n",ant->word2);
                printf("--------------------\n");
            }
            if (strcmp(word,ant->word2)==0)
            {
                printf("-%-20s\n",ant->word);
                printf("--------------------\n");
            }
            
            ant=ant->next;
        }
    
}
TList* merge2List1(TList* h1, int size1, TList* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    TList*dummy = malloc(sizeof(TList));  
    TList* tail = dummy;
    dummy->next = NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
        if (strcmp(h1->word,h2->word)>0) {
            tail->next = h2;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        tail = tail->next;
        count2++;
    }

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    TList* result = dummy->next;
    free(dummy);
    return result;
}

TList *sortWord(TList *syn,int size){
    if(size<=1){
        return syn;
    }
    int mid=size/2,counter=0;
    TList* p1=syn,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
    while(counter<mid-1){
        p1=p1->next;
        counter++;
    }
    p2=p1->next;
    t=p1;
    p1=p1->next;
    if (t!=NULL)
    {
        t->next=NULL;
    }
    else
    {
        if (p1->next==NULL)
        {
            p2=NULL;
        }
        else
        {
            p2=p1->next;
        }
    }
    r1=sortWord(syn,mid);
    r2=sortWord(p2,size-mid);
    syn=merge2List1(r1,mid,r2,size-mid);
    return syn;
}
TList* merge2List2(TList* h1, int size1, TList* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    TList*dummy = malloc(sizeof(TList));  
    TList* tail = dummy;
    dummy->next = NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
        if (h1->Chars>h2->Chars) {
            tail->next = h2;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        tail = tail->next;
        count2++;
    }

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    TList* result = dummy->next;
    free(dummy);
    return result;
}

TList *sortWord2(TList *syn,int size){
    if(size<=1){
        return syn;
    }
    int mid=size/2,counter=0;
    TList* p1=syn,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
    while(counter<mid-1){
        p1=p1->next;
        counter++;
    }
    p2=p1->next;
    t=p1;
    p1=p1->next;
    if (t!=NULL)
    {
        t->next=NULL;
    }
    else
    {
        if (p1->next==NULL)
        {
            p2=NULL;
        }
        else
        {
            p2=p1->next;
        }
    }
    r1=sortWord2(syn,mid);
    r2=sortWord2(p2,size-mid);
    syn=merge2List2(r1,mid,r2,size-mid);
    return syn;
}
TList* merge2List3(TList* h1, int size1, TList* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    TList*dummy = malloc(sizeof(TList));  
    TList* tail = dummy;
    dummy->next = NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
        if (h1->Vowels<h2->Vowels) {
            tail->next = h2;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        tail = tail->next;
        count2++;
    }

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    TList* result = dummy->next;
    free(dummy);
    return result;
}

TList *sortWord3(TList *syn,int size){
    if(size<=1){
        return syn;
    }
    int mid=size/2,counter=0;
    TList* p1=syn,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
    while(counter<mid-1){
        p1=p1->next;
        counter++;
    }
    p2=p1->next;
    t=p1;
    p1=p1->next;
    if (t!=NULL)
    {
        t->next=NULL;
    }
    else
    {
        if (p1->next==NULL)
        {
            p2=NULL;
        }
        else
        {
            p2=p1->next;
        }
    }
    r1=sortWord3(syn,mid);
    r2=sortWord3(p2,size-mid);
    syn=merge2List3(r1,mid,r2,size-mid);
    return syn;
}
TList*CreateNodeCpy(TList*original){
    if (original==NULL)
    {
        return NULL;
    }
    
    TList*L=CreateNode();
    L->Chars=original->Chars;
    L->Consonants=original->Consonants;
    L->indicator=original->indicator;
    L->next=NULL;
    L->Vowels=original->Vowels;
    strncpy(L->word,original->word,sizeof(L->word)-1);
    L->word[sizeof(L->word)-1]='\0';
    strncpy(L->word2,original->word2,sizeof(L->word2)-1);
    L->word2[sizeof(L->word2)-1]='\0';
    return L ;
}
BTList*CreateBNodeCpy(BTList*original){
    if (original==NULL)
    {
        return NULL;
    }
    
    BTList*L=BCreateNode();
    L->Chars=original->Chars;
    L->Consonants=original->Consonants;
    L->next=NULL;
    L->prev=NULL;
    L->Vowels=original->Vowels;
    strncpy(L->word,original->word,sizeof(L->word)-1);
    L->word[sizeof(L->word)-1]='\0';
    strncpy(L->syn,original->syn,sizeof(L->syn)-1);
    L->syn[sizeof(L->syn)-1]='\0';
    strncpy(L->ant,original->ant,sizeof(L->ant)-1);
    L->ant[sizeof(L->ant)-1]='\0';
    return L ;
}
TList *countWord(TList *syn, char *prt){
    if (syn==NULL)
    {
        return NULL;
    }
    TList* FalseHead=malloc(sizeof(TList)),*tail=FalseHead;
    FalseHead->next=NULL;
    while (syn!=NULL)
    {
        if (strstr(syn->word,prt)!=NULL||strstr(syn->word2,prt)!=NULL)
        {   
            tail->next=CreateNodeCpy(syn);
            tail=tail->next;
        }
        syn=syn->next;
    }
    return FalseHead->next;
}
bool isPalindrom(char str[]){
    int size=strlen(str);
    if (size==0)
    {
        return true;
    }
    for (int i = 0; i < size/2; i++)
    {
        if (str[i]!=str[size-1-i]&&str[i]!=str[size-1-i]-32)
        {
            return false;
        }  
    }
    return true;
}
void InsertWithRespectToSort(TList**L,TList*new){
    if (new==NULL)
    {
        return;
    }
    
    if (*L==NULL)
    {
        *L=new;
        return;
    }
    if (strcmp(new->word,(*L)->word)<0)
    {
        new->next=*L;
        (*L)=new;
        return;
    }
    TList*Temp=*L;
    while (Temp->next!=NULL)
    {
        if (strcmp(new->word,Temp->next->word)>0)
        {
            break;
        }
    }
    new->next=Temp->next;
    Temp->next=new;
    return;
}
TList *palindromWord(TList *syn){
    if (syn==NULL)
    {
        return NULL;
    }
    TList*Head=NULL;
    while (syn!=NULL)
    {
        if (isPalindrom(syn->word)||isPalindrom(syn->word2))
        {
            InsertWithRespectToSort(&Head,CreateNodeCpy(syn));
        }
        syn=syn->next;
    }

    return Head;
}
float CalculateRate(char str1[],char str2[]){
    int size,full;
    float rate=0;
    if (strlen(str1)>strlen(str2)){
        full=strlen(str1);
    }
    else
    {
        full=strlen(str2);
    }
    if (strlen(str1)<strlen(str2))
    {
        size=strlen(str1);
    }
    else
    {
        size=strlen(str2);
    }
    for (int i = 0; i < size; i++)
    {
        if (str1[i]==str2[i]||str1[i]==str2[i]+32||str1[i]==str2[i]-32)
        {
            rate++;
        }
    }
    return (rate/full);
}
TList *similarWord(TList *syn, char *word, float rate){
    if (syn==NULL)
    {
        return NULL;
    }
    TList*falseHead=CreateNode(),*tail=falseHead;
    while (syn!=NULL)
    {
        if (CalculateRate(syn->word,word)>=rate||CalculateRate(syn->word2,word)>=rate)
        {
            tail->next=CreateNodeCpy(syn);
            tail=tail->next;
        }
        syn=syn->next;
    }
    return falseHead->next;
}
void updateWordInFile(const char* word, const char* syne, const char* anton){
    // Validate inputs to ensure they are not NULL
    if (word == NULL || syne == NULL || anton == NULL) {
        fprintf(stderr, "Error: Invalid input to updateWordInFile. Word, synonym, and antonym must be non-NULL.\n");
        return;
    }

    // Hardcoded filename - This function will always operate on this file.
    const char* filename = "file.txt";

    FILE *original_file, *temp_file;
    char buffer[256]; // Buffer to read lines from the file. Adjust size if lines can be longer.
    char temp_filename[] = "temp_dict.txt"; // Name for the temporary file
    bool found_and_updated = false; // Flag to track if the word was found and its line was updated

    // Open the original file for reading ("r" mode)
    original_file = fopen(filename, "r");
    if (original_file == NULL) {
        perror("Error opening original file for update");
        // If the file doesn't exist, we can't update it.
        return;
    }

    // Open a temporary file for writing ("w" mode). This file will hold the updated content.
    temp_file = fopen(temp_filename, "w");
    if (temp_file == NULL) {
        perror("Error creating temporary file for update");
        fclose(original_file); // Close the original file before exiting
        return; // Exit if the temporary file cannot be created
    }

    printf("Updating file '%s' for word '%s'...\n", filename, word);

    // Read the original file line by line until the end of the file (NULL is returned by fgets)
    while (fgets(buffer, sizeof(buffer), original_file) != NULL) {
        char file_word[20]; // Temporary buffer to hold the word read from the current file line
        char file_syn[20]; // Temporary buffer for synonym part
        char file_ant[20]; // Temporary buffer for antonym part

        char buffer_copy[sizeof(buffer)];
        strncpy(buffer_copy, buffer, sizeof(buffer_copy) - 1); // Copy with size limit
        buffer_copy[sizeof(buffer_copy) - 1] = '\0'; // Ensure null termination for safety

        buffer_copy[strcspn(buffer_copy, "\n")] = 0;

        int scan_result = sscanf(buffer_copy, "%19[^=]=%19[^#]#%19[^\n]", file_word, file_syn, file_ant);

        // Check if sscanf successfully read at least the word part (scan_result >= 1)
        // AND if the extracted word matches the target word we are looking for (strcmp == 0).
        if (scan_result >= 1 && strcmp(file_word, word) == 0) {
            fprintf(temp_file, "%s=%s#%s\n", file_word, syne, anton);
            printf("Found and updated line for word '%s'.\n", word);
            found_and_updated = true; // Set the flag as the word was found and updated
        } else {
            fprintf(temp_file, "%s", buffer);
        }
    }

    // Close both the original and temporary files
    fclose(original_file);
    fclose(temp_file);

    // After processing the entire file, check if the word was found and updated.
    if (!found_and_updated) {
        printf("Word '%s' not found in the file. File not updated.\n", word);
        remove(temp_filename); // Remove the temporary file
        return; // Exit the function
    }

    if (remove(filename) != 0) {
        // If removing the original file fails, print an error.
        perror("Error removing original file for update");
        // The temporary file still exists with the updated content. Inform the user.
        fprintf(stderr, "Temporary updated file saved as '%s'. Please manually replace '%s' with this file.\n", temp_filename, filename);
    }
    else {
        // If the original file was successfully removed, rename the temporary file
        // to the original filename.
        if (rename(temp_filename, filename) != 0) {
            // If renaming fails, print an error.
            perror("Error renaming temporary file to original filename");
            // The original file is gone, and the updated content is in temp_filename. Inform the user.
            fprintf(stderr, "Updated file is in '%s', original was removed. Please manually rename '%s' to '%s'.\n", temp_filename, temp_filename, filename);
        }
        else {
            // If renaming was successful, the file update is complete.
            printf("File '%s' updated successfully.\n", filename);
        }
    }
}

void updateWord(TList *syn, TList *ant, char *word, char *syne, char *anton){
    if (syn==NULL||ant==NULL)
    {
        return ;
    }
    printf("ERROR\n");
    while (syn!=NULL)
    {
        if (strcmp(syn->word,word)==0)
        {
            strncpy(syn->word2,syne,sizeof(syn->word2)-1);
            syn->word2[sizeof(syn->word2)-1]='\0';
            strncpy(ant->word,anton,sizeof(ant->word)-1);
            ant->word[sizeof(ant->word)-1]='\0';
        }
        syn=syn->next;
        ant=ant->next;
    }
    updateWordInFile(word,syne,anton);
}

BTList*merge(TList *syn, TList *ant){
    if (syn==NULL||ant==NULL)
    {
        return NULL;
    }
    BTList*falseHead=BCreateNode(),*tail=falseHead;
    while (syn!=NULL||ant!=NULL)
    {
        tail->next=BCreateNode();
        tail->next->prev=tail;
        strcpy(tail->next->word,syn->word);
        strcpy(tail->next->syn,syn->word2);
        strcpy(tail->next->ant,ant->word2);
        tail->next->Vowels=syn->Vowels;
        tail->next->Chars=syn->Chars;
        tail->next->Consonants=syn->Consonants;
        tail=tail->next;
        ant=ant->next;
        syn=syn->next;
    }
    return falseHead->next;
}
CTList*merge2(TList *syn, TList *ant){
    if (syn==NULL||ant==NULL)
    {
        return NULL;
    }
    CTList*falseHead=CCreateNode(),*tail=falseHead;
    while (syn!=NULL||ant!=NULL)
    {
        tail->next=CCreateNode();
        strcpy(tail->next->word,syn->word);
        strcpy(tail->next->syn,syn->word2);
        strcpy(tail->next->ant,ant->word2);
        tail->next->Vowels=syn->Vowels;
        tail->next->Chars=syn->Chars;
        tail->next->Consonants=syn->Consonants;
        tail=tail->next;
        ant=ant->next;
        syn=syn->next;
    }
    tail->next=falseHead->next;
    return falseHead->next;
}
TList *addWord(TList *syn, TList *ant, char *word, char *syne, char *anton){
    TList*tail=syn;
    while (tail->next!=NULL)
    {
        tail=tail->next;
    }
    tail->next=CreateNode();
    tail=tail->next;
    strcpy(tail->word,word);
    strcpy(tail->word2,syne);
    countVowelsConsonants(tail->word,&(tail->Vowels),&(tail->Consonants));
    tail->Chars=tail->Vowels+tail->Consonants;
    tail->indicator=0;
    tail=ant;
    while (tail->next!=NULL)
    {
        tail=tail->next;
    }
    tail->next=CreateNode();
    tail=tail->next;
    strcpy(tail->word,word);
    strcpy(tail->word2,anton);
    countVowelsConsonants(tail->word,&(tail->Vowels),&(tail->Consonants));
    tail->Chars=tail->Vowels+tail->Consonants;
    tail->indicator=1;

}
void DisplayHeader(){
    printf("  %-20s | %-20s | %-20s | %-8s | %-10s | %-10s | \n","Synonym","Antonym","Type", "Vowels", "Consonants", "Chars");
    printf("  ---------------------|----------------------|----------|----------|------------|-------------\n");
}
void printBList(BTList* head) {
    BTList* current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Contents of the list:\n");
    while (current != NULL) {
        
        printf("  %-20s = %-20s # %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->syn,current->ant,current->Vowels,current->Consonants,current->Chars);
        
        current = current->next;
    }
}
void DestroyBList(BTList*T){
    printf("Freeing list memory...\n");
    if (T==NULL)
    {
        return;
    }
    BTList*Current=T;
    while (T!=NULL)
    {
        Current=T;
        T=T->next;
        free(Current);
    }
    printf("List memory freed.\n");
}
void printCList(CTList* head) {
    CTList* current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Contents of the list:\n");
    do {
        
        printf("  %-20s = %-20s # %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->syn,current->ant,current->Vowels,current->Consonants,current->Chars);
        
        current = current->next;
    }while (current != head);
}
void DestroyCList(CTList*T){
    printf("Freeing list memory...\n");
    if (T==NULL)
    {
        return;
    }
    CTList*current=T->next,*head=T;
    T=T->next;
    do
    {
        T=T->next;
        free(current);
        current=T;
    } while (current->next==head);
    
    printf("List memory freed.\n");
}
void EnQueue(TQueue**Q,BTList*value){
    TQueue*T=*Q;
    if (T==NULL)
    {
        *Q=createQueue();
        T=*Q;
        T->head=value;
        T->tail=value;
        return;
    }
    T->tail->next=value;
    value->prev=T->tail;
    T->tail=T->tail->next;
    return;
}
TQueue*toQueue(BTList*merged){
    TQueue*Q=createQueue();
    while (merged!=NULL)
    {       
        BTList*New=CreateBNodeCpy(merged);
        EnQueue(&Q,New);
        merged=merged->next;
    }
    return Q;
}
TStack*createStack(){
    TStack*stk=malloc(sizeof(TStack));
    stk->top=NULL;
    return stk;
}
void Push(TStack*stk,BTList*New){
    if (New==NULL||stk==NULL)
    {
        return;
    }
    if (stk->top==NULL)
    {
        stk->top=New;
        New->next=NULL;
        New->prev=NULL;
    }
    else
    {
        New->next=stk->top;
        New->prev=NULL;
        stk->top->prev=New;
        stk->top=New;
    }
}
bool IsEmptyStack(TStack*stk){
    return (stk==NULL)||(stk->top==NULL);
}
BTList*Pop(TStack*stk){
    if (stk==NULL||stk->top==NULL)
    {
        return NULL;
    }
    BTList * ret=stk->top;
    stk->top=stk->top->next;
    ret->next=NULL;
    return ret;
}
TStack *toStack(BTList *merged){
    if (merged==NULL)
    {
        return NULL;
    }
    BTList*next=NULL;
    TStack*stk=createStack();
    while (merged!=NULL)
    {
        next=merged->next;
        merged->next=NULL;
        Push(stk,merged);
        merged=next;
    }
    return stk;
}
// Corrected getInfWordStack function
void getInfWordStack(TStack *stk, char *word) {
    // Check for invalid input
    if (stk == NULL || IsEmptyStack(stk) || word == NULL) {
        printf("Stack is empty or word is invalid.\n");
        return;
    }

    TStack* temp1 = createStack(); // Temp stack for Pass 1 -> Pass 2
    TStack* temp2 = createStack(); // Temp stack for Pass 2 -> Restore
    BTList* current = NULL;
    bool syn_found = false;
    bool ant_found = false;

    printf("--- Information for '%s' (from Stack) ---\n", word);

    // Pass 1: Check Synonyms and move from stk to temp1
    printf("Synonyms:\n");
    while (!IsEmptyStack(stk)) {
        current = Pop(stk); // Remove from original stack
        if (current != NULL) {
            // Check word field and syn field for synonym match
            if (strcmp(word, current->word) == 0) {
                printf("- %s (word: %s)\n", current->syn, current->word);
                syn_found = true;
            } else if (strcmp(word, current->syn) == 0) {
                printf("- %s (word: %s)\n", current->word, current->syn);
                syn_found = true;
            }
            Push(temp1, current); // Push onto the first temporary stack
        }
    }
    if (!syn_found) {
        printf("- None found\n");
    }
    printf("--------------------\n");

    // Pass 2: Check Antonyms and move from temp1 to temp2
    printf("Antonyms:\n");
     while (!IsEmptyStack(temp1)) {
        current = Pop(temp1); // Remove from first temp stack
        if (current != NULL) {
             // Check word field and ant field for antonym match
            if (strcmp(word, current->word) == 0) {
                 printf("- %s (word: %s)\n", current->ant, current->word);
                 ant_found = true;
            } else if (strcmp(word, current->ant) == 0) {
                 // If the target word is an antonym, the original word is the opposite
                 printf("- %s (word: %s)\n", current->word, current->ant);
                 ant_found = true;
            }
            Push(temp2, current); // Push onto the second temporary stack
        }
    }
    if (!ant_found) {
        printf("- None found\n");
    }
     printf("--------------------\n");

    // Pass 3: Restore original stack by moving from temp2 to stk
    while (!IsEmptyStack(temp2)) {
        current = Pop(temp2); // Remove from second temp stack
        if (current != NULL) {
            Push(stk, current); // Push back onto the original stack
        }
    }

    // Free the temporary stack structures (not the nodes, as they are back in stk)
    free(temp1);
    free(temp2);
}
void DestroyQueue(TQueue* Q) {
    if (Q == NULL) return;
    printf("Destroying Queue...\n");
    // IMPORTANT: toQueue uses CreateBNodeCpy, so the queue OWNS its nodes.
    BTList* current = Q->head;
    BTList* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current); // Free the node created by CreateBNodeCpy
        current = nextNode;
    }
    free(Q); // Free the queue structure itself
    printf("Queue destroyed.\n");
}

void DestroyStack(TStack* S) {
    if (S == NULL) return;
    printf("Destroying Stack...\n");
    free(S);
    printf("Stack structure freed .\n");
}
BTList* merge2ListB(BTList* h1, int size1, BTList* h2, int size2) {

    if (h1==NULL&&h2==NULL) return NULL;

    BTList*dummy = malloc(sizeof(TList));  
    BTList* tail = dummy;
    dummy->next = NULL;

    int count1=0,count2=0;

    while (count1<size1&&count2<size2&&h1!=NULL&&h2!=NULL) {
        if (strcmp(h1->word,h2->word)<0) {
            tail->next = h2;
            h2->prev=tail;
            h2 = h2->next;
            count2++;
        } else {
            tail->next = h1;
            h1->prev=tail;
            h1 = h1->next;
            count1++;
        }
        tail = tail->next;
    }

    while (count1 < size1 && h1 != NULL) {
        tail->next = h1;
        h1->prev=tail;
        h1 = h1->next;
        tail = tail->next;
        count1++;
    }
    
    while (count2 < size2 && h2 != NULL) {
        tail->next = h2;
        h2 = h2->next;
        h2->prev=tail;
        tail = tail->next;
        count2++;
    }

    
    if (h1 != NULL) tail->next = h1; 
    if (h2 != NULL) tail->next = h2;  

    BTList* result = dummy->next;
    free(dummy);
    return result;
}

BTList *sortWordB(BTList *syn,int size){
    if(size<=1){
        return syn;
    }
    int mid=size/2,counter=0;
    BTList* p1=syn,*p2=NULL,*t=NULL,*r1=NULL,*r2=NULL;
    while(counter<mid-1){
        p1=p1->next;
        counter++;
    }
    p2=p1->next;
    t=p1;
    p1=p1->next;
    if (t!=NULL)
    {
        t->next=NULL;
    }
    else
    {
        if (p1->next==NULL)
        {
            p2=NULL;
        }
        else
        {
            p2=p1->next;
        }
    }
    r1=sortWordB(syn,mid);
    r2=sortWordB(p2,size-mid);
    syn=merge2ListB(r1,mid,r2,size-mid);
    return syn;
}
int BTListSize(BTList*B){
    if (B==NULL)
    {
        return 0;
    }
    int counter=0;
    while (B!=NULL)
    {
        counter ++;
        B=B->next;
    }
    return counter;
}
TStack *sortWordStack(TStack *syn){
    BTList*FalseHead=BCreateNode(),*tail=FalseHead,*Head=NULL;
    tail->next=NULL;
    while (!IsEmptyStack(syn))
    {
        tail->next=Pop(syn);
        tail=tail->next;
        tail->next=NULL;
    }
    Head=FalseHead->next;
    TStack*stk=createStack();
    Head=sortWordB(Head,BTListSize(Head));
    while (Head!=NULL)
    {   
        tail=Head->next;
        Head->next=NULL;
        Push(stk,Head);
        Head=tail;
    }
    
    return stk;
}
TStack *deleteWordStack(TStack *stk, char *word){
    if (stk==NULL)
    {
        return NULL;
    }
    BTList*temp=NULL;
    TStack*Tem=createStack();
    while (!IsEmptyStack(stk))
    {
        temp=Pop(stk);
        if (strcmp(word,temp->word)==0||strcmp(word,temp->ant)==0||strcmp(word,temp->syn)==0)
        {
            
        }
        else
        {
            Push(Tem,temp);
        }
    }
    while (!IsEmptyStack(Tem))
    {
        Push(stk,Pop(Tem));
    }
    return NULL;
}
TStack *updateWordStack(TStack *stk, char *word, char *syne, char *anton){
    if (stk==NULL)
    {
        return NULL;
    }
    TStack*Temp=createStack();
    BTList*current=NULL;
    while (!IsEmptyStack(stk))
    {
        current=Pop(stk);
        if (strcmp(word,current->word)==0)
        {
            strncpy(current->word,word,sizeof(current->word)-1);
            current->word[sizeof(current->word)-1]='\0';
            strncpy(current->ant,anton,sizeof(current->ant)-1);
            current->ant[sizeof(current->ant)-1]='\0';
            strncpy(current->syn,syne,sizeof(current->syn)-1);
            current->syn[sizeof(current->syn)-1]='\0';
            countVowelsConsonants(current->word,&(current->Vowels),&(current->Consonants));
            current->Chars=current->Vowels+current->Consonants;
        }
        
        Push(Temp,current);
    }
    while (!IsEmptyStack(Temp))
    {
        Push(stk,Pop(Temp));
    }
    return stk;
    
}
BTList* DeQueue(TQueue*Q){
    if(Q->head==NULL){
        return NULL;
    }
    else if(Q->head->next==NULL){
        BTList* val=CreateBNodeCpy(Q->head);
        BTList*fre=Q->head;
        Q->head=NULL;
        Q->tail=NULL;
        free(Q->head);
        return val;
    }
    else{
        BTList *val=CreateBNodeCpy(Q->head);
        BTList*fre=Q->head;
        Q->head=Q->head->next;
        free(fre);
        return val;
    }
}
TQueue *stackToQueue(TStack *stk){
    if (stk==NULL)
    {
        return NULL;
    }
    TQueue*Q=createQueue();
    while (!IsEmptyStack(stk))
    {
        EnQueue(&Q,Pop(stk));
    }
    return Q;
}
BTList *StacktoList(TStack *Stk){
    if (Stk==NULL)
    {
        return NULL;
    }
    BTList*FalseHead=BCreateNode(),*tail=FalseHead;
    while (!IsEmptyStack(Stk))
    {
        tail->next=Pop(Stk);
        tail=tail->next;
    }
    return FalseHead->next;
}
BTList* Peek(TStack*stk){
    if (stk==NULL||IsEmptyStack(stk))
    {
        return NULL;
    }
    return CreateBNodeCpy(stk->top);
}
TStack *addWordStack(TStack *stk, char *word, char *syne, char *anton){
    BTList*current=BCreateNode();
    TStack*temp=createStack();
    strncpy(current->word,word,sizeof(current->word)-1);
    current->word[sizeof(current->word)-1]='\0';
    strncpy(current->ant,anton,sizeof(current->ant)-1);
    current->ant[sizeof(current->ant)-1]='\0';
    strncpy(current->syn,syne,sizeof(current->syn)-1);
    current->syn[sizeof(current->syn)-1]='\0';
    while (!IsEmptyStack(stk))
    {
        Push(temp,Pop(stk));
    }
    Push(temp,current);
    while (!IsEmptyStack(temp))
    {
        Push(stk,Pop(temp));
    }
}
bool isPalyndromeStack(char *word){
    BTList*temp,*temp2;
    TStack*stk1=createStack(),*stk2=createStack();
    int size=strlen(word);
    for (int i = 0; i <size ; i++)
    {
        temp=BCreateNode();
        temp->word[0] = word[i];
        temp->word[1] = '\0';
        Push(stk1,temp);
        temp2=BCreateNode();
        temp2->word[0] = word[size-1-i];
        temp2->word[1] = '\0';
        Push(stk2,temp2);
    }
    while (!IsEmptyStack(stk1)&&!IsEmptyStack(stk2))
    {
        temp=Pop(stk1);
        temp2=Pop(stk2);
        if (strcmp(temp->word,temp2->word)!=0)
        {
            return false;
        }
    }
    if (!IsEmptyStack(stk1)||!IsEmptyStack(stk2))
    {
        return false;
    }
    return true;
}
char *getSmallest(TStack *stk){
    if (stk==NULL|IsEmptyStack(stk))
    {
        return NULL;
    }
    BTList*current=NULL;
    char*str;
    int lenght=20;
    while (!IsEmptyStack(stk))
    {
        current=Pop(stk);
        if (lenght>current->Chars)
        {
            str=&(current->word[0]);
        }
    }
    return str;
}
TStack *StackRev(TStack *stk){
    if (stk==NULL)
    {
        return NULL;
    }
    if (IsEmptyStack(stk))
    {
        return stk;
    }
    BTList*temp=Pop(stk);
    StackRev(stk);
    Push(stk,temp);
    return stk;
}
void AddNodeToExistingTree(TTree*root,TTree*new){
    if (root==NULL)
    {
        return ;
    }
    if (new->Chars>=root->Chars)
    {
        if (root->right==NULL)
        {
            root->right=new;
            return ;
        }
        else
        {
            AddNodeToExistingTree(root->right,new);
        }
    }
    else
    {
        if (root->left==NULL)
        {
            root->left=new;
            return ;
        }
        else
        {
            AddNodeToExistingTree(root->left,new);
        }
    }
}
void AddNodeToTree(TTree**root,TTree*New){
    if (*root==NULL)
    {
        *root=New;
        return;
    }
    else
    {
        AddNodeToExistingTree(*root,New);
        return;
    }
    return ;
}
TTree*CpyBTListToTTree(BTList*original){
    if (original==NULL)
    {
        return NULL;
    }
    TTree*L=TCreateNode();
    L->Chars=original->Chars;
    L->Consonants=original->Consonants;
    L->right=NULL;
    L->left=NULL;
    L->Vowels=original->Vowels;
    strncpy(L->word,original->word,sizeof(L->word)-1);
    L->word[sizeof(L->word)-1]='\0';
    strncpy(L->syn,original->syn,sizeof(L->syn)-1);
    L->syn[sizeof(L->syn)-1]='\0';
    strncpy(L->ant,original->ant,sizeof(L->ant)-1);
    L->ant[sizeof(L->ant)-1]='\0';
    return L ;
}
TTree *toTree(TStack *stk){
    if (stk==NULL||IsEmptyStack(stk))
    {
        return NULL;
    }
    TTree*T=NULL;
    while (!IsEmptyStack(stk))
    {
        AddNodeToTree(&T,CpyBTListToTTree(Pop(stk)));
    }
    return T;
}
void PrintSingleColunm(TTree*root){
    TTree* current = root;
    if (current == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    printf("  %-20s = %-20s # %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->syn,current->ant,current->Vowels,current->Consonants,current->Chars);     
}
void printTreeInOrder(TTree*R){
    if (R==NULL)
    {
        return ;
    }
    printTreeInOrder(R->left);
    PrintSingleColunm(R);
    printTreeInOrder(R->right);
}
void printTreePostOrder(TTree*R){
    if (R==NULL)
    {
        return ;
    }
    printTreePostOrder(R->left);
    printTreePostOrder(R->right);
    PrintSingleColunm(R);   
}
void printTreePreOrder(TTree*R){
    if (R==NULL)
    {
        return ;
    }
    PrintSingleColunm(R);
    printTreePreOrder(R->left);
    printTreePreOrder(R->right);
}
TTree *fillTree(FILE *file_name){
    char buffer[100]; 
    int checker;
    TTree*T=NULL,*Temp=NULL,*Tail=NULL;
    TTree*res=NULL;
    while (fgets(buffer, sizeof(buffer), file_name)!=NULL)
        {
            char word[20];
            char ant[20];
            char syn[20];
            checker=sscanf(buffer, "%19[^=]=%19[^#]#%19[^\n]",word,syn,ant);
            if (checker==3)
            {
                printf("word: %s, syn: %s ant :%s\n", word,syn, ant);

                    T=TCreateNode();

                    strncpy(T->word,word,sizeof(T->word)-1);

                    T->word[sizeof(T->word)-1]='\0';

                    strncpy(T->ant,ant,sizeof(T->ant)-1);

                    T->ant[sizeof(T->ant)-1]='\0';

                    strncpy(T->syn,syn,sizeof(T->syn)-1);

                    T->syn[sizeof(syn)-1]='\0';

                    countVowelsConsonants(T->word,&(T->Vowels),&(T->Consonants));

                    T->Chars=T->Vowels+T->Consonants;

                    AddNodeToTree(&res,T);
            }
            else
            {
                printf("Error in reading\n");
                return res;
            }
        }
        return res;
}
void DestroyTree(TTree*R){
    if (R == NULL) return;
    DestroyTree(R->left);
    DestroyTree(R->right);
    free(R);
}
TTree*SerchInBst(TTree*root,char*word,int size){
    TTree*res1=NULL,*res2=NULL;
    if (root==NULL)
    {
        return NULL;
    }
    if (strcmp(root->word,word)==0)
    {
        return root;
    }
    else
    {
        if (size>=root->Chars)
        {
            res1=SerchInBst(root->right,word,size);
        }
        else
        {
            res2=SerchInBst(root->left,word,size);
        }
        if (res1!=NULL)
        {
            return res1;
        }
        else if (res2!=NULL)
        {
            return res2;
        }
        else
        {
            return NULL;
        }
        
    }
    
    
}
TTree*getInfWordTree(TTree *root, char *word){
    TTree*res=NULL;
    return res=SerchInBst(root,word,strlen(word));
}
bool isMirrorS(TTree*l,TTree*r){
    if (r==NULL&&l==NULL)
    {
        return true;
    }
    if (r==NULL||l==NULL)
    {
        return false;
    }
    if (r->Chars!=l->Chars)
    {
        return false;
    }
    return isMirrorS(l->left,r->right)&&isMirrorS(l->right,r->left);
}
int height(TTree*R){
    if (R==NULL)
    {
        return 0;
    }
    if (R->left==NULL&&R->right==NULL)
    {
        return 1;
    }
    return height(R->right)>height(R->left) ? 1+height(R->right) : 1+height(R->left); 
}
bool isBalencedBST(TTree *tr){
    if (tr==NULL)
    {
        return true;
    }
    int indicator=height(tr->right)-height(tr->left);
    if (indicator==0||indicator==-1||indicator==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
TTree *LowestCommonAncestor(TTree *root, char *word1, char *word2){
        if (root==NULL)
        {
            return NULL;
        }
        if (strcmp(root->word,word1)==0||strcmp(root->word,word2)==0)
        {
            return root;
        }
        TTree*FoundLeft=LowestCommonAncestor(root->left,word1,word2);
        TTree*FoundRight=LowestCommonAncestor(root->right,word1,word2);
        if (FoundLeft!=NULL&&FoundRight!=NULL)
        {
            return root;
        }
        else if (FoundLeft==NULL)
        {
            return FoundRight;
        }
        else
        {
            return FoundLeft;
        }
}
int CountNodesRanges(TTree *tr, int l, int h){
    if (tr==NULL)
    {
        return 0;
    }
    return (tr->Chars>l&&tr->Chars<h) ? CountNodesRanges(tr->left,l,h)+CountNodesRanges(tr->right,l,h)+1 :CountNodesRanges(tr->left,l,h)+CountNodesRanges(tr->right,l,h);
}
TTree*findSmallest(TTree*root){
    if (root==NULL)
    {
        return NULL;
    }
    TTree*foundright=findSmallest(root->right);
    TTree*foundleft=findSmallest(root->left);
    if (foundleft!=NULL&&foundright!=NULL)
    {
        return foundleft->Chars<foundright->Chars ? foundleft : foundright;
    }
    else if (foundright==NULL)
    {
        return foundleft;
    }
    else
    {
        return foundright;
    }
}
TTree *deleteWordBST(TTree *tr, char *word) {
    if (tr == NULL) {
        return NULL;
    }

    int wordSize = strlen(word);
    int comparison = wordSize - tr->Chars;

    if (comparison < 0) {
        // Word to be deleted has fewer characters, go left
        tr->left = deleteWordBST(tr->left, word);
    } else if (comparison > 0) {
        // Word to be deleted has more characters, go right
        tr->right = deleteWordBST(tr->right, word);
    } else {
        // The number of characters matches. Now, compare the actual word string.
        int stringComparison = strcmp(word, tr->word);

        if (stringComparison < 0) {
            // Chars match, but the target word is alphabetically smaller, go left
            tr->left = deleteWordBST(tr->left, word);
        } else if (stringComparison > 0) {
            // Chars match, but the target word is alphabetically larger, go right
            tr->right = deleteWordBST(tr->right, word);
        } else {
            // Found the node to be deleted (Chars match AND word matches)

            // Case 1: Node with only one child or no child
            if (tr->left == NULL) {
                TTree *temp = tr->right;
                // No need to free tr->word, it's a fixed-size array
                free(tr); // Free the node structure
                return temp;
            } else if (tr->right == NULL) {
                TTree *temp = tr->left;
                // No need to free tr->word, it's a fixed-size array
                free(tr); // Free the node structure
                return temp;
            }

            // Case 2: Node with two children
            // Get the in-order successor (smallest in the right subtree based on Chars)
            TTree *inorderSuccessor = findSmallest(tr->right);

            // Copy the content of the in-order successor to this node
            // Use strncpy for fixed-size arrays to prevent buffer overflows
            strncpy(tr->word, inorderSuccessor->word, sizeof(tr->word) - 1);
            tr->word[sizeof(tr->word) - 1] = '\0'; // Ensure null termination
            strncpy(tr->ant, inorderSuccessor->ant, sizeof(tr->ant) - 1);
            tr->ant[sizeof(tr->ant) - 1] = '\0';
            strncpy(tr->syn, inorderSuccessor->syn, sizeof(tr->syn) - 1);
            tr->syn[sizeof(tr->syn) - 1] = '\0';

            tr->Chars = inorderSuccessor->Chars;
            tr->Vowels = inorderSuccessor->Vowels;
            tr->Consonants = inorderSuccessor->Consonants;

            // Delete the in-order successor node from the right subtree
            // Pass the successor's word for the recursive deletion call
            tr->right = deleteWordBST(tr->right, inorderSuccessor->word);
        }
    }
    return tr;
}
void handleListOperations(TList* syn, TList* ant, const char* filename);
void handleMergedListOperations(BTList** mergedList, CTList** circularMergedList, TQueue** queueFromList, TStack** stackFromList, TList* syn, TList* ant);
void handleStackOperations(TStack** stackFromList);
void handleQueueOperations(TQueue** queueFromList);
void handleTreeOperations(TTree** dictionaryTree, const char* filename);

// Main function
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
    Syn=getSynWords(file);
    if (Syn == NULL && !feof(file)) {
        fprintf(stderr, "Warning: Error or empty content loading synonyms from file.\n");
    }
    rewind(file);
    Ant=getAntoWords(file);
     if (Ant == NULL && !feof(file)) {
        fprintf(stderr, "Warning: Error or empty content loading antonyms from file.\n");
    }
    fclose(file);
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
        printf(" 6. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

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
            case 6: // Exit
                printf("Exiting program.\n");
                running = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
        if (running) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }

    // --- Cleanup Resources ---
    printf("\n--- Cleaning up resources ---\n");
    DestroyList(Syn);
    DestroyList(Ant);
    if (MergedList != NULL) { DestroyBList(MergedList); }
    if (CircularMergedList != NULL) { DestroyCList(CircularMergedList); }
    if (QueueFromList != NULL) { DestroyQueue(QueueFromList); }
    if (StackFromList != NULL) {
         printf("Cleaning up Stack (if it owns nodes)...\n");
         while (!IsEmptyStack(StackFromList)) {
             BTList* node = Pop(StackFromList);
             if (node != NULL) {
                 // If nodes were copied (e.g., from toStack), they need to be freed.
                 // If nodes were transferred ownership, this is correct.
                 // Based on toStack implementation provided, it pushes the original merged list nodes,
                 // so StackFromList *owns* the nodes.
                 free(node);
             }
         }
         free(StackFromList);
         printf("Stack and its nodes freed.\n");
    }
     if (DictionaryTree != NULL) {
        printf("Cleaning up Tree...\n");
        DestroyTree(DictionaryTree); // Assuming DestroyTree frees nodes
        printf("Tree freed.\n");
    }
    printf("Cleanup complete. Goodbye!\n");

    return 0;
}

// --- Menu Handler Function Implementations (rest of the file) ---

void handleListOperations(TList* syn, TList* ant, const char* filename) {
    int choice;
    bool running_menu = true;
    char Target[20], Part[20], WordToUpdate[20], NewSynonym[20], NewAntonym[20], WordToAdd[20];
    float SimRate;
    TList *FoundWords = NULL;
    TList *PalindromeWords = NULL;
    TList *SimilarWordsList = NULL;


    while(running_menu) {
        printf("\n========== List Operations Menu ==========\n");
        printf(" 1. Display Synonyms\n");
        printf(" 2. Display Antonyms\n");
        printf(" 3. Get Information for a Word\n");
        printf(" 4. Sort Synonyms Alphabetically\n");
        printf(" 5. Sort Antonyms Alphabetically\n");
        printf(" 6. Sort Synonyms by Character Count (Ascending)\n");
        printf(" 7. Sort Antonyms by Character Count (Ascending)\n");
        printf(" 8. Sort Synonyms by Vowel Count (Descending)\n");
        printf(" 9. Sort Antonyms by Vowel Count (Descending)\n");
        printf("10. Find words containing a specific part\n");
        printf("11. Find palindrome words\n");
        printf("12. Find words similar to a target word\n");
        printf("13. Update a word's synonym and antonym (in-memory and file)\n");
        printf("14. Add a new word (with syn & ant) (in-memory only)\n");
        printf("15. Back to Main Menu\n");
        printf("===========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: // Display Syn
                printf("\n--- Displaying Synonyms ---\n");
                printList(syn);
                break;
            case 2: // Display Ant
                printf("\n--- Displaying Antonyms ---\n");
                printList(ant);
                break;
            case 3: // Get Info from Lists
                printf("Enter the word to get information for: ");
                if(scanf("%19s", Target) == 1) {
                    while (getchar() != '\n');
                    printf("\n--- Information for '%s' (from Lists) ---\n", Target);
                    getInfWord(syn, ant, Target);
                } else {
                     printf("Invalid input for word.\n");
                     while (getchar() != '\n');
                }
                break;
            case 4: // Sort Syn Alpha
                if (IsEmpty(syn)) {
                    printf("Synonym list is empty. Nothing to sort.\n");
                } else {
                    printf("Sorting Synonyms Alphabetically...\n");
                    syn = sortWord(syn, ListSize(syn));
                    printf("Synonyms sorted.\n");
                    printList(syn);
                }
                break;
            case 5: // Sort Ant Alpha
                if (IsEmpty(ant)) {
                    printf("Antonym list is empty. Nothing to sort.\n");
                } else {
                    printf("Sorting Antonyms Alphabetically...\n");
                    ant = sortWord(ant, ListSize(ant));
                    printf("Antonyms sorted.\n");
                    printList(ant);
                }
                break;
            case 6: // Sort Syn Chars
                 if (IsEmpty(syn)) {
                     printf("Synonym list is empty. Nothing to sort.\n");
                } else {
                    printf("Sorting Synonyms by Character Count (Ascending)....\n");
                    syn = sortWord2(syn, ListSize(syn));
                    printf("Synonyms sorted.\n");
                    printList(syn);
                }
                break;
            case 7: // Sort Ant Chars
                 if (IsEmpty(ant)) {
                     printf("Antonym list is empty. Nothing to sort.\n");
                 } else {
                    printf("Sorting Antonyms by Character Count (Ascending)....\n");
                    ant = sortWord2(ant, ListSize(ant));
                    printf("Antonyms sorted.\n");
                    printList(ant);
                 }
                break;
            case 8: // Sort Syn Vowels
                 if (IsEmpty(syn)) {
                      printf("Synonym list is empty. Nothing to sort.\n");
                 } else {
                    printf("Sorting Synonyms by Vowel Count (Descending)...\n");
                    syn = sortWord3(syn, ListSize(syn));
                    printf("Synonyms sorted.\n");
                    printList(syn);
                 }
                break;
            case 9: // Sort Ant Vowels
                 if (IsEmpty(ant)) {
                      printf("Antonym list is empty. Nothing to sort.\n");
                 } else {
                    printf("Sorting Antonyms by Vowel Count (Descending)...\n");
                    ant = sortWord3(ant, ListSize(ant));
                    printf("Antonyms sorted.\n");
                    printList(ant);
                 }
                break;
            case 10: // Find containing part
                printf("Enter the part of the word to search for: ");
                 if(scanf("%19s", Part) == 1) {
                     while (getchar() != '\n');
                     printf("\n--- Searching for words containing '%s' ---\n", Part);
                     FoundWords = countWord(syn, Part);
                     printf("\n--- Found in Synonyms List ---\n");
                     printList(FoundWords);
                     DestroyList(FoundWords); // Free temporary list
                     FoundWords = NULL;
                     FoundWords = countWord(ant, Part);
                     printf("\n--- Found in Antonyms List ---\n");
                     printList(FoundWords);
                     DestroyList(FoundWords); // Free temporary list
                     FoundWords = NULL;
                 } else {
                     printf("Invalid input for part.\n");
                     while (getchar() != '\n');
                 }
                break;
            case 11: // Find Palindromes
                printf("\n--- Searching for Palindrome Words ---\n");
                PalindromeWords = palindromWord(syn);
                printf("\n--- Palindromes in Synonyms List ---\n");
                printList(PalindromeWords);
                DestroyList(PalindromeWords); // Free temporary list
                PalindromeWords = NULL;
                PalindromeWords = palindromWord(ant);
                 printf("\n--- Palindromes in Antonyms List ---\n");
                printList(PalindromeWords);
                DestroyList(PalindromeWords); // Free temporary list
                PalindromeWords = NULL;
                break;
            case 12: // Find Similar Words
                 printf("Enter the word to find similarities for: ");
                 if(scanf("%19s", Target) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');
                 printf("Enter the minimum similarity rate (e.g., 0.5 for 50%%): ");
                 if(scanf("%f", &SimRate) != 1 || SimRate < 0.0 || SimRate > 1.0) { printf("Invalid rate (must be 0.0-1.0).\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');

                 printf("\n--- Searching for words similar to '%s' (Rate >= %.2f) ---\n", Target, SimRate);
                 SimilarWordsList = similarWord(syn, Target, SimRate);
                 printf("\n--- Similar words found in Synonyms ---\n");
                 printList(SimilarWordsList);
                 DestroyList(SimilarWordsList); // Free temporary list
                 SimilarWordsList = NULL;
                 SimilarWordsList = similarWord(ant, Target, SimRate);
                 printf("\n--- Similar words found in Antonyms ---\n");
                 printList(SimilarWordsList);
                 DestroyList(SimilarWordsList); // Free temporary list
                 SimilarWordsList = NULL;
                 break;
            case 13: // Update Word (in-memory and file)
                 printf("\n--- Update Word Entry ---\n");
                 printf("Enter the word to update: ");
                 if (scanf("%19s", WordToUpdate) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');
                 printf("Enter the NEW synonym for '%s': ", WordToUpdate);
                 if (scanf("%19s", NewSynonym) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');
                 printf("Enter the NEW antonym for '%s': ", WordToUpdate);
                 if (scanf("%19s", NewAntonym) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');

                 updateWord(syn, ant, WordToUpdate, NewSynonym, NewAntonym);
                 printf("Attempted to update word '%s'. Check lists and file to verify.\n", WordToUpdate);
                 break;
            case 14: // Add Word (in-memory only)
                 printf("\n--- Add New Word Entry (in-memory only) ---\n");
                 printf("Enter the new word: ");
                 if (scanf("%19s", WordToAdd) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');
                 printf("Enter the synonym for '%s': ", WordToAdd);
                 if (scanf("%19s", NewSynonym) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');
                 printf("Enter the antonym for '%s': ", WordToAdd);
                 if (scanf("%19s", NewAntonym) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                 while (getchar() != '\n');

                 addWord(syn, ant, WordToAdd, NewSynonym, NewAntonym);
                 printf("Attempted to add word '%s' to in-memory lists.\n", WordToAdd);
                 printf("Note: This change is in-memory only. To save this new word to the file, you would need a 'Save' option or a different add function.\n");
                 break;
            case 15: // Back to Main Menu
                running_menu = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 15.\n");
        }
        if (running_menu) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }
}

void handleMergedListOperations(BTList** mergedList, CTList** circularMergedList, TQueue** queueFromList, TStack** stackFromList, TList* syn, TList* ant) {
    int choice;
    bool running_menu = true;

    while(running_menu) {
        printf("\n========== Merged List Operations Menu ==========\n");
        printf(" 1. Merge Syn/Ant into Doubly Linked list (BTList)\n");
        printf(" 2. Merge Syn/Ant into Circular Linked list (CTList)\n");
        printf(" 3. Display Doubly Linked Merged List (BTList)\n");
        printf(" 4. Display Circular Merged List (CTList)\n");
        printf(" 5. Convert Merged BTList to Queue (copies nodes)\n");
        printf(" 6. Convert Merged BTList to Stack (transfers node ownership)\n");
        printf(" 7. Back to Main Menu\n");
        printf("=================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: // Merge to BTList
                printf("\n--- Merging into Doubly Linked List (BTList) ---\n");
                 if (*mergedList != NULL) { DestroyBList(*mergedList); *mergedList = NULL; }
                 if (*circularMergedList != NULL) { DestroyCList(*circularMergedList); *circularMergedList = NULL; }
                 if (*queueFromList != NULL) { DestroyQueue(*queueFromList); *queueFromList = NULL;}
                 if (*stackFromList != NULL) {
                      printf("Cleaning up previous Stack nodes...\n");
                      while (!IsEmptyStack(*stackFromList)) {
                         BTList* node = Pop(*stackFromList);
                         if (node != NULL) {
                             free(node);
                         }
                     }
                     free(*stackFromList);
                     *stackFromList = NULL;
                     printf("Note: Previous Stack invalidated as its nodes were part of the merged list.\n");
                 }

                 *mergedList = merge(syn, ant);
                 if (*mergedList) {
                    printf("Merged list (BTList) created successfully.\n");
                 } else {
                    printf("Failed to create merged list (BTList). Ensure Syn and Ant lists are populated.\n");
                 }
                break;
             case 2: // Merge to CTList
                printf("\n--- Merging into Circular Linked List (CTList) ---\n");
                 if (*mergedList != NULL) { DestroyBList(*mergedList); *mergedList = NULL; }
                 if (*circularMergedList != NULL) { DestroyCList(*circularMergedList); *circularMergedList = NULL; }
                 if (*queueFromList != NULL) { DestroyQueue(*queueFromList); *queueFromList = NULL;}
                 if (*stackFromList != NULL) {
                      printf("Cleaning up previous Stack nodes...\n");
                      while (!IsEmptyStack(*stackFromList)) {
                         BTList* node = Pop(*stackFromList);
                         if (node != NULL) {
                             free(node);
                         }
                     }
                     free(*stackFromList);
                     *stackFromList = NULL;
                     printf("Note: Previous Stack invalidated as its nodes were part of the merged list.\n");
                 }

                 *circularMergedList = merge2(syn, ant);
                 if (*circularMergedList) {
                    printf("Merged list (CTList) created successfully.\n");
                 } else {
                     printf("Failed to create merged list (CTList). Ensure Syn and Ant lists are populated.\n");
                 }
                 break;
            case 3: // Display BTList
                printf("\n--- Displaying Doubly Linked Merged List (BTList) ---\n");
                printBList(*mergedList);
                break;
            case 4: // Display CTList
                 printf("\n--- Displaying Circular Merged List (CTList) ---\n");
                 printCList(*circularMergedList);
                 break;
            case 5: // Convert Merged BTList to Queue (copies nodes)
                 printf("\n--- Converting Merged BTList to Queue ---\n");
                 printf("(Note: The Queue will contain *copies* of the BTList nodes. The original BTList remains intact.)\n");
                 if (*mergedList == NULL) {
                     printf("Merged BTList does not exist. Create it first (Option 1).\n");
                 } else {
                     if (*queueFromList != NULL) { DestroyQueue(*queueFromList); *queueFromList = NULL; }
                     *queueFromList = toQueue(*mergedList);
                     if (*queueFromList != NULL && ((*queueFromList)->head != NULL || *mergedList == NULL)) {
                        printf("Queue created successfully (Queue owns new nodes).\n");
                        printf("Queue created. To process queue elements, you would need a separate dequeue/display loop.\n");
                     } else {
                         printf("Failed to create Queue or Queue is empty.\n");
                         if(*queueFromList) free(*queueFromList);
                         *queueFromList = NULL;
                     }
                 }
                 break;
            case 6: // Convert Merged BTList to Stack (transfers node ownership)
                 printf("\n--- Converting Merged BTList to Stack ---\n");
                 printf("(Note: The Stack will *take ownership* of the BTList nodes. The original Merged BTList will be empty/invalidated after this operation.)\n");
                 if (*mergedList == NULL) {
                     printf("Merged BTList does not exist. Create it first (Option 1).\n");
                 } else {
                     if (*stackFromList != NULL) {
                         printf("Cleaning up previous Stack nodes...\n");
                          while (!IsEmptyStack(*stackFromList)) {
                             BTList* node = Pop(*stackFromList);
                             if (node != NULL) {
                                 free(node);
                             }
                         }
                         free(*stackFromList);
                         *stackFromList = NULL;
                     }
                     *stackFromList = toStack(*mergedList);
                     *mergedList = NULL;

                     if (*stackFromList != NULL && ((*stackFromList)->top != NULL || *mergedList == NULL)) {
                         printf("Stack created successfully (took ownership of BTList nodes).\n");
                         printf("The original Merged BTList is now empty/invalidated.\n");
                     } else {
                         printf("Failed to create Stack or Stack is empty.\n");
                         if(*stackFromList) free(*stackFromList);
                         *stackFromList = NULL;
                         printf("The original Merged BTList is now empty/invalidated.\n");
                     }
                 }
                 break;
            case 7: // Back to Main Menu
                running_menu = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
         if (running_menu) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }
}

void handleStackOperations(TStack** stackFromList) {
    int choice;
    bool running_menu = true;
    char Target[20], wordToDelete[20], wordToUpdateStack[20], newSynonymStack[20], newAntonymStack[20], wordToAddStack[20], synToAddStack[20], antToAddStack[20];

    TQueue* queueFromStack = NULL;
    BTList* listFromStack = NULL;


    while(running_menu) {
        printf("\n========== Stack Operations Menu ==========\n");
        printf(" 1. Get Information for a Word (from Stack)\n");
        printf(" 2. Sort Stack Alphabetically\n");
        printf(" 3. Delete Word from Stack\n");
        printf(" 4. Update Word in Stack\n");
        printf(" 5. Add Word to Stack (to the top)\n");
        printf(" 6. Convert Stack to Queue (copies nodes)\n");
        printf(" 7. Convert Stack to BTList (copies nodes)\n");
        printf(" 8. Back to Main Menu\n");
        printf("===========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: // Get Info from Stack
                 printf("\n--- Get Information for a Word (from Stack) ---\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                    printf("Enter the word to get information for: ");
                    if(scanf("%19s", Target) == 1) {
                        while (getchar() != '\n');
                        getInfWordStack(*stackFromList, Target);
                        printf("--- Search complete (check output above) ---\n");
                    } else {
                         printf("Invalid input for word.\n");
                         while (getchar() != '\n');
                    }
                 }
                 break;
            case 2: // Sort Stack Alphabetically
                 printf("\n--- Sorting Stack Alphabetically ---\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                     *stackFromList = sortWordStack(*stackFromList);
                     printf("Stack sorted alphabetically (based on word field).\n");
                     printf("Note: To view the sorted stack without emptying it, convert it to a BTList (Option 7) and display the list.\n");
                 }
                 break;
            case 3: // Delete Word from Stack
                 printf("\n--- Delete Word from Stack ---\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                    printf("Enter the word to delete from the stack: ");
                    if(scanf("%19s", wordToDelete) == 1) {
                        while (getchar() != '\n');
                        *stackFromList = deleteWordStack(*stackFromList, wordToDelete);
                        printf("Attempted to delete word '%s' from stack.\n", wordToDelete);
                        printf("Note: To verify deletion, inspect the stack's contents (e.g., by converting to a BTList using Option 7).\n");
                    } else {
                         printf("Invalid input for word.\n");
                         while (getchar() != '\n');
                    }
                 }
                 break;
            case 4: // Update Word in Stack
                 printf("\n--- Update Word in Stack ---\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                    printf("Enter the word to update in the stack: ");
                    if(scanf("%19s", wordToUpdateStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the NEW synonym for '%s': ", wordToUpdateStack);
                    if (scanf("%19s", newSynonymStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the NEW antonym for '%s': ", wordToUpdateStack);
                    if (scanf("%19s", newAntonymStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');

                    *stackFromList = updateWordStack(*stackFromList, wordToUpdateStack, newSynonymStack, newAntonymStack);
                    printf("Attempted to update word '%s' in stack. Note: Verification requires inspecting the stack (e.g., Option 1 or 7).\n", wordToUpdateStack);
                 }
                 break;
            case 5: // Add Word to Stack (Push)
                printf("\n--- Add Word to Stack (Push) ---\n");
                if (*stackFromList == NULL) {
                     printf("Stack has not been created. Use Merged List Option 6 first.\n");
                 } else {
                    char wordToAddStack[20], synToAddStack[20], antToAddStack[20];
                    printf("Enter the word to add to the stack: ");
                    if(scanf("%19s", wordToAddStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the synonym for '%s': ", wordToAddStack);
                    if (scanf("%19s", synToAddStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the antonym for '%s': ", wordToAddStack);
                    if (scanf("%19s", antToAddStack) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');

                    BTList* newNode = BCreateNode();
                    if (newNode == NULL) {
                        perror("Memory allocation failed for new stack node");
                    } else {
                        strncpy(newNode->word, wordToAddStack, sizeof(newNode->word) - 1); newNode->word[sizeof(newNode->word) - 1] = '\0';
                        strncpy(newNode->syn, synToAddStack, sizeof(newNode->syn) - 1); newNode->syn[sizeof(newNode->syn) - 1] = '\0';
                        strncpy(newNode->ant, antToAddStack, sizeof(newNode->ant) - 1); newNode->ant[sizeof(newNode->ant) - 1] = '\0';
                        countVowelsConsonants(newNode->word, &(newNode->Vowels), &(newNode->Consonants));
                        newNode->Chars = newNode->Vowels + newNode->Consonants;

                        Push(*stackFromList, newNode);
                        printf("Word '%s' pushed onto the stack.\n", wordToAddStack);
                    }
                 }
                break;
            case 6: // Convert Stack to Queue (copies nodes)
                 printf("\n--- Converting Stack to Queue ---\n");
                 printf("(Note: The Queue will contain *copies* of the Stack nodes. The original Stack remains intact.)\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                     if (queueFromStack != NULL) { DestroyQueue(queueFromStack); queueFromStack = NULL; }
                     queueFromStack = stackToQueue(*stackFromList);
                     if (queueFromStack != NULL && (queueFromStack->head != NULL || IsEmptyStack(*stackFromList))) {
                         printf("Stack converted to Queue successfully (Queue owns new nodes).\n");
                         printf("Note: This is a temporary queue for demonstration. To use it elsewhere, manage its pointer.\n");
                     } else {
                         printf("Failed to convert Stack to Queue or Queue is empty.\n");
                         if(queueFromStack) free(queueFromStack);
                         queueFromStack = NULL;
                     }
                 }
                 break;
            case 7: // Convert Stack to BTList (copies nodes)
                 printf("\n--- Converting Stack to BTList ---\n");
                 printf("(Note: This creates a *new* BTList with copies of the Stack nodes. The original Stack remains intact.)\n");
                 if (*stackFromList == NULL || IsEmptyStack(*stackFromList)) {
                     printf("Stack has not been created or is empty. Use Merged List Option 6 first.\n");
                 } else {
                     if (listFromStack != NULL) { DestroyBList(listFromStack); listFromStack = NULL; }
                     listFromStack = StacktoList(*stackFromList);
                     if (listFromStack != NULL) {
                         printf("Stack converted to BTList successfully (New list owns copies).\n");
                         printf("Displaying the created BTList:\n");
                         printBList(listFromStack);
                         printf("Note: This is a temporary list for demonstration. To use it elsewhere, manage its pointer.\n");
                     } else {
                         printf("Failed to convert Stack to BTList or BTList is empty.\n");
                     }
                 }
                 break;
            case 8: // Back to Main Menu
                running_menu = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
         if (running_menu) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }
    if (queueFromStack != NULL) { DestroyQueue(queueFromStack); queueFromStack = NULL; }
    if (listFromStack != NULL) { DestroyBList(listFromStack); listFromStack = NULL; }
}

void handleQueueOperations(TQueue** queueFromList) {
     int choice;
    bool running_menu = true;
    char Target[20];
    BTList* dequeuedNode = NULL;

    while(running_menu) {
        printf("\n========== Queue Operations Menu ==========\n");
        printf(" 1. Dequeue (Remove from front)\n");
        printf(" 2. Enqueue (Add to back) (in-memory only)\n");
        printf(" 3. Display Queue (will empty the queue)\n");
        printf(" 4. Back to Main Menu\n");
        printf("===========================================\n");
        printf("Enter your choice: ");

         if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: // Dequeue
                 printf("\n--- Dequeue (Remove from front) ---\n");
                 if (*queueFromList == NULL || (*queueFromList)->head == NULL) {
                     printf("Queue is empty or has not been created. Use Merged List Option 5 or Stack Option 6 first.\n");
                 } else {
                     dequeuedNode = DeQueue(*queueFromList);
                     if (dequeuedNode != NULL) {
                         printf("Dequeued word: %s (Syn: %s, Ant: %s)\n", dequeuedNode->word, dequeuedNode->syn, dequeuedNode->ant);
                         free(dequeuedNode);
                         dequeuedNode = NULL;
                     } else {
                         printf("Dequeue failed (Queue might be empty now).\n");
                     }
                 }
                 break;
            case 2: // Enqueue (in-memory only)
                 printf("\n--- Enqueue (Add to back) (in-memory only) ---\n");
                 if (*queueFromList == NULL) {
                     printf("Queue has not been created. Use Merged List Option 5 or Stack Option 6 first.\n");
                 } else {
                    char wordToEnqueue[20], synToEnqueue[20], antToEnqueue[20];
                    printf("Enter the word to enqueue: ");
                    if(scanf("%19s", wordToEnqueue) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the synonym for '%s': ", wordToEnqueue);
                    if (scanf("%19s", synToEnqueue) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');
                    printf("Enter the antonym for '%s': ", wordToEnqueue);
                    if (scanf("%19s", antToEnqueue) != 1) { printf("Invalid input.\n"); while(getchar()!='\n'); break; }
                    while (getchar() != '\n');

                    BTList* newNode = BCreateNode();
                    if (newNode == NULL) {
                        perror("Memory allocation failed for new queue node");
                    } else {
                        strncpy(newNode->word, wordToEnqueue, sizeof(newNode->word) - 1); newNode->word[sizeof(newNode->word) - 1] = '\0';
                        strncpy(newNode->syn, synToEnqueue, sizeof(newNode->syn) - 1); newNode->syn[sizeof(newNode->syn) - 1] = '\0';
                        strncpy(newNode->ant, antToEnqueue, sizeof(newNode->ant) - 1); newNode->ant[sizeof(newNode->ant) - 1] = '\0';
                        countVowelsConsonants(newNode->word, &(newNode->Vowels), &(newNode->Consonants));
                        newNode->Chars = newNode->Vowels + newNode->Consonants;

                        EnQueue(queueFromList, newNode);
                        printf("Word '%s' enqueued.\n", wordToEnqueue);
                         printf("Note: This change is in-memory only. To save, you would need a separate save function.\n");
                    }
                 }
                break;
            case 3: // Display Queue (empties queue)
                 printf("\n--- Displaying Queue (will empty the queue) ---\n");
                 if (*queueFromList == NULL || (*queueFromList)->head == NULL) {
                     printf("Queue is empty or has not been created. Use Merged List Option 5 or Stack Option 6 first.\n");
                 } else {
                     printf("Contents of the queue (dequeuing):\n");
                     BTList* current = NULL;
                     int count = 0;
                     while((current = DeQueue(*queueFromList)) != NULL) {
                         printf("  %-20s = %-20s # %-20s : Vowels %2d | Consonents %2d | Chars %2d \n", current->word, current->syn,current->ant,current->Vowels,current->Consonants,current->Chars);
                         free(current);
                         count++;
                     }
                     if (count == 0) {
                         printf("Queue was empty.\n");
                     } else {
                         printf("Queue is now empty after display.\n");
                     }
                 }
                 break;
            case 4: // Back to Main Menu
                running_menu = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
         if (running_menu) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }
}

void handleTreeOperations(TTree** dictionaryTree, const char* filename) {
    int choice;
    bool running_menu = true;
    char Target[20];
    TTree* foundNode = NULL; // Variable to store result of search

    while(running_menu) {
        printf("\n========== Tree Operations Menu ==========\n");
        printf(" 1. Fill Tree from File\n");
        printf(" 2. Display Tree (In-Order)\n");
        printf(" 3. Display Tree (Pre-Order)\n");
        printf(" 4. Display Tree (Post-Order)\n");
        printf(" 5. Search Word in Tree\n");
        printf(" 6. Delete Word from Tree\n"); // Added delete option
        printf(" 7. Back to Main Menu\n"); // Shifted Back option
        printf("==========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1: // Fill Tree from File
                 printf("\n--- Filling Tree from File ---\n");
                 if (*dictionaryTree != NULL) {
                     printf("Destroying existing tree before filling...\n");
                     DestroyTree(*dictionaryTree);
                     *dictionaryTree = NULL;
                 }
                 FILE* file = fopen(filename, "r");
                 if (file == NULL) {
                     perror("Error opening file to fill tree");
                 } else {
                     *dictionaryTree = fillTree(file);
                     fclose(file);
                     if (*dictionaryTree != NULL) {
                         printf("Tree filled from file successfully.\n");
                         // Note: The current fillTree builds based ONLY on Chars.
                         // Deletion of a specific word might be unreliable if duplicates exist
                         // and the tree isn't built with secondary string ordering.
                         printf("Note: Tree is built primarily by Character Count. Deletion of specific words with duplicate character counts may have unexpected behavior if the tree was not built with secondary alphabetical ordering.\n");
                     } else {
                         printf("Failed to fill tree from file. Check file format and fillTree function.\n");
                     }
                 }
                 break;
            case 2: // Display Tree (In-Order)
                 printf("\n--- Displaying Tree (In-Order) ---\n");
                 if (*dictionaryTree == NULL) {
                     printf("Tree is empty. Fill it first (Option 1).\n");
                 } else {
                     printTreeInOrder(*dictionaryTree);
                 }
                 break;
            case 3: // Display Tree (Pre-Order)
                 printf("\n--- Displaying Tree (Pre-Order) ---\n");
                 if (*dictionaryTree == NULL) {
                     printf("Tree is empty. Fill it first (Option 1).\n");
                 } else {
                     printTreePreOrder(*dictionaryTree);
                 }
                 break;
            case 4: // Display Tree (Post-Order)
                 printf("\n--- Displaying Tree (Post-Order) ---\n");
                 if (*dictionaryTree == NULL) {
                     printf("Tree is empty. Fill it first (Option 1).\n");
                 } else {
                     printTreePostOrder(*dictionaryTree);
                 }
                 break;
            case 5: // Search Word in Tree
                 printf("\n--- Search Word in Tree ---\n");
                 if (*dictionaryTree == NULL) {
                     printf("Tree is empty. Fill it first (Option 1).\n");
                 } else {
                    printf("Enter the word to search for: ");
                    if(scanf("%19s", Target) == 1) {
                        while (getchar() != '\n');
                        foundNode = getInfWordTree(*dictionaryTree, Target); // Assuming getInfWordTree uses SerchInBst
                        if (foundNode != NULL) {
                            printf("Word found in tree:\n");
                            PrintSingleColunm(foundNode);
                        } else {
                            printf("Word '%s' not found in tree.\n", Target);
                        }
                    } else {
                         printf("Invalid input for word.\n");
                         while (getchar() != '\n');
                    }
                 }
                 break;
            case 6: // Delete Word from Tree (New Option)
                 printf("\n--- Delete Word from Tree ---\n");
                 if (*dictionaryTree == NULL) {
                     printf("Tree is empty. Fill it first (Option 1).\n");
                 } else {
                    char wordToDeleteTree[20];
                    printf("Enter the word to delete from the tree: ");
                     if(scanf("%19s", wordToDeleteTree) == 1) {
                        while (getchar() != '\n');
                        *dictionaryTree = deleteWordBST(*dictionaryTree, wordToDeleteTree); // Call the corrected delete function
                        printf("Attempted to delete word '%s' from tree.\n", wordToDeleteTree);
                        printf("Note: Verify deletion by displaying the tree (Options 2-4).\n");
                     } else {
                         printf("Invalid input for word.\n");
                         while (getchar() != '\n');
                     }
                 }
                 break;
            case 7: // Back to Main Menu
                running_menu = false;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
         if (running_menu) {
             printf("\nPress Enter to continue...");
             getchar();
             printf("\n");
        }
    }
}
