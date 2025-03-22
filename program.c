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

// Function to get the top element of the stack
char *peek(Stack *s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->top->data;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to get the precedence of an operator
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Function to convert Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isalnum(c)) { // Check if character is a letter or digit
            postfix[j++] = c;
        } else if (c == '(') {
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (c == ')') {
            while (!isEmpty(&s) && strcmp(peek(&s), "(") != 0) {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s); // Remove '(' from stack
        } else if (isOperator(c)) {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(c)) {
                postfix[j++] = pop(&s)[0];
            }
            char temp[2] = {c, '\0'};
            push(&s, temp);
        }
        i++;
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s)[0];
    }

    postfix[j] = '\0';
}

// Function to convert Postfix to Infix
void postfixToInfix(char postfix[], char infix[]) {
    Stack s;
    initStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isalnum(c)) { // Check if character is a letter or digit
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op2, c, op1);
            push(&s, temp);
        }
        i++;
    }

    strcpy(infix, pop(&s));
}

// Function to convert Infix to Prefix
void infixToPrefix(char infix[], char prefix[]) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char reversedInfix[MAX], reversedPrefix[MAX];

    // Reverse the infix expression
    strcpy(reversedInfix, strrev(infix));

    // Replace '(' with ')' and vice versa
    for (i = 0; reversedInfix[i] != '\0'; i++) {
        if (reversedInfix[i] == '(') {
            reversedInfix[i] = ')';
        } else if (reversedInfix[i] == ')') {
            reversedInfix[i] = '(';
        }
    }

    // Convert reversed infix to postfix
    infixToPostfix(reversedInfix, reversedPrefix);

    // Reverse the postfix expression to get prefix
    strcpy(prefix, strrev(reversedPrefix));
}

// Function to convert Prefix to Infix
void prefixToInfix(char prefix[], char infix[]) {
    Stack s;
    initStack(&s);
    int i = strlen(prefix) - 1;

    while (i >= 0) {
        char c = prefix[i];

        if (isalnum(c)) { // Check if character is a letter or digit
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op1, c, op2);
            push(&s, temp);
        }
        i--;
    }

    strcpy(infix, pop(&s));
}

// Function to convert Prefix to Postfix
void prefixToPostfix(char prefix[], char postfix[]) {
    Stack s;
    initStack(&s);
    int i = strlen(prefix) - 1;

    while (i >= 0) {
        char c = prefix[i];

        if (isalnum(c)) { // Check if character is a letter or digit
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "%s%s%c", op1, op2, c);
            push(&s, temp);
        }
        i--;
    }

    strcpy(postfix, pop(&s));
}

// Function to convert Postfix to Prefix
void postfixToPrefix(char postfix[], char prefix[]) {
    Stack s;
    initStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isalnum(c)) { // Check if character is a letter or digit
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "%c%s%s", c, op2, op1);
            push(&s, temp);
        }
        i++;
    }

    strcpy(prefix, pop(&s));
}

// Fungsi utama dengan menu
int main() {
    int choice;
    char input[MAX], result[MAX];
    
    do {
        printf("\n+-------------------------------+\n");
        printf("|      Menu Konversi Ekspresi   |\n");
        printf("+-------------------------------+\n");
        printf("| 1. Infix ke Postfix           |\n");
        printf("| 2. Postfix ke Infix           |\n");
        printf("| 3. Infix ke Prefix            |\n");
        printf("| 4. Prefix ke Infix            |\n");
        printf("| 5. Prefix ke Postfix          |\n");
        printf("| 6. Postfix ke Prefix          |\n");
        printf("| 7. Keluar                     |\n");
        printf("+-------------------------------+\n");
        printf("Pilih opsi (1-7): ");
        scanf("%d", &choice);
        getchar();

        if (choice == 7) break;

        printf("Masukkan ekspresi: ");
        fgets(input, MAX, stdin);
        input[strcspn(input, "\n")] = 0;

        switch (choice) {
            case 1: 
            infixToPostfix(input, result); 
            break;

            case 2: 
            postfixToInfix(input, result); 
            break;

            case 3: 
            infixToPrefix(input, result); 
            break;

            case 4: 
            prefixToInfix(input, result); 
            break;

            case 5: 
            prefixToPostfix(input, result); 
            break;

            case 6: 
            postfixToPrefix(input, result); 
            break;

            default: 
            printf("Pilihan tidak valid!\n"); 
            continue;
        }
        
        printf("Hasil: %s\n", result);
    } while (choice != 7);
    
    printf("Terima kasih!\n");
    return 0;
}
