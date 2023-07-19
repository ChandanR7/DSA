#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned long long int tag;
    bool valid;
} CacheLine;

typedef struct {
    int associativity;
    int lineSize;
    CacheLine* lines;
} CacheSet;

typedef struct {
    int numSets;
    CacheSet* sets;
} CacheMemory;

// Function to initialize the cache memory
void initializeCacheMemory(CacheMemory* cache, int numSets, int associativity, int lineSize) {
    cache->numSets = numSets;
    cache->sets = (CacheSet*)malloc(numSets * sizeof(CacheSet));

    for (int i = 0; i < numSets; i++) {
        cache->sets[i].associativity = associativity;
        cache->sets[i].lineSize = lineSize;
        cache->sets[i].lines = (CacheLine*)malloc(associativity * sizeof(CacheLine));

        for (int j = 0; j < associativity; j++) {
            cache->sets[i].lines[j].valid = false;
        }
    }
}

// Function to perform linear probing in the cache memory
void linearProbing(CacheSet* set, unsigned long long int tag, unsigned long long int* accessedAddresses, int numAccesses) {
    for (int i = 0; i < numAccesses; i++) {
        int index = accessedAddresses[i] % set->associativity;
        int count = 0;

        while (count < set->associativity && set->lines[index].valid) {
            index = (index + 1) % set->associativity;
            count++;
        }

        if (!set->lines[index].valid) {
            set->lines[index].tag = tag;
            set->lines[index].valid = true;
        }
    }
}

// Function to print the cache memory state to the output file
void printCacheMemoryState(CacheMemory* cache, FILE* outputFile) {
    for (int i = 0; i < cache->numSets; i++) {
        fprintf(outputFile, "Set %d:\n", i);

        for (int j = 0; j < cache->sets[i].associativity; j++) {
            fprintf(outputFile, "  Line %d: ", j);

            if (cache->sets[i].lines[j].valid) {
                fprintf(outputFile, "0x%llx\n", cache->sets[i].lines[j].tag);
            } else {
                fprintf(outputFile, "-\n");
            }
        }
    }
}

int main() {
    int numSets, associativity, lineSize;
    int numAccesses;
    unsigned long long int* accessedAddresses;
    char filename[50];

    printf("Enter the number of sets in the cache memory: ");
    scanf("%d", &numSets);
    printf("Enter the associativity of each set: ");
    scanf("%d", &associativity);
    printf("Enter the line size (in bytes): ");
    scanf("%d", &lineSize);
    printf("Enter the number of memory access requests: ");
    scanf("%d", &numAccesses);

    accessedAddresses = (unsigned long long int*)malloc(numAccesses * sizeof(unsigned long long int));

    printf("Enter the memory access requests (in hexadecimal format):\n");
    for (int i = 0; i < numAccesses; i++) {
        scanf("%llx", &accessedAddresses[i]);
    }

    printf("Enter the output filename: ");
    scanf("%s", filename);

    FILE* outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        return 1;
    }

    CacheMemory cache;
    initializeCacheMemory(&cache, numSets, associativity, lineSize);

    for (int i = 0; i < numAccesses; i++) {
        unsigned long long int tag = accessedAddresses[i] / (lineSize * numSets);
        int setIndex = (accessedAddresses[i] / lineSize) % numSets;

        if (!cache.sets[setIndex].lines[tag % associativity].valid) {
            cache.sets[setIndex].lines[tag % associativity].tag = tag;
            cache.sets[setIndex].lines[tag % associativity].valid = true;
        } else {
            linearProbing(&cache.sets[setIndex], tag, &accessedAddresses[i], 1);
        }
    }

    printCacheMemoryState(&cache, outputFile);

    fclose(outputFile);
    printf("Output file created successfully.\n");

    return 0;
}

