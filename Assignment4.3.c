#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6 // Number of vertices in the graph

// Structure to represent a node in the priority queue
struct MinHeapNode {
    int v;
    int dist;
};

// Structure to represent a priority queue
struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode* array;
};

// Function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

// Function to create a Min Heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode*)malloc(capacity * sizeof(struct MinHeapNode));
    return minHeap;
}

// Function to swap two nodes in the priority queue
void swapMinHeapNode(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

// Heapify function to maintain heap property of the priority queue
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].dist < minHeap->array[smallest].dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].dist < minHeap->array[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

//  check if the priority queue is empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Function to extract the minimum distance node from the priority queue
struct MinHeapNode extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode root = minHeap->array[0];
    struct MinHeapNode lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->size--;

    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease the distance value of a vertex in the priority queue
void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
    int i;

    for (i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i].v == v)
            break;
    }

    minHeap->array[i].dist = dist;

    while (i && minHeap->array[i].dist < minHeap->array[(i - 1) / 2].dist) {
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// check if a vertex is in the priority queue
int isInMinHeap(struct MinHeap* minHeap, int v) {
    for (int i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i].v == v)
            return 1;
    }
    return 0;
}

// Function to print the distance array and path
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



// Function to implement Dijkstra's algorithm for a graph using a priority queue
void dijkstra(int graph[V][V], int src) {
    int dist[V];    // The output array dist[i] will hold the shortest distance from src to i
    int parent[V];  // Array to store the shortest path tree

    // Creating a priority queue to store vertices and their distances
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize all distances as INFINITE and parent[] as -1
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    // Distance of the source vertex from itself is 0
    dist[src] = 0;

    // Fill the minHeap with all vertices and their distances
    for (int i = 0; i < V; i++) {
        minHeap->array[i] = *newMinHeapNode(i, dist[i]);
        minHeap->size++;
    }

    // Find the shortest path for all vertices
    while (!isEmpty(minHeap)) {
        // Extract the vertex with the minimum distance value
        struct MinHeapNode minHeapNode = extractMin(minHeap);
        int u = minHeapNode.v;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it is in the priority queue, there's an edge from u to v, and the total weight of the path from src to v through u is smaller than the current value of dist[v]
            if (isInMinHeap(minHeap, v) && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Update the parent array
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }

    // Print the distance array and path
    printSolution(dist, parent);

    // // Freeing allocated memory for the priority queue
    free(minHeap->array);
    free(minHeap);
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

}