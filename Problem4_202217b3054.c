#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 2001
#define INF INT_MAX

// Adjacency list node
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Graph structure
typedef struct {
    Node* head[MAX_NODES];
} Graph;

// Min-Heap structure for Dijkstra's algorithm
typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int* position;
    MinHeapNode** array;
} MinHeap;

// Utility function to create a new adjacency list node
Node* newNode(int vertex, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    return node;
}

// Utility function to create a graph
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_NODES; i++)
        graph->head[i] = NULL;
    return graph;
}

// Utility function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* node = newNode(dest, weight);
    node->next = graph->head[src];
    graph->head[src] = node;

    node = newNode(src, weight);
    node->next = graph->head[dest];
    graph->head[dest] = node;
}

// Utility function to create a new Min-Heap node
MinHeapNode* newMinHeapNode(int vertex, int distance) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->distance = distance;
    return minHeapNode;
}

// Utility function to create a Min-Heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->position = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Utility function to swap two Min-Heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify at given index
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->distance < minHeap->array[smallest]->distance)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->distance < minHeap->array[smallest]->distance)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->position[smallestNode->vertex] = idx;
        minHeap->position[idxNode->vertex] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Utility function to check if the Min-Heap is empty
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extract the minimum node from the heap
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];

    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->position[root->vertex] = minHeap->size - 1;
    minHeap->position[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Decrease the distance value of a vertex
void decreaseKey(MinHeap* minHeap, int vertex, int distance) {
    int i = minHeap->position[vertex];
    minHeap->array[i]->distance = distance;

    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance) {
        minHeap->position[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->position[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Utility function to check if a vertex is in the Min-Heap
int isInMinHeap(MinHeap* minHeap, int vertex) {
    return minHeap->position[vertex] < minHeap->size;
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(Graph* graph, int src, int dest) {
    int dist[MAX_NODES];
    MinHeap* minHeap = createMinHeap(MAX_NODES);

    for (int v = 0; v < MAX_NODES; ++v) {
        dist[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->position[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->position[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = MAX_NODES;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        Node* pCrawl = graph->head[u];
        while (pCrawl != NULL) {
            int v = pCrawl->vertex;

            if (isInMinHeap(minHeap, v) && dist[u] != INF &&
                pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    if (dist[dest] == INF) {
        printf("NO\n");
    } else {
        printf("YES\n%d\n", dist[dest]);
    }
}

int main() {
    int M, A, B;
    scanf("%d %d %d", &M, &A, &B);

    Graph* graph = createGraph();

    for (int i = 0; i < M; i++) {
        int X, Y, Z;
        scanf("%d %d %d", &X, &Y, &Z);
        addEdge(graph, X, Y, Z);
    }

    dijkstra(graph, A, B);

    return 0;
}
