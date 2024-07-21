#include <stdio.h>
#include <stdlib.h>

#define MAX 250
#define INF 1000000

typedef struct {
    int x, y, jumps;
} Node;

int M, N;
int R[MAX][MAX], D[MAX][MAX];
int visited[MAX][MAX];

// Direction vectors for moving right and down
int dx[] = {1, 0};
int dy[] = {0, 1};

int isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

int bfs() {
    Node queue[MAX * MAX];
    int front = 0, rear = 0;

    // Start from the top-left corner
    queue[rear++] = (Node){0, 0, 0};
    visited[0][0] = 1;

    while (front < rear) {
        Node current = queue[front++];

        // Check if we reached the bottom-right corner
        if (current.x == M - 1 && current.y == N - 1) {
            return current.jumps;
        }

        // Try all possible jumps to the right
        for (int r = 1; r <= R[current.x][current.y]; r++) {
            int newX = current.x;
            int newY = current.y + r;
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = 1;
                queue[rear++] = (Node){newX, newY, current.jumps + 1};
            }
        }

        // Try all possible jumps down
        for (int d = 1; d <= D[current.x][current.y]; d++) {
            int newX = current.x + d;
            int newY = current.y;
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = 1;
                queue[rear++] = (Node){newX, newY, current.jumps + 1};
            }
        }
    }

    return INF; // If no path found
}

int main() {
    scanf("%d %d", &M, &N);

    // Read R values
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &R[i][j]);
        }
    }

    // Read D values
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &D[i][j]);
        }
    }

    // Initialize visited array
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }

    // Perform BFS to find the minimum number of jumps
    int result = bfs();

    // Print the result
    if (result != INF) {
        printf("%d\n", result);
    } else {
        printf("-1\n"); // If no path found
    }

    return 0;
}
