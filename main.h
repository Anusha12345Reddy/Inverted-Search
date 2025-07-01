#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NAMELENGTH 50  
#define FAILURE 0
#define SUCCESS 1
#define DATA_NOT_FOUND 2

// Structure for linked list node containing filenames
typedef struct Slist_node
{
    char filename[NAMELENGTH]; // Filename of the current node
    struct Slist_node *link;   // Pointer to the next node in the list
} Slist;

// Structure for subnode (file information)
typedef struct sub_node
{
    int wordcount;        // Count of occurrences of the word in the file
    char *filename;      // Filename where the word appears
    struct sub_node *subnode; // Pointer to the next subnode (if any)
} subnode;

// Structure for mainnode (word information)
typedef struct main_node
{
    int filecount;       // Count of unique files the word appears in
    char *word;          // The word itself
    subnode *subnode;    // Pointer to the subnode (file-related data)
    struct main_node *mainnode; // Pointer to the next mainnode in the hash table chain
} mainnode;

// Function prototypes

// Reads and validates command line arguments, returns pointer to filename list
int read_and_validate(int argc, char *argv[], Slist **filename_head);

// Inserts a filename at the end of the filename linked list
int insert_at_last(Slist **filename_head, char *filename);

// Prints the list of filenames
void print_list(Slist *filename_head);

// Frees the memory allocated for the filename linked list
void free_list(Slist *filename_head);

// Frees the memory allocated for the hash table (mainnode and subnode structures)
void free_hash_table(mainnode **HT);

// Creates the word database from the list of filenames
int create_database(mainnode **HT, Slist *filename_head);

// Displays the contents of the word database
void display_database(mainnode **HT);

// Searches the database for a specific word (not implemented)
int search_database(mainnode **HT);

// Saves the database to a file (not implemented)
int save_database(mainnode **HT);

// Updates the database (not implemented)
int update_database(mainnode **HT, char *file_name);

// Function prototypes
int check_duplicate_filename(mainnode **HT, const char *filename);
void add_subnode(mainnode *main_node, const char *filename);
void process_word(mainnode **HT, char *word, const char *filename);
mainnode *find_or_create_mainnode(mainnode **HT, int index, const char *word, int *word_found);

#endif // MAIN_H
