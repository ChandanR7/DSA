#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_TRANSITIONS 100

typedef struct {
    int from;
    int to;
} Transition;

typedef struct {
    int state;
    bool visited;
} StateNode;

// Function to perform model checking using BFS
void performModelChecking(int initialState, Transition transitions[], int numTransitions,
                          int desiredStates[], int numDesiredStates,
                          bool desiredProperties[], int numDesiredProperties,
                          FILE* outputFile) {
    StateNode states[MAX_STATES];
    for (int i = 0; i < MAX_STATES; i++) {
        states[i].state = i;
        states[i].visited = false;
    }

    // Initialize the BFS queue
    int queue[MAX_STATES];
    int front = -1, rear = -1;
    queue[++rear] = initialState;
    states[initialState].visited = true;

    while (front != rear) {
        int currentState = queue[++front];

        // Check desired states
        for (int i = 0; i < numDesiredStates; i++) {
            if (currentState == desiredStates[i]) {
                desiredProperties[i] = true;
            }
        }

        // Generate successor states
        for (int i = 0; i < numTransitions; i++) {
            if (transitions[i].from == currentState && !states[transitions[i].to].visited) {
                queue[++rear] = transitions[i].to;
                states[transitions[i].to].visited = true;
            }
        }
    }

    // Write the results to the output file
    for (int i = 0; i < numDesiredProperties; i++) {
        fprintf(outputFile, "Property %d: %s\n", i + 1, desiredProperties[i] ? "Satisfied" : "Not Satisfied");
    }
}

int main() {
    Transition transitions[MAX_TRANSITIONS];
    int numTransitions;
    int initialState;
    int desiredStates[MAX_STATES];
    int numDesiredStates;
    bool desiredProperties[MAX_STATES];
    int numDesiredProperties;
    char filename[50];

    printf("Enter the number of transitions: ");
    scanf("%d", &numTransitions);

    printf("Enter the transitions (from to):\n");
    for (int i = 0; i < numTransitions; i++) {
        scanf("%d %d", &transitions[i].from, &transitions[i].to);
    }

    printf("Enter the initial state: ");
    scanf("%d", &initialState);

    printf("Enter the number of desired states: ");
    scanf("%d", &numDesiredStates);

    printf("Enter the desired states:\n");
    for (int i = 0; i < numDesiredStates; i++) {
        scanf("%d", &desiredStates[i]);
    }

    printf("Enter the number of desired properties: ");
    scanf("%d", &numDesiredProperties);

    FILE* outputFile;
    printf("Enter the output filename: ");
    scanf("%s", filename);

    outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        return 1;
    }

    performModelChecking(initialState, transitions, numTransitions, desiredStates,
                         numDesiredStates, desiredProperties, numDesiredProperties, outputFile);

    fclose(outputFile);
    printf("Output file created successfully.\n");

    return 0;
}

