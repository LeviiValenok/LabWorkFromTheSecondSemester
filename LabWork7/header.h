#ifndef LABWORK6_HEADER_H
#define LABWORK6_HEADER_H
#endif //LABWORK6_HEADER_H
#include <stdbool.h>

typedef struct Tree
{
    char word [20];
    char translation [20];
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
} Node;

void mainMenu();
int readMenuOptionAndValidate();

Node *initializeTree(Node *root);
void displayTreeRecursively(Node* root);
Node* addElementToTree(Node* root, char* word, char* translate);
void displayNonRecursively(Node* root);
int rightChoice();
void clearTree(Node* root);
void deleteSymbols(char* string);
Node* deleteItem(Node* root, char* compareString);
