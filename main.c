
#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
char files[MAX][50];
int visited[MAX];
int n;

// Breadth First Search
void BFS(int start, int target) {
    int queue[MAX];
    int front = 0, rear = 0;
    int found = 0;

    memset(visited, 0, sizeof(visited));

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];

        printf("%s ", files[current]);

        if (current == target) {
            found = 1;
        }

        for (int i = 0; i < n; i++) {
            if (graph[current][i] &&
                !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    if (found)
        printf("\nFile found using BFS!\n");
    else
        printf("\nFile not found using BFS!\n");
}

// Depth First Search
void DFS(int current) {
    visited[current] = 1;

    printf("%s ", files[current]);

    for (int i = 0; i < n; i++) {
        if (graph[current][i] &&
            !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    int edges, u, v;
    int start, target;
    char searchFile[50];

    printf("Enter number of files/folders: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of nodes!\n");
        return 1;
    }

    printf("\nEnter file/folder names:\n");

    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        scanf("%49s", files[i]);
    }

    printf("\nEnter number of connections: ");
    scanf("%d", &edges);

    if (edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of connections!\n");
        return 1;
    }

    printf("\nEnter connections (node numbers):\n");

    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n ||
            v < 0 || v >= n || u == v) {
            printf("Invalid connection!\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("\nEnter starting node number: ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting node!\n");
        return 1;
    }

    printf("Enter file to search: ");
    scanf("%49s", searchFile);

    target = -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(files[i], searchFile) == 0) {
            target = i;
            break;
        }
    }

    if (target == -1) {
        printf("\nFile does not exist in graph!\n");
        return 0;
    }

    BFS(start, target);

    memset(visited, 0, sizeof(visited));

    printf("\nDFS Traversal: ");
    DFS(start);

    if (visited[target])
        printf("\nFile found using DFS!\n");
    else
        printf("\nFile not found using DFS!\n");

    return 0;
}
