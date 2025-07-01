// Title       : Search Word in Database
// Description : Searches for a specific word in the hash table, displaying the word's details including 
//               the files in which it appears and the occurrence count for each file.
// Parameters  : 
//      - mainnode **HT : Pointer to the hash table where the word search is performed.
// Returns     : SUCCESS (1) if the word is found and search completes successfully,
//               DATA_NOT_FOUND (2) if the word is not found,
//               FAILURE (0) if there is an error (e.g., if HT is uninitialized).
#include "main.h"
int search_database(mainnode **HT)
{
    // Input Word
    char word_input[50];
    printf("Enter a word: ");
    scanf("%s", word_input);

    // Hash Index Calculation
    int index = tolower(word_input[0]) % 97;
    if (index < 0 || index > 25) 
        index = 26;

    // Traverse the main node list at the calculated index
    mainnode *main = HT[index];
    if (main == NULL)
    {
        printf("ERROR: No entries found for this word '%s'.\n", word_input);
        return DATA_NOT_FOUND;
    }

    while (main)
    {
        if (strcmp(main->word, word_input) == 0)  
        {
            subnode *sub = main->subnode;
            printf("INFO: Word '%s' is present in the following files:\n", word_input);

            while (sub)
            {
                printf(" - Filename: <%s>, Wordcount: %d\n", sub->filename, sub->wordcount);
                sub = sub->subnode;
            }
            return SUCCESS;  
        }
        main = main->mainnode;  
    }

    printf("INFO: Word '%s' not found in any file.\n", word_input);
    return DATA_NOT_FOUND;
}
