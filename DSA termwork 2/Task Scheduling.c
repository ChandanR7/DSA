#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int workload;
} Processor;

int main() {
    int numProcessors, numTasks;

    printf("Enter the number of processors: ");
    scanf("%d", &numProcessors);
    printf("Enter the number of tasks: ");
    scanf("%d", &numTasks);

    Processor* processors = (Processor*)malloc(numProcessors * sizeof(Processor));

    for (int i = 0; i < numProcessors; i++) {
        processors[i].id = i;
        processors[i].workload = 0;
    }

    int* taskIDs = (int*)malloc(numTasks * sizeof(int));

    printf("Enter the task IDs:\n");
    for (int i = 0; i < numTasks; i++) {
        scanf("%d", &taskIDs[i]);
    }

    for (int i = 0; i < numTasks; i++) {
        int hash1 = taskIDs[i] % numProcessors;
        int hash2 = 1 + (taskIDs[i] % (numProcessors - 1));

        int processorIndex = hash1;

        while (processors[processorIndex].workload > 0) {
            processorIndex = (processorIndex + hash2) % numProcessors;
        }

        processors[processorIndex].workload += taskIDs[i];
    }

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error creating the output file.\n");
        return 1;
    }

    fprintf(outputFile, "Final state of the processors:\n");
    for (int i = 0; i < numProcessors; i++) {
        fprintf(outputFile, "Processor %d: Workload = %d\n", processors[i].id, processors[i].workload);
    }

    fclose(outputFile);
    printf("Output file created successfully.\n");

    free(processors);
    free(taskIDs);

    return 0;
}

