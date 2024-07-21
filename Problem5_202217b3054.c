#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position player, box;
    int pushes, walks;
} State;

typedef struct Node {
    State state;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} PriorityQueue;

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

void push(PriorityQueue* pq, State state) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->state = state;
    newNode->next = NULL;

    if (pq->head == NULL || pq->head->state.pushes > state.pushes ||
        (pq->head->state.pushes == state.pushes && pq->head->state.walks > state.walks)) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        Node* current = pq->head;
        while (current->next != NULL && (current->next->state.pushes < state.pushes ||
            (current->next->state.pushes == state.pushes && current->next->state.walks <= state.walks))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

State pop(PriorityQueue* pq) {
    if (pq->head == NULL) {
        State state = {{-1, -1}, {-1, -1}, -1, -1};
        return state;
    }
    Node* temp = pq->head;
    pq->head = pq->head->next;
    State state = temp->state;
    free(temp);
    return state;
}

int isEmpty(PriorityQueue* pq) {
    return pq->head == NULL;
}

int isValid(int x, int y, int r, int c, char maze[MAX][MAX]) {
    return x >= 0 && x < r && y >= 0 && y < c && maze[x][y] != '#';
}

int visited[MAX][MAX][MAX][MAX];

int bfs(int r, int c, Position start, Position box, Position target, char maze[MAX][MAX]) {
    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    PriorityQueue* pq = createPriorityQueue();

    State initialState = {start, box, 0, 0};
    push(pq, initialState);
    visited[start.x][start.y][box.x][box.y] = 1;

    while (!isEmpty(pq)) {
        State current = pop(pq);

        if (current.box.x == target.x && current.box.y == target.y) {
            return current.pushes;
        }

        for (int i = 0; i < 4; i++) {
            int newPlayerX = current.player.x + dir[i][0];
            int newPlayerY = current.player.y + dir[i][1];

            if (isValid(newPlayerX, newPlayerY, r, c, maze)) {
                if (newPlayerX == current.box.x && newPlayerY == current.box.y) {
                    int newBoxX = current.box.x + dir[i][0];
                    int newBoxY = current.box.y + dir[i][1];

                    if (isValid(newBoxX, newBoxY, r, c, maze) && !visited[newPlayerX][newPlayerY][newBoxX][newBoxY]) {
                        visited[newPlayerX][newPlayerY][newBoxX][newBoxY] = 1;
                        State newState = {{newPlayerX, newPlayerY}, {newBoxX, newBoxY}, current.pushes + 1, current.walks + 1};
                        push(pq, newState);
                    }
                } else if (!visited[newPlayerX][newPlayerY][current.box.x][current.box.y]) {
                    visited[newPlayerX][newPlayerY][current.box.x][current.box.y] = 1;
                    State newState = {{newPlayerX, newPlayerY}, {current.box.x, current.box.y}, current.pushes, current.walks + 1};
                    push(pq, newState);
                }
            }
        }
    }

    return -1;
}

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    char maze[MAX][MAX];
    Position start, box, target;

    for (int i = 0; i < r; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < c; j++) {
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
                maze[i][j] = '.';
            } else if (maze[i][j] == 'B') {
                box.x = i;
                box.y = j;
                maze[i][j] = '.';
            } else if (maze[i][j] == 'T') {
                target.x = i;
                target.y = j;
                maze[i][j] = '.';
            }
        }
    }

    memset(visited, 0, sizeof(visited));
    int result = bfs(r, c, start, box, target, maze);
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
