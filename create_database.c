//Title       : Create Database from File List
//Description : Reads words from multiple files listed in a linked list and populates a hash table, 
//              storing each unique word and the files it appears in with their respective counts.
// Parameters  : 
//      - mainnode **HT            : Pointer to the hash table where words are stored based on their hash index.
//      - Slist *filename_head     : Pointer to the head of a linked list containing file names to read words from.
// Returns     : SUCCESS (1) if the database is created and populated successfully, 
//              FAILURE (0) if there is an error in opening files or allocating memory.
#include "main.h"
int create_database(mainnode **HT, Slist *filename_head)
{
    Slist *temp = filename_head;

    while (temp) // Traverse through the file.
    {
        if (check_duplicate_filename(HT, temp->filename))
        {
            printf("Error: Duplicate filename '%s'. Skipping...\n", temp->filename);
            temp = temp->link;
            continue;
        }

        // Open each file and read words.
        FILE *fptr = fopen(temp->filename, "r");
        if (!fptr)
        {
            printf("Error: Could not open file '%s'.\n", temp->filename);
            return FAILURE;
        }

        char word[100];
        int ch, i = 0;
        while ((ch = fgetc(fptr)) != EOF) 
        {
            if (isalnum(ch))  // If it's a letter or digit, build a word
            {  
                word[i++] = ch;
            } 
            else  
            { 
                if (i > 0)  // If we have a word, process it
                {  
                    word[i] = '\0';
                    process_word(HT, word, temp->filename);
                    i = 0;
                }

                if (!isspace(ch))  // If it's a special character, store it separately
                {  
                    word[0] = ch;
                    word[1] = '\0';
                    process_word(HT, word, temp->filename);
                }
            }
        }
        fclose(fptr);
        temp = temp->link;
    }
    return SUCCESS;
}
void process_word(mainnode **HT, char *word, const char *filename)
{
    int index;
    if (isalpha(word[0])) 
    {
        index = tolower(word[0]) - 'a'; // Letters (A-Z, a-z) -> 0-25
    } 
    else if (isdigit(word[0])) 
    {
        index = 26; // Numbers (0-9) -> Index 26
    } 
    else 
    {
        index = 27; // Special characters -> Index 27
    }

    int word_found = 0;
    mainnode *main_node = find_or_create_mainnode(HT, index, word, &word_found);
    add_subnode(main_node, filename);
}


// Function to check if a filename already exists in the hash table
int check_duplicate_filename(mainnode **HT, const char *filename)
{
    for (int i = 0; i < 28; i++) // Loop through all 28 indices
    {
        mainnode *m = HT[i];
        while (m)
        {
            subnode *s = m->subnode;
            while (s)
            {
                if (strcmp(s->filename, filename) == 0)
                {
                    return 1;  // Duplicate found
                }
                s = s->subnode;
            }
            m = m->mainnode;
        }
    }
    return 0;  // No duplicate found
}

// Function to find an existing main node or create a new one
mainnode *find_or_create_mainnode(mainnode **HT, int index, const char *word, int *word_found)
{
    mainnode *m = HT[index];
    mainnode *prev = NULL;

    // Search 
    while (m)
    {
        if (strcmp(m->word, word) == 0)
        {
            return m;
        }
        prev = m;
        m = m->mainnode;
    }

    // Create
    mainnode *new_main = malloc(sizeof(mainnode));
    new_main->word = malloc(strlen(word) + 1);
    strcpy(new_main->word, word);
    new_main->filecount = 0;
    new_main->subnode = NULL;
    new_main->mainnode = NULL;

    if (prev)
        prev->mainnode = new_main;
    else
        HT[index] = new_main;

    return new_main;
}

// Function to add or update a subnode for a main node
void add_subnode(mainnode *main_node, const char *filename)
{
    subnode *s = main_node->subnode;
    subnode *prev_sub = NULL;

    while (s)
    {
        if (strcmp(s->filename, filename) == 0)
        {
            s->wordcount++;
            return;
        }
        prev_sub = s;
        s = s->subnode;
    }

    subnode *new_sub = malloc(sizeof(subnode));
    new_sub->wordcount = 1;
    new_sub->filename = malloc(strlen(filename) + 1);
    strcpy(new_sub->filename, filename);
    new_sub->subnode = NULL;

    if (prev_sub)
        prev_sub->subnode = new_sub;
    else
        main_node->subnode = new_sub;

    main_node->filecount++;
}
