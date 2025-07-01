//Title       : Display Database
// Description : Displays the contents of the hash table, printing each word and the files in which it appears 
//               along with the occurrence count for each file.
// Parameters  : 
//      - mainnode **HT : Pointer to the hash table containing the indexed words and associated file information.

#include "main.h"
void display_database(mainnode **HT)
{
    printf("%-8s%-20s%-12s %s \t %s", "Index", "Word", "FileCount", "FileName", "WordCount");
    printf("\n");

    for (int i = 0; i < 28; i++)  // 26 letters + 1 for non alphabatic characters.
    {
        if (HT[i] != NULL)  // check wheather if it's not equal to NULL.
        {
            mainnode *temp = HT[i];  
            while (temp)    // traverse through the mainnode.
            {
                printf("%-8d%-20s%-12d", i, temp->word, temp->filecount);

                subnode *s = temp->subnode;  
                while (s)   // traverse through the subnode.
                {
                    printf("\n\t\t\t\t\t %s\t %d\t\n", s->filename, s->wordcount);
                    s = s->subnode;  
                }

                printf("\n");
                temp = temp->mainnode;  
            }
        }
    }
}
