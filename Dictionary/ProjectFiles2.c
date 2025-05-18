#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
void swapC(char*c,char*b){
    char temp=*c;
    *c=*b;
    *b=temp;
}
void permutations(char str[],char *head){
    if (strlen(str)==2)
    {
        swapC(&str[0],&str[1]);
        printf("%s\n",head);
        swapC(&str[0],&str[1]);
        printf("%s\n",head);
    }
    else
    {   
        char temp[strlen(str)];
        strcpy(temp,str);
        for (int i = 0; i < strlen(str); i++)
        {
            permutations(str+1,head);
            strcpy(str,temp);
            swapC(&str[0],&str[i+1]);
        }
    }
    
}
void printSub(char str[]){
    int size=strlen(str),k=0;
    if (size==1)
    {
        printf("%s\n",str);
        return;
    }
    char temp[size-1];
    printf("%s\n",str);
    for (int i = 0; i < size; i++)
    { 
        k=0;
        for (int j = 0; j < size; j++)
        {
            if (i!=j)
            {   
                temp[k]=str[j];
                k++;
            }
           
        }
        temp[size-1]='\0';
        printSub(temp);
    }
}
int countWordOccurence(FILE *file_name, char *word){
    char buffer[100]; 
    int checker;
    if (fgets(buffer, sizeof(buffer), file_name)==NULL)
    {
        return 0;
    }
    else
    {
        char word1[20];
        char ant[20];
        char syn[20];
        int counter=0;
        checker=sscanf(buffer, "%19[^=]=%19[^#]#%19[^\n]",word1,syn,ant);
        if (checker==3)
        {
            if (strcmp(word,word1)==0)
            {
                counter++;
            }
            if (strcmp(word,syn)==0)
            {
                counter++;
            }
            if (strcmp(word,ant)==0)
            {
                counter++;
            }
        }
        return countWordOccurence(file_name,word)+counter;
    }
}
void DeleateWordInFile(FILE*original_file,char*word){
    // Validate inputs to ensure they are not NULL
    if (word == NULL) {
        return;
    }

    // Hardcoded filename - This function will always operate on this file.
    const char* filename = "file.txt";

    FILE *temp_file;
    char buffer[256]; // Buffer to read lines from the file. Adjust size if lines can be longer.
    char temp_filename[] = "temp_dict.txt"; // Name for the temporary file
    bool found_and_updated = false; // Flag to track if the word was found and its line was updated
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

        // Create a copy of the buffer to parse. This is important because sscanf might
        // modify the buffer, and we might need the original buffer content for lines
        // that are not being updated or don't match the expected format.
        char buffer_copy[sizeof(buffer)];
        strncpy(buffer_copy, buffer, sizeof(buffer_copy) - 1); // Copy with size limit
        buffer_copy[sizeof(buffer_copy) - 1] = '\0'; // Ensure null termination for safety

        // Remove trailing newline from buffer_copy if present. This is necessary
        // for accurate string comparison and parsing.
        buffer_copy[strcspn(buffer_copy, "\n")] = 0;

        // Attempt to parse the line using sscanf based on the expected format "word=syn#ant"
        // - %19[^=] reads up to 19 characters excluding '=', into file_word.
        // - = matches the literal '=' character.
        // - %19[^#] reads up to 19 characters excluding '#', into file_syn.
        // - # matches the literal '#' character.
        // - %19[^\n] reads up to 19 characters excluding newline, into file_ant.
        // sscanf returns the number of items successfully matched and assigned.
        int scan_result = sscanf(buffer_copy, "%19[^=]=%19[^#]#%19[^\n]", file_word, file_syn, file_ant);

        // Check if sscanf successfully read at least the word part (scan_result >= 1)
        // AND if the extracted word matches the target word we are looking for (strcmp == 0).
        if (scan_result >= 1 && strcmp(file_word, word) == 0) {
            found_and_updated = true; // Set the flag as the word was found and updated
        } else {
            // This line does not contain the word to update, or its format is unexpected.
            // Write the original line back to the temporary file.
            // We use the original 'buffer' here because it includes the original newline character.
            fprintf(temp_file, "%s", buffer);
        }
    }

    // Close both the original and temporary files
    fclose(original_file);
    fclose(temp_file);

    // After processing the entire file, check if the word was found and updated.
    if (!found_and_updated) {
        // If the word was not found in the file, inform the user and remove the temporary file
        // as it contains an exact copy of the original file (no changes were made).
        printf("Word '%s' not found in the file. File not updated.\n", word);
        remove(temp_filename); // Remove the temporary file
        return; // Exit the function
    }

    // If the word was found and updated, proceed to replace the original file with the temporary file.
    // First, remove the original file.
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

