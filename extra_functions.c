#include "main.h"


int read_and_validate(int argc, char *argv[], Slist **filename_head)
{
    if (argc < 2)
    {
        printf("ERROR: Please Enter FileNames\n");
        printf("Usage: ./a.out <file1.txt> <file2.txt> <file3.txt> ...\n");
        return FAILURE;
    }

    for (int i = 1; argv[i] != NULL; i++)
    {
        const char *first_dot = strchr(argv[i], '.');  // Find first '.'
        const char *last_dot = strrchr(argv[i], '.');  // Find last '.'
        
        // Ensure exactly one ".txt" and it appears only once
        if (!last_dot || strcmp(last_dot, ".txt") != 0 || first_dot != last_dot)
        {
            printf("ERROR: Invalid file extension for <%s>. Expected a single .txt file.\n", argv[i]);
            continue;
        }

        FILE *fptr = fopen(argv[i], "r");
        if (!fptr)
        {
            printf("ERROR: File <%s> Doesn't Exist\n", argv[i]);
            continue;
        }

        fseek(fptr, 0, SEEK_END);
        if (!ftell(fptr))
        {
            printf("ERROR: %s is EMPTY\n", argv[i]);
            fclose(fptr);
        }
        else
        {
            fclose(fptr);
            insert_at_last(filename_head, argv[i]);  // Add to list
            printf("INFO: File <%s> exists and is added to the list.\n", argv[i]);  // Confirmation message
        }
    }

    if (*filename_head == NULL)
    {
        printf("INFO: No valid files found. List is empty.\n");
    }
    else
    {
        print_list(*filename_head);
    }
    
    return SUCCESS;
}





int insert_at_last(Slist **filename_head, char *filename)
{
    Slist *new = malloc(sizeof(Slist));
    if (!new)
        return FAILURE;

    strcpy(new->filename, filename);
    new->link = NULL;

    if (*filename_head == NULL)
    {
        *filename_head = new;
        return SUCCESS;
    }

    Slist *temp = *filename_head;
    while (temp->link != NULL)
    {
        if (!strcmp(temp->filename, filename))
        {
            printf("ERROR: Duplicate File Detected\tMoving Next...\n");
            free(new);
            return SUCCESS;
        }
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}


void print_list(Slist *filename_head)
{
    if (!filename_head)
    {
        printf("INFO: List is empty\n");
        return;
    }

    int count = 0;
    while (filename_head)
    {
        printf("%s -> ", filename_head->filename);
        filename_head = filename_head->link;
        count++;
    }
    printf("NULL\n");
    printf("INFO: Total files in the list: %d\n", count);
}


void free_list(Slist *filename_head)
{
    Slist *temp;
    while (filename_head)
    {
        temp = filename_head;       
        filename_head = filename_head->link; 
        free(temp);                  
    }
}


void free_hash_table(mainnode **HT)
{
    for (int i = 0; i < 27; i++)
    {
        mainnode *m = HT[i];
        while (m)
        {
            subnode *s = m->subnode;
            while (s)
            {
                subnode *temp_sub = s;
                s = s->subnode;
                free(temp_sub->filename);
                free(temp_sub);
            }
            mainnode *temp_main = m;
            m = m->mainnode;
            free(temp_main->word);
            free(temp_main);
        }
    }
}




