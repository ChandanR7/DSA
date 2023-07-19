#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    char* word;
} DictionaryEntry;

typedef struct {
    DictionaryEntry* entries;
    int size;
} HashTable;

// Hash function
int hash(char* word) {
    int hashValue = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        hashValue = (hashValue * 31 + word[i]) % TABLE_SIZE;
    }

    return hashValue;
}

// Initialize the hash table
void initializeHashTable(HashTable* hashTable, int size) {
    hashTable->entries = (DictionaryEntry*)malloc(size * sizeof(DictionaryEntry));
    hashTable->size = size;

    for (int i = 0; i < size; i++) {
        hashTable->entries[i].word = NULL;
    }
}

// Insert a word into the hash table using quadratic probing
void insertWord(HashTable* hashTable, char* word) {
    int index = hash(word);
    int i = 1;

    while (hashTable->entries[index].word != NULL) {
        index = (index + i * i) % hashTable->size;
        i++;
    }

    hashTable->entries[index].word = strdup(word);
}

// Search for a word in the hash table using quadratic probing
bool searchWord(HashTable* hashTable, char* word) {
    int index = hash(word);
    int i = 1;

    while (hashTable->entries[index].word != NULL) {
        if (strcmp(hashTable->entries[index].word, word) == 0) {
            return true;
        }

        index = (index + i * i) % hashTable->size;
        i++;
    }

    return false;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable, TABLE_SIZE);

    FILE* dictionaryFile = fopen("dictionary.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Error opening the dictionary file.\n");
        return 1;
    }

    // Read the dictionary file and insert words into the hash table
    char word[100];
    while (fgets(word, sizeof(word), dictionaryFile) != NULL) {
        word[strcspn(word, "\n")] = '\0';  // Remove the newline character
        insertWord(&hashTable, word);
    }

    fclose(dictionaryFile);

    // Prompt the user to enter words for spell checking
    char input[100];
    printf("Enter a word for spell checking (or type 'exit' to quit): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove the newline character

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error creating the output file.\n");
        return 1;
    }

    while (strcmp(input, "exit") != 0) {
        bool isSpelledCorrectly = searchWord(&hashTable, input);

        if (isSpelledCorrectly) {
            printf("The word '%s' is spelled correctly.\n", input);
            fprintf(outputFile, "The word '%s' is spelled correctly.\n", input);
        } else {
            printf("The word '%s' is spelled incorrectly.\n", input);
            fprintf(outputFile, "The word '%s' is spelled incorrectly.\n", input);
        }

        printf("\nEnter a word for spell checking (or type 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove the newline character
    }

    fclose(outputFile);
    printf("Output file created successfully.\n");

    return 0;
}

