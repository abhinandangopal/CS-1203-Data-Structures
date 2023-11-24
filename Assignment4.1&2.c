#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6 // Defining number of vertices in the graph

// declare function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// printing the distance from the source and the path
void printSolution(int dist[], int parent[]) {
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\t\t\t", i, dist[i]);
        int path[V], pathIndex = 0;
        int j = i;
        while (j != -1) {
            path[pathIndex++] = j;
            j = parent[j];
        }
        for (int k = pathIndex - 1; k >= 0; k--) {
            printf("%d ", path[k]);
        }
        printf("\n");
    }
}


// Function to implement Dijkstra's algorithm 
void dijkstra(int graph[V][V], int src) {
    int dist[V];    // The output array dist[i] will hold the shortest distance from src to i
    int sptSet[V];  // sptSet[i] is true if vertex i is included in the shortest path tree
    int parent[V];  // Array to store the shortest path tree

    // Initialize all distances as INFINITE, sptSet[] as false, and parent[] as -1
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1; 
    }

    // Distance of the source vertex from itself is 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
       // u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as already processed vertex
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // if dist[v] is not in the sptSet, there is an edge from u to v, and the total weight of the path from src to v through u is smaller than the current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Update parent
            }
        }
    }

    // Print the distance array and path
    printSolution(dist, parent);
}

// main program
int main() {
    int graph[V][V] = {{0, 1, 4, 0, 0, 0},
                       {1, 0, 4, 2, 7, 0},
                       {4, 4, 0, 3, 5, 0},
                       {0, 2, 3, 0, 4, 6},
                       {0, 7, 5, 4, 0, 7},
                       {0, 0, 0, 6, 7, 0}};

    dijkstra(graph, 0);

    return 0;
}