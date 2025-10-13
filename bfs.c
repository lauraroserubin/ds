#include <stdio.h>
#include <stdlib.h>
#define MAX 100  
int queue[MAX];
int front = -1, rear = -1;
void enqueue(int vertex) {
    if (rear == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    queue[++rear] = vertex;
}
int dequeue() {
    if (front == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    int vertex = queue[front++];
    if (front > rear) {
        front = rear = -1; 
    }
    return vertex;
}
void bfs(int adj[MAX][MAX], int n, int start) {
    int visited[MAX] = {0};
    enqueue(start);
    visited[start] = 1;
    while (front != -1) {
        int v = dequeue();
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}
int main() {
    int adj[MAX][MAX];
    int n, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    printf("Enter the starting vertex: ");
    scanf("%d", &start);
    printf("BFS starting from vertex %d: ", start);
    bfs(adj, n, start);
    printf("\n");
    return 0;
}
