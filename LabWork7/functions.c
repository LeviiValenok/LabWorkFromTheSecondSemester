#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void notImplementedWarning()
{
    printf("Menu option currently is not implemented, try to do it later ¯\\_(0.0)_/¯ \n\n");
}

int menuForChoice()
{
    int choice;
    printf("\t1 to display tree (recursively)\n");
    printf("\t2 to display tree (non-recursively) \n");
    printf("\t3 to add a new element to the tree\n");
    printf("\t4 to deleteItem one element from the tree\n");
    printf("\t5 to deleteItem all elements from the tree \n");
    printf("\t0 to exit\n");
    printf("Enter ---->");
    choice = readMenuOptionAndValidate();
    return choice;
}
void deleteSymbols(char* string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
        i++;
    }
}

void mainMenu()
{
    Node* tree = NULL;
    Node* root = NULL;
    bool shouldQuit = false;

    while (!shouldQuit)
    {
        switch(menuForChoice())
        {
            case 1: {
                displayTreeRecursively(root);
                break;
            }
            case 2:
            {
                displayNonRecursively(root);
//                notImplementedWarning();

                // displayTreeNonRecursively();
                break;
            }
            case 3:
            {
                if (root == NULL)
                {
                    root = initializeTree(root);
                }
                bool isQuite = false;
                while (!isQuite)
                {
                    printf("Enter a foreign word to add as an element: \n");
                    rewind(stdin);
                    char *newWord = (char *)calloc(20, sizeof(char));
                    fgets(newWord, 20, stdin);
                    deleteSymbols(newWord);
                    rewind(stdin);
                    printf("Enter a translate for the word to add as an element: \n");
                    char *translateNewWord = (char *) calloc(20, sizeof(char));
                    fgets(translateNewWord, 20, stdin);
                    deleteSymbols(translateNewWord);
                    root = addElementToTree(root, newWord, translateNewWord);
                    printf("\tDo you want to add more?\n");
                    printf("\t1 to add more\n");
                    printf("\t2 to quite\n");
                    switch(rightChoice())
                    {
                        case 1:
                        {
                            break;
                        }
                        case 2:
                        {
                            isQuite = true;
                        }
                    }
                }
                // TODO: clear spaces in newWord
                // TODO: read translation from the input

                break;
            }
            case 4:
            {
                printf("Enter a string to seek by \n");
                char* compareString = (char*)calloc(20, sizeof(char));
                gets(compareString);
                root = deleteItem(root, compareString);
                break;
            }
            case 5:
            {
                clearTree(root);
                root = NULL;
                break;
            }
            case 0:
            {
                shouldQuit = true;
                clearTree(root);
                break;
            }
            default:
            {
                printf("Warning: Wrong choice, option does not exist!\n\n");
                break;
            }
        }
    }
}

Node *initializeTree(Node *root)
{
    root = malloc(sizeof(Node));
    rewind(stdin);
    printf("Enter a foreign word :\n");
    char* foreignWord = (char*) calloc(20, sizeof(char));
    gets(foreignWord);
    rewind(stdin);
    printf("Enter a translation of word :\n");
    char* translation = (char*) calloc(20, sizeof(char));
    gets(translation);
    strcpy(root->word, foreignWord);
    strcpy(root->translation, translation);
    root->parent = NULL;
    root->left = root->right = NULL;
    return root;
}

Node* addElementToTree(Node* root, char* word, char* translate)
{
    if (strcmp(word, "") == 0)
    {
        printf("Error: elements should have not empty value!\n");
        return root;
    }
        Node *root2 = root, *root3 = NULL;
        Node *tmp = malloc(sizeof(Node));
        strcpy(tmp->word, word);
        strcpy(tmp->translation, translate);

        while (root2 != NULL)
        {
            root3 = root2;
            int compareResult = strcmp(word, root2->word);
            if (compareResult < 0)
            {
                root2 = root2->left;
            } else if (compareResult > 0)
            {
                root2 = root2->right;
            } else
            {
                printf("Error: elements must be unique!\n");
                return root;
            }
        }

        tmp->parent = root3;
        tmp->left = NULL;
        tmp->right = NULL;

        int compareResult = strcmp(word, root3->word);
        if (compareResult < 0) {
            root3->left = tmp;
        } else if (compareResult > 0) {
            root3->right = tmp;
        } else
        {
            printf("Error: elements must be unique!\n");
            return root;
        }
        return root;
    }

void displayTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    if (strcmp(root->word, "") != 0)
    {
        printf("%s %s", root->word, root->translation);
        printf("\n");
    }
    displayTree(root->left);
    displayTree(root->right);
}

void displayTreeRecursively(Node* root)
{
    printf("Tree:\n");

    if (root == NULL)
    {
        printf("(EMPTY)\n");
        return;
    }
    displayTree(root);
    printf("\n");
}

void clearTree(Node* root)
{
    if(root == NULL)
    {
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    free(root);
    return;

}
int readMenuOptionAndValidate()
{
    int number;
    char c;

    while (scanf("%d%c", &number, &c) != 2 || c != '\n' || number < 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }

    return number;
}

Node* minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
int rightChoice()
{
    int number;
    char c;
    while ((scanf("%d%c", &number, &c) != 2 || c != '\n' || number < 0) || number > 3)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return number;
}
/*void deleteItem(Node** root)
{
    if (!*root)
    {
        puts("Binary tree is empty\n");
        return;
    }
    Node* temp1, * temp2, * temp3;
    char tempString[20];
    int compareResult;
    int flag;
    rewind(stdin);
    printf("Enter a string to seek by: \n");
    fgets(tempString, 20, stdin);
    rewind(stdin);
    tempString[strlen(tempString) - 1] = '\0';
    temp2 = temp1 = *root;
    flag = 0;
    do
    {
        if (!(compareResult = strcmp(tempString, temp1->word)))
            flag = 1;
        if (compareResult < 0)
        {
            if (temp1->left)
            {
                temp2 = temp1;
                temp1 = temp1->left;
            }
            else flag = 1;
        }
        if (compareResult > 0)
        {
            if (temp1->right)
            {
                temp2 = temp1;
                temp1 = temp1->right;
            }
            else flag = 1;
        }
    } while (!flag);
    if (compareResult)
    {
        puts("Not found\n");
        return;
    }
    else
    {
        compareResult = strcmp(temp1->word, temp2->word);
        temp3 = temp1;
        if (compareResult < 0)
        {
            if (temp1->right)
            {
                temp3 = temp1->right;
                while (temp3->left) temp3 = temp3->left;
                temp2->left = temp1->right;
                temp3->left = temp1->left;
            }
            else temp2->left = temp1->left;
        }
        else
        {
            if (temp1->left)
            {
                temp3 = temp1->left;
                while (temp3->right) temp3 = temp3->right;
                temp2->right = temp1->left;
                temp3->right = temp1->right;
            }
            else temp2->right = temp1->right;
        }
        free(temp1);
    }
}*/
void displayNonRecursively(Node* root)
{
    struct stack
    {	Node* leaf;
        struct stack *next;
    } *pointer, *pointer1 = NULL;

    if (!root)
    {
        printf("Tree is empty\n");
        return;
    }
    int index = 1;
    pointer = (struct stack*)calloc(1, sizeof(struct stack));
    pointer->leaf = root;
    pointer->next = pointer1;
    printf("Root is\n %s %s\n", root->word, root->translation);
    while (pointer || root->right)
    {
        do
        {
            if(index && root->left) root = root->left;
            else if(root->right) root = root->right;
            index = 1;
            if(root->left && root->right)
            {
                pointer1 = pointer;
                pointer = (struct stack *)calloc(1, sizeof(struct stack)); // новый эл-т стека
                pointer->leaf = root;
                pointer->next = pointer1;
            }
            printf("%s %s\n", root->word, root->translation);
        } while(root->left || root->right);
        if (pointer)
        {
            root = pointer->leaf;
            pointer1 = pointer->next;
            free(pointer);
        }
        pointer = pointer1;
        if (root->left && root->right)
            index = 0;
        else break;
    }
}


Node* deleteItem(Node* root, char* compareString)
{

    if(root == NULL)
        return root;

    if(strcmp(compareString, root->word)==0){

        Node *temp;
        if(root->right == NULL)
            temp = root->left;
        else
        {
            Node *pointer = root->right;
            if(pointer->left == NULL)
            {
                pointer->left = root->left;
                temp = pointer;
            }
            else
            {
                Node* minimal = pointer->left;
                while (minimal ->left != NULL)
                {
                    pointer = minimal;
                    minimal = pointer->left;
                }
                pointer->left = minimal->right;
                minimal->left = root->left;
                minimal->right = root->right;
                temp = pointer;
            }
        }
        free(root);
        return temp;
    }
    else if (strcmp(compareString, root->word) < 0)
        root->left = deleteItem(root->left, compareString);
    else
        root->right = deleteItem(root->left, compareString);
    return root;

}