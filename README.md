# Inverted-Search

📘 Inverted Search Project – Explanation

The Inverted Search project is a command-line based text indexing engine written in C, designed to efficiently search and retrieve data across multiple text files. It implements a simplified version of an inverted index — a data structure commonly used in search engines — where each word is mapped to the list of files in which it appears. This enables rapid, keyword-based search operations even across large volumes of data.

The program first scans and processes a directory of text files, extracts individual words, and builds an inverted index using a combination of hash tables and linked lists. Each word acts as a key in the hash table, and the corresponding value is a linked list that stores the names of all files containing that word, along with the frequency of occurrences in each file.

Key features include:

- Scanning and indexing multiple `.txt` files from a directory
- Building and storing an efficient inverted index in memory
- Searching for a word to list all files it appears in
- Displaying the frequency of each word per file
- Saving the index to a file and reloading it later for reuse
- Robust input validation and memory management

This project demonstrates advanced use of hash tables, linked lists, string tokenization, and file I/O. It provides a solid foundation in building scalable search algorithms and memory-efficient indexing systems — essential skills for roles involving system design, compilers, and data-driven application development.

🔹 What This Project Showcases:

- Implementation of real-world text indexing using hash tables
- File parsing, dynamic memory allocation, and linked list management
- Efficient search and retrieval system design in pure C
- Strong understanding of algorithmic thinking and data relationships

