#include "main.h"

int main(int argc, char *argv[]) 
{
    // Declare hash table and linked list for filenames
    mainnode *HT[28] = {NULL};  // Hash table initialization
    Slist *filename_head = NULL;  

    // Check if a backup file exists to load the database
    FILE *backup_fptr = fopen("check1.txt", "r");
    if (backup_fptr) {
        fclose(backup_fptr);  // File exists, so load data
        printf("INFO: Backup file found, attempting to load database...\n");
        if (update_database(HT, "check1.txt") == SUCCESS) {
            printf("INFO: Database loaded successfully from backup file.\n");
        } else {
            printf("ERROR: Failed to load database from backup file.\n");
        }
    }

    // Perform read and validation on input files
    if (!read_and_validate(argc, argv, &filename_head)) {  
        printf("ERROR: Command-line arguments validation failed.\n");
        return 0;  
    }

    printf("\nINFO: Read and Validation Completed Successfully.\n");

    int is_database_created = 0;
    int is_database_populated = 0;
    int option = 0;

    do {
        // Show options menu to the user
        printf("\nChoose an operation:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        printf("\n");

        // Switch case for each operation
        switch (option) {
            case 1:
                if(is_database_populated == 0) {
                    if (create_database(HT, filename_head) == SUCCESS) {
                        printf("INFO: Database created successfully.\n");
                        is_database_created = 1;
                        is_database_populated = 1;
                    } else {
                        printf("ERROR: Failed to create the database.\n");
                    }
                } else {
                    printf("ERROR: Only one time we are able to populate the Hashtable by calling the Create_database.\n");
                }
                break;

            case 2:
                display_database(HT);
                break;

            case 3:
                printf("INFO: Searching the database...\n");
                int result = search_database(HT);
                if (result == SUCCESS) {
                    printf("INFO: Search completed successfully.\n");
                } else if (result == DATA_NOT_FOUND) {
                    printf("ERROR: Search failed. No matching results found.\n");
                }
                break;

            case 4:
                if (is_database_created) {
                    if (save_database(HT) == SUCCESS) {
                        printf("INFO: Database saved successfully.\n");
                    } else {
                        printf("ERROR: Failed to save the database.\n");
                    }
                } else {
                    printf("ERROR: Database not created yet. Please create it first.\n");
                }
                break;

            case 5:
                if (!is_database_created) {
                    char file_name[50];
                    printf("Enter the name of the file to update the database: ");
                    scanf("%s", file_name);
                    if (update_database(HT, file_name) == SUCCESS) {
                        printf("INFO: Database updated successfully.\n");
                    } else {
                        printf("ERROR: Failed to validate or update the file.\n");
                    }
                } else {
                    printf("ERROR: Cannot update the database after creating the database.\n");
                }
                break;

            case 6:
                printf("INFO: Exiting the program.\n");
                free_hash_table(HT);  // Free memory before exiting
                break;

            default:
                printf("ERROR: Invalid option. Please choose a valid option from the menu.\n");
                break;
        }
    } while (option != 6);

    // Free the singly linked list before exit
    free_list(filename_head);

    return 0;
}
