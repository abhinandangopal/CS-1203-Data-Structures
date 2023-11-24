#include <stdio.h>
#include <limits.h>

#define V 4 // Number of vertices in the graph

// Function to print shortest distances and the parent matrix
void printSolution(int dist[][V], int parent[][V]) {
    // Print the shortest distances between every pair of vertices
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t"); // for infinite distance
            else
                printf("%d\t", dist[i][j]); // Print the distance
        }
        printf("\n");
    }

    // Printing the parent matrix showing intermediate nodes for shortest paths
    printf("\nParent matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (parent[i][j] == -1)
                printf("NIL\t"); // If parent is -1, print 'NIL'
            else
                printf("%d\t", parent[i][j]); // Printing the parent node
        }
        printf("\n");
    }
}

// Function to find shortest paths using Floyd-Warshall algorithm
void floydWarshall(int graph[][V]) {
    int dist[V][V]; // Matrix to store shortest distances
    int parent[V][V]; // Matrix to store parent information

    // Initializing distances and parent matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j]; // Initialize distances
            if (graph[i][j] != INT_MAX && i != j)
                parent[i][j] = i; // Set parent as the source node
            else
                parent[i][j] = -1; // Setting parent as -1 for unreachable nodes or self-loops
        }
    }

    // Main algorithm for computing the shortest paths and updating parent matrix
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j]; // Update shortest distance
                    parent[i][j] = parent[k][j]; // Update parent matrix
                }
            }
        }
    }

    // Check for any negative cycles in the graph
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains negative cycle(s).\n");
            return; // Exit if a negative cycle is found
        }
    }

    // If no negative cycles, print the computed distances and parent matrix
    printSolution(dist, parent);
}

int main() {
    int graph[V][V] = {
        {0, 5, INT_MAX, 10},
        {INT_MAX, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 1},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    floydWarshall(graph);
    return 0;
}
