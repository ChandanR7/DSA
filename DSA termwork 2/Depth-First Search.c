#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjacencyList;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjacencyList = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    int i;
    for (i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void DFS(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjacencyList[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (!visited[connectedVertex]) {
            DFS(graph, connectedVertex, visited);
        }
        adjList = adjList->next;
    }
}

int main() {
    int numVertices, sourceVertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the source vertex: ");
    scanf("%d", &sourceVertex);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the adjacency list representation of the graph:\n");
    int i, j, numEdges, connectedVertex;
    for (i = 0; i < numVertices; i++) {
        printf("Vertex %d: ", i+1);
        scanf("%d", &numEdges);
        for (j = 0; j < numEdges; j++) {
            scanf("%d", &connectedVertex);
            addEdge(graph, i, connectedVertex-1);
        }
    }

    int* visited = (int*)calloc(numVertices, sizeof(int));

    printf("\nDFS Traversal:\n");
    DFS(graph, sourceVertex-1, visited);

    free(visited);
    free(graph);

    return 0;
}

