#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Function to check if a cell is a valid and open
bool isValidCell(int maze[MAX_SIZE][MAX_SIZE], int n, int m, int row, int col) {
    if (row >= 0 && row < n && col >= 0 && col < m && maze[row][col] == 1) {
        return true;
    }
    return false;
}

// Function to solve the maze using DFS
bool solveMazeDFS(int maze[MAX_SIZE][MAX_SIZE], int n, int m, int row, int col, int solution[MAX_SIZE][MAX_SIZE]) {
    // Check if the current cell is the goal
    if (row == n - 1 && col == m - 1) {
        solution[row][col] = 1;
        return true; // Maze is solved
    }

    // Check if the current cell is a valid move
    if (isValidCell(maze, n, m, row, col)) {
        // Mark the current cell as part of the solution path
        solution[row][col] = 1;

        // Move to the next cells in all possible directions
        if (solveMazeDFS(maze, n, m, row + 1, col, solution)) // Move down
            return true;
        if (solveMazeDFS(maze, n, m, row, col + 1, solution)) // Move right
            return true;
        if (solveMazeDFS(maze, n, m, row - 1, col, solution)) // Move up
            return true;
        if (solveMazeDFS(maze, n, m, row, col - 1, solution)) // Move left
            return true;

        // If none of the directions lead to the goal, backtrack
        solution[row][col] = 0;
        return false;
    }
    return false;
}

int main() {
    int maze[MAX_SIZE][MAX_SIZE];
    int solution[MAX_SIZE][MAX_SIZE];
    int n, m;
    char filename[50];

    printf("Enter the number of rows in the maze: ");
    scanf("%d", &n);
    printf("Enter the number of columns in the maze: ");
    scanf("%d", &m);

    printf("Enter the maze grid (1 for open cell, 0 for blocked cell):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    if (solveMazeDFS(maze, n, m, 0, 0, solution)) {
        printf("Solution path found!\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", solution[i][j]);
            }
            printf("\n");
        }
        printf("Enter the output filename: ");
        scanf("%s", filename);

        FILE* outputFile = fopen(filename, "w");
        if (outputFile == NULL) {
            printf("Error opening the output file.\n");
            return 1;
        }

        fprintf(outputFile, "Solution path found!\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fprintf(outputFile, "%d ", solution[i][j]);
            }
            fprintf(outputFile, "\n");
        }

        fclose(outputFile);
        printf("Output file created successfully.\n");
    } else {
        printf("No solution path found.\n");
    }

    return 0;
}

