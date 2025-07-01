// Title       : Update Database from Saved File
// Description : Reads data from a previously saved file and updates the hash table, 
//               reconstructing each main node and associated subnodes as needed.
// Parameters  : 
//      - mainnode **HT     : Pointer to the hash table where the data is to be stored.
//      - char *file_name   : Name of the file containing the saved database data.
// Returns     : SUCCESS (1) if the update is successful and data is loaded from the file,
//               FAILURE (0) if there is an error in reading the file or allocating memory.

#include "main.h" 
int update_database(mainnode **HT, char *backup_file) 
{
    // check the extension.
    if (strstr(backup_file, ".txt") == NULL)
    {
        printf("ERROR: Wrong extension\n");
        printf("USAGE: <filename.txt>\n");
        return FAILURE;
    }

    // Open a file in read mode.
    FILE *fptr = fopen(backup_file, "r");
    if (fptr == NULL)
    {
        printf("ERROR: Opening file\n");
        return FAILURE;
    }

    // check the file is empty.
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0) 
    {
        printf("INFO: File is Empty\n");
        printf("ERROR: Create Database First\n");
        fclose(fptr);
        return SUCCESS;
    }
    rewind(fptr);

    char temp[256];
    while (fscanf(fptr, "%s", temp) != EOF) 
    {
        // check for proper start character '#'.
        if (temp[0] == '#') 
        {
            // Hash index
            char *token = strtok(temp + 1, ";");
            int index = atoi(token);

            // Word
            token = strtok(NULL, ";");
            char *word = malloc(strlen(token) + 1);
            strcpy(word, token);

            // File count
            token = strtok(NULL, ";");
            int file_count = atoi(token);

            mainnode *main_node = HT[index];
            mainnode *prev = NULL;
            int word_found = 0;

            // Search or Create the main node. 
            while (main_node) 
            {
                if (strcmp(main_node->word, word) == 0) 
                {
                    word_found = 1;
                    break;
                }
                prev = main_node;
                main_node = main_node->mainnode;
            }

            if (!word_found) 
            {
                main_node = malloc(sizeof(mainnode));
                if (!main_node) 
                {
                    free(word);
                    fclose(fptr);
                    return FAILURE;
                }
                main_node->word = word;
                main_node->filecount = file_count;
                main_node->subnode = NULL;
                main_node->mainnode = NULL;

                if (prev)
                    prev->mainnode = main_node;
                else
                    HT[index] = main_node;
            } 
            else 
            {
                free(word);  
            }

            // Run a loop for file count times and fetch the filename and wordcount to store in the subnode.
            for (int i = 0; i < file_count; i++) 
            {
                // Filename
                token = strtok(NULL, ";");
                char *filename = malloc(strlen(token) + 1);
                strcpy(filename, token);

                // Wordcount
                token = strtok(NULL, ";");
                int wordcount = atoi(token);

                subnode *sub = main_node->subnode;
                subnode *sub_prev = NULL;
                int file_found = 0;
                
                while (sub) 
                {
                    if (strcmp(sub->filename, filename) == 0) 
                    { 
                        sub->wordcount = wordcount; 
                        file_found = 1;
                        break;
                    }
                    sub_prev = sub;
                    sub = sub->subnode;
                }

                if (!file_found) 
                {
                    subnode *new_sub = malloc(sizeof(subnode));
                    if (!new_sub) 
                    {
                        free(filename);
                        fclose(fptr);
                        return FAILURE;
                    }
                    new_sub->filename = filename;
                    new_sub->wordcount = wordcount;
                    new_sub->subnode = NULL;


                    if (sub_prev)
                        sub_prev->subnode = new_sub;
                    else
                        main_node->subnode = new_sub;
                } 
                else 
                {
                    free(filename);  
                }
            }
        }
        else
        {
            printf("ERROR: File Does not start with #,  So, It's not a saved file.\n");
            fclose(fptr);
            return FAILURE;
        }
    }

    fclose(fptr);
    return SUCCESS;
}