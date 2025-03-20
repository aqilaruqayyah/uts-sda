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
