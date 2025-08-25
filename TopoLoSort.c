#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// A structure for a node in the adjacency list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Adjacency list representation
Node* adj[MAX_VERTICES];
int in_degree[MAX_VERTICES];
int vertices_count;

// Queue for BFS
int queue[MAX_VERTICES];
int front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX_VERTICES - 1) return; // Queue is full
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1) return -1; // Queue is empty
    int v = queue[front++];
    if (front > rear) {
        front = rear = -1;
    }
    return v;
}

bool isQueueEmpty() {
    return front == -1;
}

void add_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = adj[u];
    adj[u] = newNode;
    in_degree[v]++;
}

void topologicalSort_Kahn() {
    for (int i = 0; i < vertices_count; i++) {
        if (in_degree[i] == 0) {
            enqueue(i);
        }
    }

    int count = 0;
    printf("Topological Sort (Kahn's Algorithm):\n");

    while (!isQueueEmpty()) {
        int u = dequeue();
        printf("%d ", u);
        count++;

        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->data;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                enqueue(v);
            }
            temp = temp->next;
        }
    }

    if (count != vertices_count) {
        printf("\nGraph contains a cycle!\n");
    } else {
        printf("\n");
    }
}

int main() {
    vertices_count = 6;
    for (int i = 0; i < vertices_count; i++) {
        adj[i] = NULL;
        in_degree[i] = 0;
    }

    add_edge(5, 2);
    add_edge(5, 0);
    add_edge(4, 0);
    add_edge(4, 1);
    add_edge(2, 3);
    add_edge(3, 1);

    topologicalSort_Kahn();

    return 0;
}