FILE *removeWordOccurence(FILE *f, char *word){
    if (countWordOccurence(f,word)==0)
    {
        return f;
    }
    else
    {
        DeleateWordInFile(f,word);
        return removeWordOccurence(f,word);
    }
}
void updateWordInFile(const char* word, const char* syne, const char* anton){

    if (word == NULL || syne == NULL || anton == NULL) {
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
void updateWordItselfInFile(const char* word, const char* syne){

    if (word == NULL || syne == NULL ) {
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
            fprintf(temp_file, "%s=%s#%s\n", syne, file_syn, file_ant);
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
int countWordOccurenceInWord(FILE *file_name, char *word){
    char buffer[100]; 
    int checker;
    if (fgets(buffer, sizeof(buffer), file_name)==NULL)
    {
        return 0;
    }
    else
    {
        char word1[20];
        char ant[20];
        char syn[20];
        int counter=0;
        checker=sscanf(buffer, "%19[^=]=%19[^#]#%19[^\n]",word1,syn,ant);
        if (checker==3)
        {
            if (strcmp(word,word1)==0)
            {
                counter++;
            }
            
        }
        return countWordOccurenceInWord(file_name,word)+counter;
    }
}
FILE *replaceWordOccurence(FILE *f, char *word, char *rep){
    if (countWordOccurenceInWord(f,word)==0)
    {
        return f;
    }
    else
    {
        updateWordItselfInFile(word,rep);
    }
}
bool isPalindromWord(char *word,int size){
    if (size==0||size==1)
    {
        return true;
    }
    if (word[0]!=word[size-1])
    {
        return false;
    }
    else
    {
        return true&&isPalindromWord(word+1,size-2);
    }
}
int distinctSubseqWord(char *word) {
    if (word == NULL) {
        return 0;
    }

    int n = strlen(word);

    if (n == 0) {
        return 1; 
    }

    int *dp = malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    int last[256];
    for (int i = 0; i < 256; ++i) {
        last[i] = 0;
    }

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        dp[i] = 2 * dp[i - 1];

        char current_char = word[i - 1];
        if (last[current_char] > 0) {
            dp[i] -= dp[last[current_char] - 1];
        }

        last[current_char] = i;
    }

    int result = dp[n];

    return result;
}
int main() {
    int choice;
    char input_string[100];
    char *head=&(input_string[0]);
    char word[100], syn[100], anton[100], rep[100];
    int size;
    FILE *file_ptr = NULL; // File pointer for file operations

    // WARNING: Placeholder definitions for syne and anton to allow the original
    // DeleateWordInFile function to compile, as it incorrectly referenced these.
    // These are not used correctly by the original DeleateWordInFile.
    // The update functions expect these as user input.
    char placeholder_syne[100] = "";
    char placeholder_anton[100] = "";


    while (1) {
        printf("\n=== Test Menu for Original C Functions ===\n");
        printf("1. Test permutations(char str[], char *head)\n");
        printf("2. Test printSub(char str[])\n");
        printf("3. Test countWordOccurence(FILE *file_name, char *word)\n");
        printf("4. Test DeleateWordInFile(FILE*original_file,char*word)\n");
        printf("5. Test removeWordOccurence(FILE *f, char *word)\n");
        printf("6. Test updateWordInFile(const char* word, const char* syne, const char* anton)\n");
        printf("7. Test updateWordItselfInFile(const char* word, const char* syne)\n");
        printf("8. Test countWordOccurenceInWord(FILE *file_name, char *word)\n");
        printf("9. Test replaceWordOccurence(FILE *f, char *word, char *rep)\n");
        printf("10. Test isPalindromWord(char *word,int size)\n");
        printf("11. Test distinctSubseqWord(char *word)\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter a string for permutations: ");
                fgets(input_string, sizeof(input_string), stdin);
                input_string[strcspn(input_string, "\n")] = 0; // Remove newline
                printf("--- Permutations (Original Function) ---\n");
                // WARNING: The original permutations function is flawed.
                // The 'head' parameter is used incorrectly internally.
                // Passing input_string as both parameters might not work as intended by the original logic.
                // A corrected version would typically only need the string and starting index.
                permutations(input_string, head);
                printf("---------------------------------------\n");
                break;

            case 2:
                printf("Enter a string for printSub: ");
                fgets(input_string, sizeof(input_string), stdin);
                input_string[strcspn(input_string, "\n")] = 0; // Remove newline
                 printf("--- Subsequences (Original printSub) ---\n");
                // WARNING: The original printSub function generates subsequences with duplicates.
                printSub(input_string);
                 printf("----------------------------------------\n");
                break;

            case 3:
                printf("Enter the word to count: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                file_ptr = fopen("file.txt", "r");
                if (file_ptr == NULL) {
                    perror("Error opening file.txt");
                    break;
                }
                printf("--- Word Occurrence Count (Original Function) ---\n");
                // WARNING: The original countWordOccurence uses flawed recursive file I/O.
                // The count will likely be incorrect as the file pointer is not reset for each recursive call.
                printf("Counting word '%s' in file.txt...\n", word);
                int count = countWordOccurence(file_ptr, word);
                printf("Original function reported count: %d\n", count);
                printf("-------------------------------------------------\n");
                fclose(file_ptr); // Close the file
                break;

            case 4:
                 printf("Enter the word to delete lines for: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                file_ptr = fopen("file.txt", "r+"); // Open for read/write to allow passing FILE*
                 if (file_ptr == NULL) {
                    perror("Error opening file.txt");
                    break;
                }
                printf("--- Delete Word in File (Original DeleateWordInFile) ---\n");
                // WARNING: The original DeleateWordInFile is severely flawed.
                // It ignores the passed FILE*, hardcodes the filename, references undefined variables,
                // and its logic is a mix of deletion and update.
                // Calling this function will likely not work as intended and might crash
                // due to the placeholder variables or incorrect file handling.
                printf("Attempting to delete lines for word '%s' from file.txt...\n", word);
                DeleateWordInFile(file_ptr, word); // WARNING: Calling the flawed original function
                printf("--------------------------------------------------------\n");
                 fclose(file_ptr); // Close the file
                break;

            case 5:
                printf("Enter the word to remove occurrences for: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                 file_ptr = fopen("file.txt", "r+"); // Open for read/write to allow passing FILE*
                 if (file_ptr == NULL) {
                    perror("Error opening file.txt");
                    break;
                }
                printf("--- Remove Word Occurrence (Original Function) ---\n");
                // WARNING: The original removeWordOccurence uses flawed recursive file I/O
                // and depends on the flawed countWordOccurence and DeleateWordInFile.
                // It will likely lead to incorrect behavior or infinite recursion.
                printf("Attempting to remove occurrences of word '%s' from file.txt...\n", word);
                // WARNING: Calling the flawed original function
                FILE* result_ptr = removeWordOccurence(file_ptr, word);
                // WARNING: The returned file pointer might not be in a valid state.
                if (result_ptr == NULL) {
                     printf("removeWordOccurence returned NULL.\n");
                } else {
                     printf("removeWordOccurence returned a file pointer.\n");
                }
                printf("--------------------------------------------------\n");
                 fclose(file_ptr); // Close the file
                break;

            case 6:
                printf("Enter the word to update: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                printf("Enter the new synonym: ");
                fgets(syn, sizeof(syn), stdin);
                syn[strcspn(syn, "\n")] = 0; // Remove newline

                printf("Enter the new antonym: ");
                fgets(anton, sizeof(anton), stdin);
                anton[strcspn(anton, "\n")] = 0; // Remove newline

                printf("--- Update Word in File (Original Function) ---\n");
                // WARNING: The original updateWordInFile hardcodes the filename and does not take FILE*.
                // Calling it directly is consistent with its original signature.
                printf("Attempting to update word '%s' in file.txt...\n", word);
                updateWordInFile(word, syn, anton);
                printf("-----------------------------------------------\n");
                break;

            case 7:
                printf("Enter the word to update: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                printf("Enter the replacement word: ");
                fgets(rep, sizeof(rep), stdin);
                rep[strcspn(rep, "\n")] = 0; // Remove newline

                printf("--- Update Word Itself in File (Original Function) ---\n");
                // WARNING: The original updateWordItselfInFile hardcodes the filename and does not take FILE*.
                // Calling it directly is consistent with its original signature.
                printf("Attempting to replace word '%s' with '%s' in file.txt...\n", word, rep);
                updateWordItselfInFile(word, rep); // Original function used 'syne' parameter here
                printf("------------------------------------------------------\n");
                break;

            case 8:
                printf("Enter the word to count (in word field only): ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                file_ptr = fopen("file.txt", "r");
                if (file_ptr == NULL) {
                    perror("Error opening file.txt");
                    break;
                }
                printf("--- Word Occurrence Count (Word Field Only - Original Function) ---\n");
                // WARNING: The original countWordOccurenceInWord uses flawed recursive file I/O.
                // The count will likely be incorrect as the file pointer is not reset for each recursive call.
                printf("Counting word '%s' in word field in file.txt...\n", word);
                count = countWordOccurenceInWord(file_ptr, word);
                printf("Original function reported count: %d\n", count);
                printf("------------------------------------------------------------------\n");
                fclose(file_ptr); // Close the file
                break;

            case 9:
                printf("Enter the word to replace: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0; // Remove newline

                printf("Enter the replacement word: ");
                fgets(rep, sizeof(rep), stdin);
                rep[strcspn(rep, "\n")] = 0; // Remove newline

                 file_ptr = fopen("file.txt", "r+"); // Open for read/write to allow passing FILE*
                 if (file_ptr == NULL) {
                    perror("Error opening file.txt");
                    break;
                }
                printf("--- Replace Word Occurrence (Original Function) ---\n");

                printf("Attempting to replace word '%s' with '%s' in file.txt...\n", word, rep);
                 // WARNING: Calling the flawed original function
                result_ptr = replaceWordOccurence(file_ptr, word, rep);
                 // WARNING: The returned file pointer might not be in a valid state.
                if (result_ptr == NULL) {
                     printf("replaceWordOccurence returned NULL.\n");
                } else {
                     printf("replaceWordOccurence returned a file pointer.\n");
                }
                printf("-------------------------------------------------\n");
                 fclose(file_ptr); // Close the file
                break;

            case 10:
                printf("Enter a word to check for palindrome: ");
                fgets(input_string, sizeof(input_string), stdin);
                input_string[strcspn(input_string, "\n")] = 0; // Remove newline
                size = strlen(input_string);
                printf("--- Palindrome Check (Original Function) ---\n");
                // WARNING: The original isPalindromWord has incorrect base cases and termination.
                // It will likely cause issues or infinite recursion for palindromes.
                printf("Checking if '%s' is a palindrome...\n", input_string);
                // WARNING: Calling the flawed original function
                if (isPalindromWord(input_string, size)) {
                    printf("Original function result: '%s' IS a palindrome.\n", input_string);
                } else {
                    printf("Original function result: '%s' IS NOT a palindrome.\n", input_string);
                }
                printf("--------------------------------------------\n");
                break;

            case 11:
                printf("Enter a word for distinct subsequences: ");
                fgets(input_string, sizeof(input_string), stdin);
                input_string[strcspn(input_string, "\n")] = 0; // Remove newline
                printf("--- Distinct Subsequences Count (Original Function) ---\n");
                 // WARNING: The original distinctSubseqWord has a memory leak (doesn't free dp).
                printf("Counting distinct subsequences for '%s'...\n", input_string);
                int distinct_count = distinctSubseqWord(input_string);
                 printf("Original function reported count: %d\n", distinct_count);
                 printf("-----------------------------------------------------\n");
                // NOTE: In a real test, you would free the memory allocated by distinctSubseqWord here
                // if you couldn't modify the original function.
                break;

            case 12:
                printf("Exiting test program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}