#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define Vartics 100

enum color {
    WHITE,
    GRAY,
    BLACK
};

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* adj[Vartics];
enum color color[Vartics];
int previous[Vartics];
int d[Vartics];
int Vartics_count;
int queue[Vartics];
int front = -1;
int rare = -1;

void enqueue(int vertex) {
    if (rare == Vartics - 1) {
        printf("The Queue is Full");
    } else {
        if (front == -1) {
            front = 0;
        }
        rare++;
        queue[rare] = vertex;
    }
}

int dequeue() {
    int vertex;
    if (front == -1) {
        printf("The queue is Empty\n");
        return -1;
    } else {
        vertex = queue[front];
        front++;
        if (front > rare) {
            front = rare = -1;
        }
        return vertex;
    }
}

bool is_queue_empty() {
    return front == -1;
}

void add_edges(int u, int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void BFS(int s) {
    for (int u = 0; u < Vartics_count; u++) {
        if (u != s) {
            color[u] = WHITE;
            previous[u] = -1;
            d[u] = -1;
        }
    }
    color[s] = GRAY;
    d[s] = 0;
    previous[s] = -1;

    front = rare = -1;
    enqueue(s);

    while (!is_queue_empty()) {
        int u = dequeue();
        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->data;
            if (color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                previous[v] = u;
                enqueue(v);
            }
            temp = temp->next;
        }
        color[u] = BLACK;
    }
}

int main() {
    Vartics_count = 8;
    for (int i = 0; i < Vartics_count; i++) {
        adj[i] = NULL;
    }
    add_edges(0, 1);
    add_edges(0, 2);
    add_edges(1, 3);
    add_edges(1, 4);
    add_edges(2, 5);
    add_edges(3, 6);
    add_edges(3, 7);
    add_edges(4, 8);

    printf("BFS:\n");
    BFS(0);
    for (int i = 0; i < Vartics_count; i++) {
        printf("vertex %d : color = %d, distance = %d, predecessor = %d\n", i, color[i], d[i], previous[i]);
    }
    return 0;
}


