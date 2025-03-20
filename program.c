#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struktur node link list
typedef struct Node {
    char data[MAX];
    struct Node *next;
} Node;

// Struktur stack
typedef struct {
    Node *top;
} Stack;

// Function to initialize the stack
void initStack(Stack *s) {
    s->top = NULL;
}
// Function to check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == NULL;
}

// Function to push an element onto the stack
void push(Stack *s, char *c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->data, c);
    newNode->next = s->top;
    s->top = newNode;
}

// Function to pop an element from the stack
char *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    Node *temp = s->top;
    char *data = (char *)malloc(MAX * sizeof(char));
    strcpy(data, temp->data);
    s->top = temp->next;
    free(temp);
    return data;
}
