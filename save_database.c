// Title       : Save Database to File
// Description : Saves the contents of the hash table to a file, allowing the database to be reloaded later. 
//               Each unique word, along with the files and counts where it appears, is saved in a structured format.
// Parameters  : 
//      - mainnode **HT : Pointer to the hash table that contains the data to be saved.
// Returns     : SUCCESS (1) if the database is successfully saved to a file,
//               FAILURE (0) if there is an error in file handling.
#include "main.h"
int save_database(mainnode **HT)
{
    // Input Filename
    char f_name[NAMELENGTH];
    printf("Enter BackUp file name: ");
    scanf("%s", f_name);

    // Check extension.
    if (strcmp(strstr(f_name, "."), ".txt"))
    {
        printf("ERROR: Please include a .txt extension\n");
        return FAILURE;
    }

    // Open File for writing.
    FILE *fptr = fopen(f_name, "w");
    if (!fptr)
    {
        printf("ERROR: Unable to open file for writing\n");
        return FAILURE;
    }

    // Loop through Hash Table: Write each main node’s data, and all subnode details to the file.
    for (int i = 0; i < 27; i++)  
    {
        mainnode *temp = HT[i];
        while (temp)
        {
            fprintf(fptr, "#%d;%s;%d;", i, temp->word, temp->filecount);

            subnode *temp_subnode = temp->subnode;
            while (temp_subnode)
            {
                fprintf(fptr, "%s;%d;", temp_subnode->filename, temp_subnode->wordcount);
                temp_subnode = temp_subnode->subnode;
            }
            fprintf(fptr, "#\n");

            temp = temp->mainnode;  
        }
    }

    if (fclose(fptr) != 0)
    {
        printf("ERROR: Failed to close the file properly\n");
        return FAILURE;
    }
    
    return SUCCESS;
}
